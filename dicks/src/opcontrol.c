/** @file opcontrol.c
 * @brief File for operator control code
 *
 * This file should contain the user operatorControl() function and any functions related to it.
 *
 * Any copyright is dedicated to the Public Domain.
 * http://creativecommons.org/publicdomain/zero/1.0/
 *
 * PROS contains FreeRTOS (http://www.freertos.org) whose source code may be
 * obtained from http://sourceforge.net/projects/freertos/files/ or on request.
 */

#include "main.h"
#include "string.h"
/*
 * Runs the user operator control code. This function will be started in its own task with the
 * default priority and stack size whenever the robot is enabled via the Field Management System
 * or the VEX Competition Switch in the operator control mode. If the robot is disabled or
 * communications is lost, the operator control task will be stopped by the kernel. Re-enabling
 * the robot will restart the task, not resume it from where it left off.
 *
 * If no VEX Competition Switch or Field Management system is plugged in, the VEX Cortex will
 * run the operator control task. Be warned that this will also occur if the VEX Cortex is
 * tethered directly to a computer via the USB A to A cable without any VEX Joystick attached.
 *
 * Code running in this task can take almost any action, as the VEX Joystick is available and
 * the scheduler is operational. However, proper use of delay() or taskDelayUntil() is highly
 * recommended to give other tasks (including system tasks such as updating LCDs) time to run.
 *
 * This task should never exit; it should end with some kind of infinite loop, even if empty.
 */
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
#define starwars "StarWars: d=4,o=5,b=90: 32p,32f#,32f#,32f#,8b.,8f#.6,32e6,32d#6,32c#6,8b.6,16f#.6,32e6,32d#6,32c#6,8b.6,16f#.6,32e6,32d#6,32e6,8c#.6,32f#,32f#,32f#,8b.,8f#.6,32e6,32d#6,32c#6,8b.6,16f#.6,32e6,32d#6,32c#6,8b.6,16f#.6,32e6,32d#6,32e6,8c#6"
#define tom "TakeOnMe: d=4,o=4,b=190: 8f#5,8f#5,8f#5,8d5,8p,8b,8p,8e5,8p,8e5,8p,8e5,8g#5,8g#5,8a5,8b5,8a5,8a5,8a5,8e5,8p,8d5,8p,8f#5,8p,8f#5,8p,8f#5,8e5,8e5,8f#5,8e5,8f#5,8f#5,8f#5,8d5,8p,8b,8p,8e5,8p,8e5,8p,8e5,8g#5,8g#5,8a5,8b5,8a5,8a5,8a5,8e5,8p,8d5,8p,8f#5,8p,8f#5,8p,8f#5,8e5,8e5"
#define jeopardy "Jeopardy: d=4,o=6,b=160: c,f,c,f5,c,f,2c,c,f,c,f,a.,8g,8f,8e,8d,8c#,c,f,c,f5,c,f,2c,f.,8d,c,a#5,a5,g5,f5,p,d#,g#,d#,g#5,d#,g#,2d#,d#,g#,d#,g#,c.7,8a#,8g#,8g,8f,8e,d#,g#,d#,g#5,d#,g#,2d#,g#.,8f,d#,c#,c,p,a#5,p,g#.5,d#,g#"
TaskHandle swTH;
TaskHandle tomTH;
TaskHandle jprdyTH;
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
void swMusac(void* ignore) {
  speakerPlayRtttl(starwars);
}
void tomMusac(void* ignore) {
  speakerPlayRtttl(tom);
}
void jprdyMusac(void* ignore) {
  speakerPlayRtttl(jeopardy);
}

void blueListen(char * message) {
    fprintf(uart1, "%x %x %x %x %x %x %x %x\r\n", message[0], message[1], message[2], message[3], message[4], message[5], message[6], message[7]);
    //fprintf(uart1, "|%s|\n", message);
    //fprintf(uart1,"%d\n", strcmp(message, "reset\r\n"));
    if (strcmp(message, "reset\r\n") == 0) {
        analogCalibrate(LINE_TRACKER_PORT);
        encoderReset(liftEnc);
        imeReset(0);
        encoderReset(swingEnc);
        encoderReset(mogoEnc);
      //gyroReset(gyro);
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
    if(strncmp(message, "sw\r\n",2) == 0) {
      fprintf(uart1, "Now Playing \'The Imperial March\' by John Williams");
      if (swTH != NULL) {
          taskDelete(swTH);
      }
      speakerShutdown();
      delay(200);
      speakerInit();
      swTH = taskCreate(swMusac, TASK_DEFAULT_STACK_SIZE, NULL,
                 TASK_PRIORITY_DEFAULT);
    }
    if(strncmp(message, "tom\r\n",3) == 0) {
      fprintf(uart1, "Now Playing \'Take on Me\' by a-ha");
      if (tomTH != NULL) {
          taskDelete(tomTH);
      }
      speakerShutdown();
      delay(200);
      speakerInit();
       tomTH = taskCreate(tomMusac, TASK_DEFAULT_STACK_SIZE, NULL,
                  TASK_PRIORITY_DEFAULT);
    }
    if(strncmp(message, "jprdy\r\n",5) == 0){
      fprintf(uart1, "Now Playing the Jeopardy Theme");
      if(jprdyTH != NULL) {
          taskDelete(jprdyTH);
      }
      speakerShutdown();
      delay(200);
      speakerInit();
      jprdyTH = taskCreate(jprdyMusac, TASK_DEFAULT_STACK_SIZE, NULL,
                 TASK_PRIORITY_DEFAULT);
    }
    if (strncmp(message, "ssd\r\n",3) == 0) {
      fprintf(uart1, "Speaker Shutdown Requested");
      if (swTH != NULL) {
          taskDelete(swTH);
      }
      if (tomTH != NULL) {
          taskDelete(tomTH);
      }
      if(jprdyTH != NULL) {
          taskDelete(jprdyTH);
      }
      speakerShutdown();
      delay(200);
      speakerInit();
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
	int downshift = 1;
	bool lastButton6D = false;
	bool lastButton6U = false;
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

      }
       if(autoGrabTH != NULL) {
          if (taskGetState(autoGrabTH) == TASK_SUSPENDED) {
            taskResume(autoGrabTH);
          }
        } else {
            autoGrabTH = taskCreate(autoGrab, TASK_DEFAULT_STACK_SIZE, NULL,
               TASK_PRIORITY_DEFAULT);

        }
        while(joystickGetDigital('2','8',JOY_RIGHT)) {};
      }
		if(joystickGetDigital(1, 6, JOY_DOWN)) {
			if(lastButton6D & joystickGetDigital(1, 6, JOY_DOWN)) {
				downshift = 2;
			}
			lastButton6D = joystickGetDigital(1, 6, JOY_DOWN);
		}
		if(joystickGetDigital(1, 6, JOY_UP)) {
			if(lastButton6U & joystickGetDigital(1, 6, JOY_UP)) {
				downshift = 1;
		}
			lastButton6U = joystickGetDigital(1, 6, JOY_UP);
		}
    delay(20);
	}
}
