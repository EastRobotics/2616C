/** @file init.c
 * @brief File for initialization code
 *
 * This file should contain the user initialize() function and any functions related to it.
 *
 * Any copyright is dedicated to the Public Domain.
 * http://creativecommons.org/publicdomain/zero/1.0/
 *
 * PROS contains FreeRTOS (http://www.freertos.org) whose source code may be
 * obtained from http://sourceforge.net/projects/freertos/files/ or on request.
 */

#include "main.h"

FILE *LCD = uart1;
Encoder getEncoderOdomY() {return encOdomY;}
Encoder getEncoderClaw() { return encClaw;}
void initializeIO() {
}

/*
 * Runs user initialization code. This function will be started in its own task with the default
 * priority and stack size once when the robot is starting up. It is possible that the VEXnet
 * communication link may not be fully established at this time, so reading from the VEX
 * Joystick may fail.
 *
 * This function should initialize most sensors (gyro, encoders, ultrasonics), LCDs, global
 * variables, and IMEs.
 *
 * This function must exit relatively promptly, or the operatorControl() and autonomous() tasks
 * will not start. An autonomous mode selection menu like the pre_auton() in other environments
 * can be implemented in this task if desired.
 */
void initialize() {
  //
  // lcdClear(uart1);
  // lcdInit(uart1);
  // lcdSetBacklight(uart1, true);
  // lcdSetBacklight(uart1, false);
  initLCDFromLCDc();
  speakerInit();
  gyro = gyroInit(aGyroscope, 0);
  encClaw = encoderInit(dClawEncoder_TOP, dClawEncoder_BOT, false);
  encOdomY = encoderInit(dOdomEncoder_YT, dOdomEncoder_YL, false);
  speakerPlayRtttl("LiftBeep: d=32,o=5,b=108: d");
}
