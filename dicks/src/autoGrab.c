#include "main.h"
#include "string.h"

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
  for (int m = 0; m < liftPortCount; m++) {
    liftControl.speed = liftControl.speed * (abs(liftControl.error  + 1)/(liftControl.error + 1));
    liftControl.error = liftControl.encDesiredPos - liftControl.encActualPos;
    motorSet(liftControl.mtrPort[m], liftControl.speed);
  }
}

void stopLiftMotors(void) {
  for (int m = 0; m < liftPortCount; m++) {
    motorSet(liftControl.mtrPort[m], 0);
  }
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
      fprintf(uart1, "Message: %s\n", liftControl.message);

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
      swingControl.actualPos = ultrasonicGet(liftUS);
    //  printf("IN swing control\n");
      delay(50);
  }
}
void closeClaw() {
  motorSet(1, -127);
  delay(200);
  motorSet(1,0);
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
void lifttostack() {
  
}
