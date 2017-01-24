typedef struct {
	int angularCurrent;
	int angularDestination;
	int transitionalDestination;
	int transitionalCurrent;
	int speed;
	int directionalCoefficient;
} driveParams;
// driveParams //
typedef struct {
	int transitionalVectorX;
	int transitionalVectorY;
	int rotationalVector;
} driveValues;
driveValues speeds;
bool vectordrive = true;
void turnToHeading(float heading, int speed, float tolerance) {
	float angleDifference; // error
	angleDifference = gyro_angle - heading;
	while(fabs(angleDifference) > tolerance) {
		//writeDebugStreamLine("Gyro: %f | %f", gyro_angle, angleDifference); // print gyro angle in debug
		angleDifference = gyro_angle - heading;
		if(BR == 0) {
			if(angleDifference < 0) {
				speeds.rotationalVector = -speed;
				} else {
				speeds.rotationalVector = speed;
			}
		}
	}
	speeds.rotationalVector = 0;
}
task driveWithController() {
	while(true) {
		switch(vectordrive) {
		case true:
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
task drive() {
	while(true) {
		FR = -speeds.transitionalVectorY + speeds.rotationalVector + speeds.transitionalVectorX;
		BR =  speeds.transitionalVectorY - speeds.rotationalVector + speeds.transitionalVectorX;
		FL = speeds.transitionalVectorY + speeds.rotationalVector + speeds.transitionalVectorX;
		BL =  -speeds.transitionalVectorY - speeds.rotationalVector + speeds.transitionalVectorX;
	//	writeDebugStreamLine("FR %i | BR %i | FL %i | BL %i", FR, BR, FL, BL);
	}
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
