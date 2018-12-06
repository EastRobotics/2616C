// bool  gyro_valid = false;
// float gyro_angle;
// void runGyro(void *ignore) {
// 	// int realBias;
// 	int value;
// 	float angle;
// 	float offsetAngle;
// 	int f = 0;
// 	lcdSetBacklight(uart1, false);
//   // realBias = SensorBias[gyro];
// 	// SensorBias[gyro] = SensorBias[gyro] - 1000;
//
// 	delay(1000);
// 	offsetAngle =  gyroGet();
// 	while(true){
// 		value = SensorValue[gyro];
//
// 		// Create float angle, remove offset
// 		angle = (value - offsetAngle) / 10.0;
//
// 		// normalize into the range 0 - 360
// 		//if( angle < 0 )
// 		//	angle += 360;
//
// 		// put in global for display
// 		gyro_angle = angle;
//
// 		// We can use the angle
// 		gyro_valid = true;
//
// 		// Delay
//
// 		wait1Msec(100);
// 		//writeDebugStreamLine("Angle %f | %i", gyro_angle, f++);
// 	}
// }
