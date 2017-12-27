
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
task drive() {
	while(true) {
		FR = -speeds.transitionalVectorY + speeds.rotationalVector;
		BR =  speeds.transitionalVectorY - speeds.rotationalVector;
		FL = speeds.transitionalVectorY + speeds.rotationalVector;
		BL =  -speeds.transitionalVectorY - speeds.rotationalVector;
	//	writeDebugStreamLine("FR %i | BR %i | FL %i | BL %i", FR, BR, FL, BL);
	}
}
