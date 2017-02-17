#pragma config(UART_Usage, UART1, uartVEXLCD, baudRate19200, IOPins, None, None)
#pragma config(UART_Usage, UART2, uartNotUsed, baudRate4800, IOPins, None, None)
#pragma config(Sensor, in1,    liftPot,        sensorPotentiometer)
#pragma config(Sensor, in2,    clawManiple,    sensorPotentiometer)
#pragma config(Sensor, in3,    gyro,           sensorGyro)
#pragma config(Sensor, in4,    pExp,           sensorAnalog)
#pragma config(Sensor, dgtl1,  y_quad,         sensorQuadEncoder)
#pragma config(Sensor, dgtl4,  x_quad,         sensorQuadEncoder)
#pragma config(Sensor, dgtl9,  liftlight,      sensorLEDtoVCC)
#pragma config(Sensor, dgtl10, clawlight,      sensorLEDtoVCC)
#pragma config(Motor,  port1,           clawL,         tmotorVex393_HBridge, openLoop)
#pragma config(Motor,  port2,           leftfront,     tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port3,           leftrear,      tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port4,           liftLT,        tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port5,           liftLB,        tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port6,           liftRT,        tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port7,           liftRB,        tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port8,           rightrear,     tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port9,           rightfront,    tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port10,          clawR,         tmotorVex393_HBridge, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

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
string Auton[] = {	"R1","R2","R3","L1","L2","L3"} ;
int wAuton;

#include "Gyro.c"
#include "OdometryMouse.c"
#include "clawBehaviors.c"
BotLocation botLoc;
#include "driveBehaviors.c"
#include "liftBehaviors.c"
#include "behaviours.c"
#include "LCD.c"
// Includes and defines stop, executable code starts



void pre_auton() {
	bDisplayCompetitionStatusOnLcd = false;
	clearDebugStream();
	bStopTasksBetweenModes = false;
	init_odometry(x_quad, y_quad,9.42,360,360,neg,pos);
	startTask(runGyro);
	startTask(drive);
	startTask(clawPos);
	startTask(liftPos);
	startTask(runLCD);
	writeDebugStreamLine("preauton");
}

task autonomous() {
	writeDebugStreamLine("auto");
	claw1.tolerance = 200;
	claw1.speed = 90;
	lift1.tolerance = 200;
	lift1.speed = 100;


	switch (wAuton){
	case 0:
		claw1.desiredPos = wide;
		lift1.desiredPos += 400;
		writeDebugStreamLine("claw started");
		turnToHeading(-45, 60, 3);

		get_botlocation(botLoc);
		moveToPosition(30.00);

		claw1.desiredPos = closed;
		wait1Msec(500);
		lift1.desiredPos = CoG;

		turnToHeading(-180, 60, 3);
		resetOdometry();

		get_botlocation(botLoc);
		moveToPosition(-12.00);

		throwObjects();
		//while(botLoc.x_pos < )
		resetOdometry();
		moveToPosition(24.00);
		break;
	case 1:
			claw1.desiredPos = wide;
			lift1.desiredPos +=400;
			speeds.transitionalVectorY = 63;
			lift1.desiredPos = CoG;
		break;
	case 2:

		break;
	case 3:

	claw1.desiredPos = wide;
		writeDebugStreamLine("claw started");
		turnToHeading(45, 70, 3);
		get_botlocation(botLoc);
		moveToPosition(30.00);
		claw1.desiredPos = closed;
		wait1Msec(500);
		lift1.desiredPos = CoG;
		turnToHeading(180, 70, 3);
		resetOdometry();

		get_botlocation(botLoc);
		moveToPosition(-24.00);

		throwObjects();
		resetOdometry();
		break;
	case 4:
		break;
	default:
		break;
	}
}

task usercontrol() {
	stopTask(drive);
	clawMan = false;
	liftMan = false;
	startTask(driveWithController);
	claw1.tolerance = 200;
	claw1.speed = 90;
	lift1.tolerance = 200;
	lift1.speed = 100;
	startTask(macroSelection);
	startTask(incDecTolerance);
	while(true) {
		get_botlocation(botLoc);
	}
}
