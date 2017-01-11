#pragma config(Sensor, in1,    clawManiple,    sensorPotentiometer)
#pragma config(Sensor, dgtl1,  clawClose,      sensorTouch)
#pragma config(Sensor, dgtl2,  encoderI,       sensorQuadEncoder)
#pragma config(Motor,  port1,           leftrear,      tmotorVex393_HBridge, openLoop, driveLeft)
#pragma config(Motor,  port2,           liftLT,        tmotorVex393_MC29, openLoop, driveLeft)
#pragma config(Motor,  port3,           liftLB,        tmotorVex393_MC29, openLoop, driveLeft)
#pragma config(Motor,  port4,           leftfront,     tmotorVex393_MC29, openLoop, driveLeft)
#pragma config(Motor,  port5,           clawL,         tmotorVex393_MC29, openLoop, driveLeft)
#pragma config(Motor,  port6,           clawR,         tmotorVex393_MC29, openLoop, reversed, driveRight)
#pragma config(Motor,  port7,           rightfront,    tmotorVex393_MC29, openLoop, driveRight)
#pragma config(Motor,  port8,           liftRT,        tmotorVex393_MC29, openLoop, reversed, driveRight)
#pragma config(Motor,  port9,           liftRB,        tmotorVex393_MC29, openLoop, reversed, driveRight)
#pragma config(Motor,  port10,          rightrear,     tmotorVex393_HBridge, openLoop, driveRight)
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
#define closed 1200
#include "behaviours.c"
bool vectordrive = true;
task Drive() {
	int X2 = 0, Y1 = 0, X1 = 0;
    while(true) {
        switch(vectordrive) {
        case true:

            Y1 = vexRT[Ch3];
            X1 = vexRT[Ch4];
            X2 = vexRT[Ch1];
	            FR = -Y1 + X2 + X1;
							BR =  Y1 - X2 + X1;
							FL = Y1 + X2 + X1;
							BL =  -Y1 - X2 + X1;
            if(vexRT[Btn8D]){
                vectordrive = false;
            }
            break;
        case false:

                 break;
        }
    }
}
task clawArm() {
    while(true){
        switch(vexRT[Btn6U]) {
        case 1:
        		lift = -127;
            while(vexRT[Btn6U]) {

            }
            break;
        case 0:
            lift = 0;
            break;
        }

        switch(vexRT[Btn6D]) {
        case 1:
            lift = 127;
            while(vexRT[Btn6D]) {

            }
            break;
        case 0:
        lift = 0;
            break;
        }
    }
}
task clawGrasp() {
    while(true) {
    	  writeDebugStreamLine("Claw = %d",SensorValue[clawManiple]);
        switch(vexRT[Btn5U]) {
        case 1:
            claw = -127;
            while(vexRT[Btn5U]){

            }
        case 0:
            claw = 0;
        }

        switch(vexRT[Btn5D]) {
        case 1:
            claw = 127;
            while(vexRT[Btn5D]){

            }
            break;
        case 0:
            claw = 0;
            break;
        }
    }
}

void pre_auton() {
    bStopTasksBetweenModes = true;
   // SensorValue[clawManiple] = 0;
}

task autonomous() {
	startTask(clawPos);
	claw1.tolerance = 120;
      claw1.speed = 40;
      claw1.desiredPos = 2350;
      wait1Msec(100);
      lift = -63;
      wait1Msec(1500);
      int Y1 = 0;
            int X1 = vexRT[Ch4];
            int X2 = 63;
	            FR = -Y1 + X2 + X1;
							BR =  Y1 - X2 + X1;
							FL = Y1 + X2 + X1;
							BL =  -Y1 - X2 + X1;
							Wait1Msec(3000);
							 Y1 = 127;
            	 X1 = vexRT[Ch4];
            	 X2 = vexRT[Ch1];
FR = -Y1 + X2 + X1;
							BR =  Y1 - X2 + X1;
							FL = Y1 + X2 + X1;
							BL =  -Y1 - X2 + X1;




}
task usercontrol() {
    startTask(Drive);
    startTask(clawArm);
 //   startTask(clawGrasp);
claw1.tolerance = 120;
      claw1.speed = 110;
      startTask(clawPos)
	startTask(macroSelection);
	startTask(incDecTolerance);
	while(1==1){

	}
	}