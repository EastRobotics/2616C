/*typedef struct {
	int angularCurrent;
	int angularDestination;
	int transitionalDestination;
	int transitionalCurrent;
	int speed;
	int directionalCoefficient;
} driveParams;
// driveParams //*/
typedef struct {
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
				speeds.transitionalVectorY = -speed;
				} else {
				speeds.transitionalVectorY = speed;
			}
		}
	}
	speeds.rotationalVector = 0;
}
task driveWithController() {
	while(true) {
		switch(vectordrive) {
		case true:
			speeds.transitionalVectorY = vexRT[Ch1];
			speeds.rotationalVector = vexRT[Ch3];
			FR = -speeds.transitionalVectorY + speeds.rotationalVector;
			BR =  speeds.transitionalVectorY - speeds.rotationalVector;
			FL = speeds.transitionalVectorY + speeds.rotationalVector;
			BL =  -speeds.transitionalVectorY - speeds.rotationalVector;
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
		FR = -speeds.transitionalVectorY + speeds.rotationalVector;
		BR =  speeds.transitionalVectorY - speeds.rotationalVector;
		FL = speeds.transitionalVectorY + speeds.rotationalVector;
		BL =  -speeds.transitionalVectorY - speeds.rotationalVector;
	//	writeDebugStreamLine("FR %i | BR %i | FL %i | BL %i", FR, BR, FL, BL);
	}
}
