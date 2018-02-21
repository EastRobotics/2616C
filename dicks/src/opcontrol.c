
#include "main.h"
#include "string.h"
#define threshold(x) (abs(x)>24?x:0)

#define mogoVal joystickGetAnalog('2','3')
#define mogoVal_actual joystickGetDigital(1, 5, JOY_UP)?-127:(joystickGetDigital(1, 5, JOY_DOWN)?127:0)

#define MASTER_CH3 joystickGetAnalog(1, 3)
#define drive threshold(MASTER_CH3)
#define swinglimit (digitalRead(9)==LOW)
// #define MASTER_CH4 joystickGetAnalog(1, 4)
// #define strafe threshold(MASTER_CH4)

#define MASTER_CH1 joystickGetAnalog(1, 1)
#define rotate threshold(MASTER_CH1)
#define liftVal threshold(joystickGetAnalog(2,3))

//#define goliath joystickGetDigital(2, 6, JOY_UP)?127:(joystickGetDigital(2, 6, JOY_DOWN)?-127:0)
#define swingVal (-threshold(joystickGetAnalog(2,2)))
#define grabbyMcGrabberson joystickGetDigital(1, 7, JOY_DOWN)?127:(joystickGetDigital(1, 7, JOY_RIGHT)?-127:0)

Semaphore AutoStackSema, downSema;
int swingdownset;
int liftdownset;
//#define grabButton joystickGetDigital(2, 7, JOY_UP)
void hc05Init(char uart, bool atMode);

char *bluetoothRead(char uart);
//TaskHandle liftTH, swingTH, autoGrabTH;
TaskHandle liftTH, swingTH, autoGrabTH,autodownTH;
 bool autolift;
int gollastdir = 0;
 int goliath(){
   int golspeed;
   if(joystickGetDigital(2, 6, JOY_UP)==1 && joystickGetDigital(2, 6, JOY_DOWN)==0){
    golspeed = -127;
    gollastdir = 1;
  //  printf("UP \n");
  }else if (joystickGetDigital(2, 6, JOY_DOWN)==1 &&  joystickGetDigital(2, 6, JOY_UP)==0)
  {
      golspeed = 127;
      gollastdir = 0;
    //  printf("Down \n");
  }else if (gollastdir == 1 )
    {
        golspeed = -25;
        //    printf("Lastdir 1 \n");
    }else if(autolift == true) {
        golspeed = -70;
    }
    else{
        golspeed = 0;
    //    printf("Lastdir 0\n");
      }
    return (golspeed);
 }
bool grabButton(){
//  printf("Autolift = %s\n",autolift==true?"True":"False");
  int js = joystickGetDigital(2, 7, JOY_UP);
  if(js == 1)
  {
    printf("ButtonPressed\n" );
  }
  return (js == 1);
}

bool grabkillButton(){
  int js = joystickGetDigital(2, 7, JOY_DOWN);
//  printf("Autolift = %s\n",autolift==true?"True":"False");
  if(js == 1)
  {
    printf("KillButtonPressed\n" );
  }
  return (js == 1);
}

bool taskkillButtons(){
  int js = 0;
//  printf("Autolift = %s\n",autolift==true?"True":"False");
  if(joystickGetDigital(2, 7, JOY_LEFT) && joystickGetDigital(2, 8, JOY_RIGHT))
  {
    printf("TaskKillButtonsPressed\n" );
    js = 1;
  }
  return (js == 1);
}
bool taskstartButtons(){
  int js = 0;
//  printf("Autolift = %s\n",autolift==true?"True":"False");
  if(joystickGetDigital(2, 7, JOY_RIGHT) && joystickGetDigital(2, 8, JOY_LEFT))
  {
    printf("TaskStartButtonsPressed\n" );
    js = 1;
  }
  return (js == 1);
}
bool autodownButton(){
  int js = 0;
 js = joystickGetDigital(2, 8, JOY_DOWN);
//  printf("Autolift = %s\n",autolift==true?"True":"False");
  if(js == 1)
  {
    printf("AutoDownButtonPressed\n" );
  }
  return (js == 1);
}

