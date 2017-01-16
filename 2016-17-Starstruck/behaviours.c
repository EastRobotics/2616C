typedef struct {
	int tolerance;
	int desiredPos;
	int currentPos;
	int speed;
	int enabled;
	int difference;
} clawManipulator;
bool clawMan = true;
clawManipulator claw1;
typedef struct {
int Y1;
int X2;
int drive1.X1;
} drivestruct;
drivestruct drive1;

task clawPos() {
	claw1.desiredPos = SensorValue[clawManiple];
	while(true) {
	if(vexRT[Btn7L] && vexRT[Btn8R]) {
		clawMan = !clawMan;
		claw = 0;
	}
	while(vexRT[Btn7L] & vexRT[Btn8R]) {}
	claw1.currentPos = SensorValue[clawManiple];
	claw1.difference = abs(claw1.desiredPos - claw1.currentPos);
	writeDebugStreamLine(" D: %d | C: %d | Diff: %d | S: %d |", claw1.desiredPos, claw1.currentPos, claw1.difference, claw1.speed);
	if(clawMan) {
		if(claw1.difference > claw1.tolerance) {
			if(motor[clawL] == 0){
				claw = ((claw1.desiredPos - claw1.currentPos > 0) ? ( (claw1.difference > 250) ? claw1.speed : claw1.speed/2 ) : ((claw1.difference > 250) ? -claw1.speed : -claw1.speed/2 ));
			}
			} else {
			claw = 0;
		}
	}
	if(!clawMan) {
		if(vexRT[Btn5D]) {
			claw = claw1.speed;
			} else if(vexRT[Btn5U]){
			claw = -claw1.speed;
			} else {
			claw = 0;
		}
	}
	wait1Msec(100);
}
}

task macroSelection() {
	while(true) {
		if(vexRT[Btn5D]) {
			claw1.desiredPos = wide;
			while(vexRT[Btn5D]) {

			}
		}
		if(vexRT[Btn5U]) {
			claw1.desiredPos = closed;
			while(vexRT[Btn5U]) {

			}
		}
		wait1Msec(100);
	}
}
task incDecTolerance() {
	while(true) {
		if(vexRT[Btn7U]) {
			claw1.tolerance +=5;
			while(vexRT[Btn7U]) {}
		}

		if(vexRT[Btn7D]){
			claw1.tolerance -= 5;
			while(vexRT[Btn7D]) {

			}
		}
		wait1Msec(100);
	}
}
void spin(int angle) {
	int gyroInitial = abs(SensorValue[gyro]);
	int gyroDest = gyroInitial + angle;
	int Y1, X2, X1;
		X2 = 90;
		Y1 = X1 = 0;
		FR = -Y1 + X2 + X1;
		BR =  Y1 - X2 + X1;
		FL = Y1 + X2 + X1;
		BL =  -Y1 - X2 + X1;

	while(abs(SensorValue[gyro]) - gyroInitial < gyroInitial + angle) {

	}
	driveoff;
}
