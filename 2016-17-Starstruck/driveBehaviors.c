typedef struct {
	int angularCurrent;
	int angularDestination;
	int transitionalDestination;
	int transitionalCurrent;
}driveParams;

task drive() {
	while(true) {
		switch(vectordrive) {
		case true:

			drive1.Y1 = vexRT[Ch3];
			drive1.X1 = vexRT[Ch4];
			drive1.X2 = vexRT[Ch1];
			FR = -drive1.Y1 + drive1.X2 + drive1.X1;
			BR =  drive1.Y1 - drive1.X2 + drive1.X1;
			FL = drive1.Y1 + drive1.X2 + drive1.X1;
			BL =  -drive1.Y1 - drive1.X2 + drive1.X1;
			if(vexRT[Btn8D]){
				vectordrive = false;
			}
			break;
		case false:

			break;
		}
	}
}
void driveRaw() {

}
driveParams strafe(char direction, int speed) {
	switch(direction) {
		case 'L':

		break;
		case 'R':

		break;
	}
}
