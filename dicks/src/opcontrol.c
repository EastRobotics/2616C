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
#define mogoVal_actual threshold(mogoVal)

#define Y joystickGetAnalog(1, 3)
#define R joystickGetAnalog(1, 1)
#define X joystickGetAnalog(1, 4)
#define slaveR joystickGetAnalog(2, 1)
#define drive threshold(Y)
#define strafe threshold(X)
#define rotate threshold(R)
#define rotateSlave threshold(slaveR)


void operatorControl() {
	printf("crap");
	int downshift = 1;
	bool lastButton6D = 0;
	bool lastButton6U = 0;
	while (1) {
		motorSet(2, mogoVal_actual);
		motorSet(3, (drive + rotate)/downshift);
		motorSet(4, (drive + rotate)/downshift);
		motorSet(5, lift)
		motorSet(6, liftM)			
		motorSet(7, (-drive + rotate)/downshift);
		motorSet(8, claw)
		motorSet(9, (-drive + rotate)/downshift);
		
		
		printf("%d\n", 127/downshift);
		if(joystickGetDigital(1, 6, JOY_DOWN)) {
			if(lastButton6D & joystickGetDigital(1, 6, JOY_DOWN)) {
				downshift = 3;
			}
			lastButton6D = joystickGetDigital(1, 6, JOY_DOWN);
		}
		if(joystickGetDigital(1, 6, JOY_UP)) {
			if(lastButton6U & joystickGetDigital(1, 6, JOY_UP)) {
				downshift = 1;
			}
			lastButton6U = joystickGetDigital(1, 6, JOY_UP);
		}
	}
}
