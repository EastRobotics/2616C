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
int motorPorts[4] = {3, 4, 7, 9};
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
    while(true) {
        gyroVals.currentTheta = gyroGet(gyROH);
        gyroVals.error = gyroVals.desiredTheta - gyroVals.currentTheta;
        gyroVals.speed = gyroVals.speed * (abs(gyroVals.error + 1)/(gyroVals.error + 1));
    }
}

void rotateDeg(int degrees) {
    gyroVals.desiredTheta += degrees;
     for (int i = 0; i < 4; i++) {
      motorSet(motorPorts[i], gyroVals.speed);
    }
    while(gyroVals.error > gyroVals.threshold) {};
     for (int i = 0; i < 4; i++) {
      motorSet(motorPorts[i], 0);
    }

}

void drive(int duration, int speed) {
    motorSet(3, speed);
    motorSet(4, speed);
    motorSet(7, -speed);
    motorSet(9, -speed);
    delay(duration);
    for (int i = 0; i < 4; i++) {
      motorSet(motorPorts[i], 0);
    }
}

void mogoOpen() {
    motorSet(2, 127);
    while(encoderGet(mogoEnc) < 60) {};
    motorSet(2, 0);
}
void mogoClose() {
    motorSet(2, -127);
    while(encoderGet(mogoEnc) > 0) {};
    motorSet(2, 0);
    motorSet(8, 127);
    delay(200);
    motorSet(8,0);
}
void autonomous() {
  for (int m = 0; m < liftPortCount; m++) {
    motorSet(liftControl.mtrPort[m], -127);
  }
    while(encoderGet(liftEnc) < 500) {};
    stopLiftMotors();
    mogoOpen();

    drive(1500, 127);

    mogoClose();
    for (int i = 0; i < 4; i++) {
      motorSet(motorPorts[i], 127);
    }
    while(gyroGet(gyROH) > -135) {};
    for (int i = 0; i < 4; i++) {
      motorSet(motorPorts[i], 0);
    }
    drive(1500, 127);

    mogoOpen();
    drive(500, 127);
    drive(500, -127);

}
