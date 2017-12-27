#pragma config(Sensor, in1,    liftPot,        sensorPotentiometer)
#pragma config(Sensor, in2,    clawManiple,    sensorPotentiometer)
#pragma config(Sensor, in3,    gyro,           sensorGyro)
#pragma config(Sensor, dgtl1,  y_quad,         sensorQuadEncoder)
#pragma config(Sensor, dgtl4,  x_quad,         sensorQuadEncoder)
#pragma config(Sensor, dgtl9,  liftlight,      sensorLEDtoVCC)
#pragma config(Sensor, dgtl10, clawlight,      sensorLEDtoVCC)
#pragma config(Motor,  port1,           leftrear,      tmotorVex393_HBridge, openLoop, driveLeft)
#pragma config(Motor,  port2,           liftLT,        tmotorVex393_MC29, openLoop, driveLeft)
#pragma config(Motor,  port3,           liftLB,        tmotorVex393_MC29, openLoop, driveLeft)
#pragma config(Motor,  port4,           leftfront,     tmotorVex393_MC29, openLoop, reversed, driveLeft)
#pragma config(Motor,  port5,           clawL,         tmotorVex393_MC29, openLoop, driveLeft)
#pragma config(Motor,  port6,           clawR,         tmotorVex393_MC29, openLoop, reversed, driveRight)
#pragma config(Motor,  port7,           rightfront,    tmotorVex393_MC29, openLoop, reversed, driveRight)
#pragma config(Motor,  port8,           liftRT,        tmotorVex393_MC29, openLoop, reversed, driveRight)
#pragma config(Motor,  port9,           liftRB,        tmotorVex393_MC29, openLoop, reversed, driveRight)
#pragma config(Motor,  port10,          rightrear,     tmotorVex393_HBridge, openLoop, driveRight)
#pragma DebuggerWindows("vexCompetitionControl")
#pragma platform(VEX2)
#pragma competitionControl(Competition)

#include "Vex_Competition_Includes.c"
#define FL motor[leftfront]
#define FR motor[rightfront]
#define BR motor[rightrear]
#define BL motor[leftrear]
#define liftLeft motor[liftLT] = motor[liftLB]
#define liftRight motor[liftRT] = motor[liftRB]
#define lift liftLeft = liftRight
#define claw motor[clawL] = motor[clawR]
#define driveoff BR = BL = FL = FR = 0
#define wide 2350
#define closed 1000
#define min 350
#define CoG 2000
#define liftprethrow 1700
#define liftthrow 2400
#define clawthrow 1700

#include "Gyro.c"
#include "OdometryMouse.c"
#include "clawBehaviors.c"
#include "driveBehaviors.c"
#include "liftBehaviors.c"
#include "behaviours.c"

// Includes and defines stop, executable code starts
BotLocation botLoc;

void pre_auton() {
	clearDebugStream();
	bStopTasksBetweenModes = false;
	init_odometry(x_quad, y_quad,9.42,360,360,neg,neg);
	startTask(runGyro);
	startTask(drive);
	startTask(clawPos);
	startTask(liftPos);
	writeDebugStreamLine("preauton");
}

task autonomous() {
	writeDebugStreamLine("auto");
	claw1.tolerance = 200;
	claw1.speed = 90;
	lift1.tolerance = 200;
	lift1.speed = 100;

	claw1.desiredPos = wide;
	writeDebugStreamLine("claw started");
	turnToHeading(-45, 70, 3);
	get_botlocation(botLoc);
	speeds.transitionalVectorY = 127;
	writeDebugStreamLine("Forward");
	while(botLoc.y_pos < 30.0) {
		get_botlocation(botLoc);
		writeDebugStreamLine("y- %f ", botLoc.y_pos);
	}

	speeds.transitionalVectorY = 0;
	claw1.desiredPos = closed;
	wait1Msec(500);
	lift1.desiredPos = CoG;
	turnToHeading(-180, 70, 3);
	resetOdometry();
	get_botlocation(botLoc);
	speeds.transitionalVectorY = -127;
	while(botLoc.y_pos > -24.0) {
		get_botlocation(botLoc);
		writeDebugStreamLine("y- %f ", botLoc.y_pos);
	}
	speeds.transitionalVectorY = 0;
	throwObjects();
	//while(botLoc.x_pos < )
	resetOdometry();
	speeds.transitionalVectorY = 63;
	wait1Msec(1000);
	speeds.transitionalVectorY = 0;

}

task usercontrol() {
	/*startTask(spin);
	wait1Msec(5000);*/
	startTask(driveWithController);
	//   startTask(clawGrasp);
	claw1.tolerance = 200;
	claw1.speed = 90;
	lift1.tolerance = 200;
	lift1.speed = 100;
	//startTask(clawPos);
	//startTask(liftPos);
	startTask(macroSelection);
	startTask(incDecTolerance);
}
