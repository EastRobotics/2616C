typedef struct {
	int Y1;
	int X2;
	int X1;
} drivestruct;
drivestruct drive1;

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
		if(vexRT[Btn6U]) {
			lift1.tolerance =200;
			lift1.desiredPos = CoG;

			while(vexRT[Btn6U]) {
			}
		}
		if(vexRT[Btn6D]) {
			lift1.tolerance =300;
			lift1.desiredPos = min;
			while(vexRT[Btn6D]) {
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
