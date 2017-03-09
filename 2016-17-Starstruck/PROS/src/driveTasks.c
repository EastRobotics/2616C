#include "main.h"

void driveControl(void *ignore) {
  while(1) {
  if(abs(joystickGetAnalog('1', '1')) > 24 &&  abs(joystickGetAnalog('1','3')) > 24) {
      r = joystickGetAnalog('1', '1');
      y = joystickGetAnalog('1', '3');
    } else if(abs(joystickGetAnalog('1', '1')) > 24) {
        r = joystickGetAnalog('1', '1');
        y = 0;
    } else if(abs(joystickGetAnalog('1', '3')) > 24) {
        y = joystickGetAnalog('1', '3');
        r = 0;
    } else {
      y = r = 0;
    }
  }
}
void runDrive(void* ignore) {
  while(1) {
    motorSet(mDriveFR, y - r);
    motorSet(mDriveBR, -y + r);
    motorSet(mDriveFL, y + r);
    motorSet(mDriveBL, -y - r);
  }
}
void moveToPosition(float position) {
  refreshBotLocation(&botLoc);
  if(position / -1 == 1) {
    y = -63;
    while(botLoc.y_pos > position) {
      refreshBotLocation(&botLoc);
    }
    y=0;
  } else {
    y=63;
    while(botLoc.y_pos < position) {
      refreshBotLocation(&botLoc);
    }
    y = 0;
  }
}
// void turnToHeading(float heading, int speed, float tolerance) {
// 	float angleDifference; // error
// 	angleDifference = gyro_angle - heading;
// 	while(abs(angleDifference) > tolerance) {
// 		//writeDebugStreamLine("Gyro: %f | %f", gyro_angle, angleDifference); // print gyro angle in debug
// 		angleDifference = gyro_angle - heading;
// 		if(motorGet(mDriveBR) == 0) {
// 			if(angleDifference < 0) {
// 				r = -speed;
// 				} else {
// 				r = speed;
// 			}
// 		}
// 	}
// 	r = 0;
// }
