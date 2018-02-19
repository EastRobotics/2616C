#include "main.h"
#include "string.h"

#define swinglimit (digitalRead(9)==LOW)

extern  bool autolift;
extern TaskHandle liftTH, swingTH, autoGrabTH;
extern Semaphore AutoStackSema;
extern int swingdownset;
extern int liftdownset;

void initLiftData(void) {
  liftControl.mtrPort[0] = 2;
  liftControl.mtrPort[1] = 6;
  liftControl.speed = 127;

  liftControl.encLimit = 80;
  liftControl.timeout = 5000;
  liftControl.exec = false;
  liftControl.coneDetectThreshold = 15;
  liftControl.autostack = false;
}
void initSwingData() {
  swingControl.mtrPort = 3;
  swingControl.speed = -127;
  swingControl.encLimit = 40;
}
void setLiftMotors(void) {

    motorSet(2, 127);
    motorSet(6, 127);
  // for (int m = 0; m < liftPortCount; m++) {
  //   liftControl.speed = liftControl.speed * (abs(liftControl.error  + 1)/(liftControl.error + 1));
  //   liftControl.error = liftControl.encDesiredPos - liftControl.encActualPos;
  //   motorSet(liftControl.mtrPort[m], liftControl.speed);
  // }
}

void stopLiftMotors(void) {
  motorSet(2, 0);
  motorSet(6, 0);
  // for (int m = 0; m < liftPortCount; m++) {
  //   motorSet(liftControl.mtrPort[m], 0);
  // }
}
void lift(void *ignore) { // Lift task function
  while (1) {
    liftControl.encActualPos = encoderGet(liftEnc);
    if (liftControl.exec) {
        if (motorGet(liftControl.mtrPort[0]) == 0) {
          setLiftMotors();
        }
        if (liftControl.encActualPos >= liftControl.encLimit) {
          for (int m = 0; m < liftPortCount; m++) {
            motorSet(liftControl.mtrPort[m], 0);
            liftControl.exec = false;
            strncpy(liftControl.message, "Hit Encoder Limit", 17);
          }
        }
        if (liftControl.encActualPos >= liftControl.encDesiredPos) {
          for (int m = 0; m < liftPortCount; m++) {
            motorSet(liftControl.mtrPort[m], 0);
            liftControl.exec = false;
            strncpy(liftControl.message, "Hit Desired", 11);
          }
        }
         if(swingControl.actualPos >= swingControl.encLimit) {
           stopLiftMotors();
           liftControl.exec = false;
          liftControl.encDesiredPos = 0;
          }
        }
       liftControl.encActualPos = encoderGet(liftEnc);
       liftControl.error = liftControl.encDesiredPos - liftControl.encActualPos;
      delay(20);

  }
}

void swing(void* ignore) {
  while (1) {
    if (swingControl.exec) {
      if (motorGet(swingControl.mtrPort) == 0) {
          motorSet(swingControl.mtrPort, swingControl.speed);
      }
      if (swingControl.actualPos >= liftControl.coneDetectThreshold) {
        motorSet(swingControl.mtrPort, -20);
        liftControl.encDesiredPos = 45;
        liftControl.exec = true;
      }
    }
      swingControl.actualPos = ultrasonicGet(intakeUS);
    //  printf("IN swing control\n");
      delay(50);
  }
}
void closeClaw() {
  motorSet(1, -127);
  delay(200);
  motorSet(1,-10);
}

void openClaw() {
  motorSet(1, 127);
  delay(200);
  motorSet(1,0);
}

void autoGrab(void *ignore) {
  while(1) {
    if (taskGetState(swingTH) == TASK_SUSPENDED) {
      taskResume(swingTH);
    }

    if (taskGetState(liftTH) == TASK_SUSPENDED) {
      taskResume(liftTH);
    }
  swingControl.exec = true;
  liftControl.exec = true;
  while (liftControl.coneDetectThreshold > swingControl.actualPos) {
    printf("%d %d  - Not at limit!\n",liftControl.coneDetectThreshold , swingControl.actualPos);
  }
  printf("Finish Swing\n");
  taskSuspend(swingTH);
  motorSet(swingControl.mtrPort, -90);
  delay(500);
  motorSet(swingControl.mtrPort, 0);
  printf("Open Claw\n");
  openClaw();
  delay(350);


  fprintf(uart1, "%s %d", liftControl.exec ? "True":"False", liftControl.encDesiredPos);
  taskSuspend(NULL);
  }
}

int getUS (){
  int us = ultrasonicGet(intakeUS);
   return(us==-1?999:us);
}


void autoGrab2(void *ignore) {
  int stacktop;
  while(true){
      printf("AutoGrab - Wait for Semaphore\n");
      semaphoreTake(AutoStackSema,1000000);

    printf("AutoGrab - Got Semaphore\n");

  // start goliath
  //
int swingE;
  motorSet(3,-90);
  while(!swinglimit){}
  motorSet(3,0);
  swingE = encoderGet(swingEnc) ;
  //printf(" make sure its running at a stall value\n");

  motorSet(1, -30);

  printf(" start dr4b up\n");
  motorSet(2,127);
  motorSet(6,127);

 printf("Start IntakeUS = %d\n",ultrasonicGet(intakeUS));
  printf(" wait for ultrasonic to reach required value (15)\n");
  while(ultrasonicGet(intakeUS) < 15){
printf("IntakeUS = %d\n",ultrasonicGet(intakeUS));
}
stacktop = encoderGet(liftEnc);
  printf("  stop dr4b\n");
  motorSet(2,0);
  motorSet(6,0);


  printf(" start goliath swing\n");
  motorSet(3, 90);

  printf(" wait for goliath u to reach 280\n");
  while(encoderGet(swingEnc) > swingE - 350)
  {printf("Swing = %d - %d  -%d\n",encoderGet(swingEnc),swingE,swingE-315);
}
   motorSet(3, 0);
   motorSet(2,-40);
   motorSet(6,-40);
     while (encoderGet(liftEnc)>(stacktop>10?stacktop - 5:stacktop)){}
     motorSet(2,0);
     motorSet(6,0);
 printf(" stop swing\n");



  printf(" output goliath\n");
  motorSet(1, 127);
  delay(200);
  motorSet(1,0);
  autolift = false;
  //taskDelete(autoGrabTH);
  printf("AutoGrab - Releasing Semaphone\n");
  semaphoreGive(AutoStackSema);
  delay(100);
}
}

void autodown(){
  int lifttop = encoderGet(liftEnc);
  motorSet(1,127);
  delay(300);
  motorSet(2,127);
  motorSet(6,127);
  while(encoderGet(liftEnc) < lifttop+10){}
  motorSet(1,0);
  motorSet(2,0);
  motorSet(6,0);
  motorSet(3, -110);
   while(!swinglimit){}//encoderGet(swingEnc) < swingdownset
   motorSet(3, 0);
   motorSet(2,-127);
   motorSet(6,-127);
   while(encoderGet(liftEnc) > liftdownset+10){}
   motorSet(2,0);
   motorSet(6,0);
   motorSet(1,-90);
}
void lifttostack() {

}
