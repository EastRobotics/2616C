
#include "main.h"
#include "string.h"
#define threshold(x) (abs(x)>24?x:0)

#define mogoVal joystickGetAnalog('2','3')
#define mogoVal_actual joystickGetDigital(1, 5, JOY_UP)?-127:(joystickGetDigital(1, 5, JOY_DOWN)?127:0)

#define MASTER_CH3 joystickGetAnalog(1, 3)
#define drive threshold(MASTER_CH3)

// #define MASTER_CH4 joystickGetAnalog(1, 4)
// #define strafe threshold(MASTER_CH4)

#define MASTER_CH1 joystickGetAnalog(1, 1)
#define rotate threshold(MASTER_CH1)
#define liftVal threshold(joystickGetAnalog(2,3))

#define claw joystickGetDigital(2, 6, JOY_UP)?127:(joystickGetDigital(2, 6, JOY_DOWN)?-127:0)
#define swingVal (-threshold(joystickGetAnalog(2,2)))
#define grabbyMcGrabberson joystickGetDigital(1, 7, JOY_DOWN)?127:(joystickGetDigital(1, 7, JOY_RIGHT)?-127:0)

#define grabButton joystickGetDigital(2, 7, JOY_UP)
void hc05Init(char uart, bool atMode);

char *bluetoothRead(char uart);
//TaskHandle liftTH, swingTH, autoGrabTH;

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
  fprintf(uart1, "Odom Ultrasonic: %d\n", ultrasonicGet(dexterUS));
  fprintf(uart1, "Mobile Goal Encoder: %d\n\n", analogRead(7));
  fprintf(uart1, "Lift Encoder: %d\n", encoderGet(liftEnc));
  fprintf(uart1, "Swing Encoder: %d\n", analogRead(5));
  fprintf(uart1, "Lift Ultrasonic: %d\n", ultrasonicGet(liftUS));
  bt = powerLevelMain();
  fprintf(uart1, "Main Battery Voltage: %0.4fV\n", ((float)bt) / 1000);
  fprintf(uart1, "Secondary Battery Voltage: %0.4fV\n", (float) analogRead(2) * 4.0 / 70);
  fprintf(uart1, "Claw Limit Switch: %s\n", (digitalRead(CLAW_LIMIT) == LOW)?"Pressed":"Released");

  fprintf(uart1, " \r\n \r\n \r\n");
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
  liftTH = taskCreate(lift, TASK_DEFAULT_STACK_SIZE, NULL,
           TASK_PRIORITY_DEFAULT);
  swingTH = taskCreate(swing, TASK_DEFAULT_STACK_SIZE, NULL,
           TASK_PRIORITY_DEFAULT);
  bluetoothout = true;
	blisten(1, blueListen);
	printf("crap");
  bool autolift = false;
  taskRunLoop(displaysensordata, 2000);
	while (1) {
   printf("%d | %d | %d\n", analogRead(7), ultrasonicGet(liftUS), encoderGet(liftEnc));
    motorSet(1, claw);
    if (!autolift) {
      motorSet(2, liftVal);
      motorSet(3, swingVal);
      motorSet(6, liftVal);
    }

	motorSet(4, (drive + rotate)/downshift);
    	motorSet(7, (-drive + rotate)/downshift);
	motorSet(8, (drive + rotate)/downshift);
	motorSet(9, (-drive + rotate)/downshift);
    !(analogRead(7) > 1234) || joystickGetDigital(1, 5, JOY_DOWN)?motorSet(10, mogoVal_actual):motorSet(10, abs(mogoVal_actual)/4);
    if (grabButton) {
       if(autoGrabTH != NULL) {
          if (taskGetState(autoGrabTH) == TASK_SUSPENDED) {
            taskResume(autoGrabTH);
          }
        } else {
            autoGrabTH = taskCreate(autoGrab, TASK_DEFAULT_STACK_SIZE, NULL,
               TASK_PRIORITY_DEFAULT);

        }
      }
      if (joystickGetDigital('2','8',JOY_RIGHT)) {

        //TODO make a method for this
        if (liftTH != NULL) {
          if (taskGetState(liftTH) == TASK_SUSPENDED) {
            autolift = true;
            taskResume(liftTH);
            taskResume(swingTH);
          } else {
            autolift = false;
            liftControl.exec = false;
            swingControl.exec = false;
            taskSuspend(liftTH);
            taskSuspend(swingTH);
          }
          while(joystickGetDigital('2','8',JOY_RIGHT)) {};
        }
      }
    delay(20);
	}
}