void displaysensordata() {

  // int le;
  // int us;
  unsigned int bt;
if (bluetoothout) {
//  bprintf(uart1, "%c[2J", 27);  //Clear Screen
//  bprintf(uart1, "%c[H", 27);   // Top left corner
//

  fprintf(uart1, " \r\n \r\n \r\n");   // Top left corner
  fprintf(uart1, "Gyroscope: %d\n", gyroGet(gyROH));
  // fprintf(uart1, "Odom Ultrasonic: %d\n", ultrasonicGet(dexterUS));
  fprintf(uart1, "Mobile Goal Encoder: %d\n\n", analogRead(7));
  fprintf(uart1, "Lift Encoder: %d\n", encoderGet(liftEnc));
  fprintf(uart1, "Swing Encoder: %d\n", encoderGet(swingEnc));
  fprintf(uart1, "Intake Ultrasonic: %d\n", ultrasonicGet(intakeUS));
  bt = powerLevelMain();
  fprintf(uart1, "Main Battery Voltage: %0.4fV\n", ((float)bt) / 1000);
  fprintf(uart1, "Secondary Battery Voltage: %0.4fV\n", (float) analogRead(2) * 4.0 / 70);
  fprintf(uart1, "Swing Limit Switch: %s\n", (digitalRead(9) == LOW)?"Pressed":"Released");

  fprintf(uart1, "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
}
      delay(100);
}

void blueListen(char * message) {
    fprintf(uart1, "%x %x %x %x %x %x %x %x\r\n", message[0], message[1], message[2], message[3], message[4], message[5], message[6], message[7]);
    //fprintf(uart1, "|%s|\n", message);
    //fprintf(uart1,"%d\n", strcmp(message, "reset\r\n"));
    if (strcmp(message, "reset\r\n") == 0) {
        analogCalibrate(LINE_TRACKER_PORT);
        encoderReset(liftEnc);
        encoderReset(swingEnc);
        encoderReset(mogoEnc);
      	gyroReset(gyROH);
        fprint("Reset Sensor\r\n", uart1);


    }
    if(strncmp(message, "ping\r\n",4) == 0) {
        fprintf(uart1, "pong");
    }
    if(strncmp(message, "blueon\r\n",6) == 0) {
        bluetoothout = true;
        fprintf(uart1, "Bluetooth On");
    }
    if(strncmp(message, "blueoff\r\n",7) == 0) {
        bluetoothout = false;
        fprintf(uart1, "Bluetooth Off");
    }
    if(strncmp(message, "lreset\r\n",7) == 0) {
                encoderReset(liftEnc);
                fprintf(uart1, "Lift Encoder Reset");
    }
    delay(200);
}

void operatorControl() {
//TaskHandle dtask;
//T
 AutoStackSema = semaphoreCreate();
 semaphoreTake(AutoStackSema,0);
 downSema = semaphoreCreate();
 semaphoreTake(downSema,0);
 autoGrabTH = taskCreate(autoGrab2, TASK_DEFAULT_STACK_SIZE, NULL,
    TASK_PRIORITY_DEFAULT);
  autodownTH =  taskCreate(autodown, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);
 printf("Starting ----\n");
  bluetoothout = true;
	blisten(1, blueListen);
	printf("crap");
  bool autolift = false;
  taskRunLoop(displaysensordata, 1000);
	while (1) {
  // printf("%d | %d | %d\n", analogRead(7), ultrasonicGet(intakeUS), encoderGet(liftEnc));
  // printf("Limit Switch - %s\n",swinglimit==true?"Triggered":"Untriggered");
    if (!autolift) {
      motorSet(2, liftVal);
      motorSet(3, -swingVal);
      motorSet(6, liftVal);
      motorSet(1,  goliath());
      //printf("Autolift is false\n");
    }
	motorSet(4, (drive + rotate));
    	motorSet(7, (-drive + rotate));
	motorSet(8, (drive + rotate));
	motorSet(9, (-drive + rotate));
    !(analogRead(7) > 1234) || joystickGetDigital(1, 5, JOY_DOWN)?motorSet(10, mogoVal_actual):motorSet(10, abs(mogoVal_actual)/4);
    if (grabButton() && !autolift) {
      autolift=true;
      swingdownset = encoderGet(swingEnc);
      liftdownset = encoderGet(liftEnc);
      semaphoreGive(AutoStackSema);
    //  autolift = false;
    //  printf("OpControl - Given Returned\n");
      }
      if (grabkillButton()) {
        semaphoreTake(AutoStackSema,0);
        autolift=false;
      }
      delay(20);
      if(semaphoreTake(AutoStackSema,0)){
         printf("OpControl - Auto Semaphore Returned\n");
         autolift=false;
       }
    //   printf("Test down Sema\n");
       if(semaphoreTake(downSema,0)){
          printf("OpControl - Down Semaphore Returned\n");
          autolift=false;
        }
       if (autodownButton()  && !autolift) {
         gollastdir = 0;
         autolift=true;
         semaphoreGive(downSema);
         //autolift=false;
         gollastdir = 1;
       }
       if (taskkillButtons()){
         printf("AbortingStackTask");
         taskDelete(autoGrabTH);
         taskDelete(autodownTH);
         autolift=false;
       }
       if (taskstartButtons()){
         printf("RestartingStackTask");
         autoGrabTH = taskCreate(autoGrab2, TASK_DEFAULT_STACK_SIZE, NULL,
            TASK_PRIORITY_DEFAULT);

        autodownTH =  taskCreate(autodown, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);

            autolift=false;
       }
    delay(20);
	}
}
