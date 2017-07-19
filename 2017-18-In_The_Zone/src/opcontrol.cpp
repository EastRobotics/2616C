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
#include <../src/GeneralRobotics/Wheel.h>
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
 #define Y1 joystickGetAnalog('1', '3')
 #define X1 joystickGetAnalog('1', '1')
 #define X2 joystickGetAnalog('1', '4')
 #define aY1 abs(Y1)
 #define aX1 abs(X1)
 #define aX2 abs(X2)
void operatorControl() {
	Wheel *FL = new Wheel(5);
  // FrontLeft is v_2
	Wheel *FR = new Wheel(4);
  // FrontRight is v_1
	Wheel *BL = new Wheel(3);
  // BackLeft is v_3
	Wheel *BR = new Wheel(2);
  Wheel wheels[4];
  wheels[0] = *FR;
  wheels[1] = *FL;
  wheels[2] = *BL;
  wheels[3] = *BR;
  // BackRight is v_4
	while (1) {
    if (aX1 > 24) {
        for (size_t i = 0; i < sizeof(wheels)/sizeof(*wheels); i++) {
          wheels[i].setVector('w', X1);
        }
    } else {
      for (size_t i = 0; i < sizeof(wheels)/sizeof(*wheels); i++) {
        wheels[i].setVector('w', 0);
      }
    }
    if (aY1 > 24) {
      for (size_t i = 0; i < sizeof(wheels)/sizeof(*wheels); i++) {
        wheels[i].setVector('y', Y1);
      }
    } else {
      for (size_t i = 0; i < sizeof(wheels)/sizeof(*wheels); i++) {
        wheels[i].setVector('y', 0);
      }
    }
    if(aX2 > 24) {
      for (size_t i = 0; i < sizeof(wheels)/sizeof(*wheels); i++) {
        wheels[i].setVector('x', X2);
      }
    } else {
      for (size_t i = 0; i < sizeof(wheels)/sizeof(*wheels); i++) {
        wheels[i].setVector('x', 0);
      }
    }
	}
}
// if(abs(joystickGetAnalog('1', '1')) > 24 &&  abs(joystickGetAnalog('1','3')) > 24) {
// 	FR -> setValue(Y1 - X2 + X1);
// 	BR -> setValue(Y1 + X2 + X1);
// 	FL -> setValue(Y1 + X2 + X1);
// 	BL -> setValue(Y1 - X2 - X1);
// } else if(abs(joystickGetAnalog('1', '1')) > 24) {
// 	FR -> setValue(Y1 - X2 + X1);
// 	BR -> setValue(Y1 + X2 + X1);
// 	FL -> setValue(Y1 + X2 + X1);
// 	BL -> setValue(Y1 - X2 - X1);
// } else if(abs(joystickGetAnalog('1', '3')) > 24) {
// 	FR -> setValue(Y1 - X2 + X1);
// 	FL -> setValue(Y1 + X2 + X1);
//   BR -> setValue(Y1 + X2 + X1);
// 	BL -> setValue(Y1 - X2 - X1);
// } else {
// 	FR -> setValue(0);
// 	BR -> setValue(0);
// 	FL -> setValue(0);
// 	BL -> setValue(0);
//
// }
