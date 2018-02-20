/** @file auto.c
 * @brief File for autonomous code
 *
 * This file should contain the user autonomous() function and any functions related to it.
 *
 * Any copyright is dedicated to the Public Domain.
 * http://creativecommons.org/publicdomain/zero/1.0/
 *
 * PROS contains FreeRTOS (http://www.freertos.org) whose source code may be
 * obtained from http://sourceforge.net/projects/freertos/files/ or on request.
 */

#include "main.h"

/*
 * Runs the user autonomous code. This function will be started in its own task with the default
 * priority and stack size whenever the robot is enabled via the Field Management System or the
 * VEX Competition Switch in the autonomous mode. If the robot is disabled or communications is
 * lost,  the autonomous task will be stopped by the kernel. Re-enabling the robot will restart
 * the task, not re-start it from where it left off.
 *
 * Code running in the autonomous task cannot access information from the VEX Joystick. However,
 * the autonomous function can be invoked from another task if a VEX Competition Switch is not
 * available, and it can access joystick information if called in this way.
 *
 * The autonomous task may exit, unlike operatorControl() which should never exit. If it does
 * so, the robot will await a switch to another mode or disable/enable cycle.
 */
#define WHEEL_RADIUS 2
int motorPorts[4] = {4, 8, 7, 9};
typedef struct {
    int speed;
    int desiredAngle;
    int currentAngle;
    int error;
    int allowedError;
} MogoMove;

GyroMove gyroVals;
void initGyroVals(void *ignore) {
    gyroVals.speed = 63;
    gyroVals.desiredTheta = 0;
    gyroVals.threshold = 3;
    while(true) {
        gyroVals.currentTheta = gyroGet(gyROH);
        gyroVals.error = gyroVals.desiredTheta - gyroVals.currentTheta;
        gyroVals.speed = gyroVals.speed * (abs(gyroVals.error + 1)/(gyroVals.error + 1));
    }
}

void rotateDeg(int degrees) {
    gyroVals.desiredTheta += degrees;
     for (int i = 0; i < 4; i++) {
      motorSet(motorPorts[i], -gyroVals.speed);
    }
    while(abs(gyroVals.error) > gyroVals.threshold) {};
     for (int i = 0; i < 4; i++) {
      motorSet(motorPorts[i], 0);
    }
}

void drive(int duration, int speed) {
    motorSet(4, speed);
    motorSet(7, -speed);
    motorSet(8, speed);
    motorSet(9, -speed);
    delay(duration);
    for (int i = 0; i < 4; i++) {
      motorSet(motorPorts[i], 0);
    }
}
void driveDistance(int distance, int speed) {
  motorSet(4, speed);
  motorSet(8, speed);
  motorSet(7, -speed);
  motorSet(9, -speed);
  while(((encoderGet(leftDrive) + encoderGet(rightDrive))/2) * WHEEL_RADIUS * 2 < distance) {};
}

void mogoOpen() {
    motorSet(10, 127);
    delay(1750);
    motorSet(10, 0);
}

void mogoClose() {
    motorSet(10, -127);
    while(analogRead(7) < 1200) {};
    motorSet(10, 0);
}

void autonomous() {

  /*
  taskCreate(initGyroVals, TASK_DEFAULT_STACK_SIZE, NULL,
           TASK_PRIORITY_DEFAULT);
           */
  for (int m = 0; m < liftPortCount; m++) {
    motorSet(liftControl.mtrPort[m], 127);
  }
    delay(300);
    stopLiftMotors();
    mogoOpen();

    drive(1500, -127);
    rotateDeg(45);
    drive(500, 127);
    
    mogoClose();
    drive(500, -127);
    openClaw();
    rotateDeg(-45);
    
/*
    rotateDeg(180);

    drive(2000, 127);

    mogoOpen();

    drive(500, 127);
    drive(1000, -127);
*/
}
