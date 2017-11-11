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

#include <main.h>

 void operatorControl() {
   printf("%s\n", "fuck it");
   taskCreate(driveControl, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);
   taskCreate(liftControl, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);
   while (1) {
     printf("%s\n", "Shit");
		delay(20);
	}
}
