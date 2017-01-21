typedef struct {
	int angularCurrent;
	int angularDestination;
	int transitionalDestination;
	int transitionalCurrent;
	int speed;
	int directionalCoefficient;
} driveParams;

typedef struct {
	int transitionalVectorX;
	int transitionalVectorY;
	int rotationalVector;
} driveValues;
bool vectordrive = true;
task drive() {
	while(true) {
		switch(vectordrive) {
		case true:
			driveValues speeds;
			speeds.transitionalVectorY = vexRT[Ch3];
			speeds.transitionalVectorX = vexRT[Ch4];
			speeds.rotationalVector = vexRT[Ch1];
			FR = -speeds.transitionalVectorY + speeds.rotationalVector + speeds.transitionalVectorX;
			BR =  speeds.transitionalVectorY - speeds.rotationalVector + speeds.transitionalVectorX;
			FL = speeds.transitionalVectorY + speeds.rotationalVector + speeds.transitionalVectorX;
			BL =  -speeds.transitionalVectorY - speeds.rotationalVector + speeds.transitionalVectorX;
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
driveValues* strafe(driveParams dP) {
	driveValues dV;
	int direction = dP.directionalCoefficient;
	switch(direction) {
		case 'L':
			dV.transitionalVectorX = 127;
		break;
		case 'R':
			dV.transitionalVectorX = -127;
		break;
	}
	return dV;
}
