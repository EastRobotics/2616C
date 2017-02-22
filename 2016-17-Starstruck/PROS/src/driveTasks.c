#include "main.h"

void driveControl(void *ignore) {
  while(1) {
  if(abs(joystickGetAnalog('1', '1')) > 16 && abs(joystickGetAnalog('1','3'))) {
      int r = joystickGetAnalog('1', '1');
      int y = joystickGetAnalog('1', '3');
      motorSet(mDriveFR, y - r);
      motorSet(mDriveBR, -y + r);
      motorSet(mDriveFL, y + r);
      motorSet(mDriveBL, -y - r);
    } else {
      motorStop(mDriveFR);
      motorStop(mDriveBR);
      motorStop(mDriveFL);
      motorStop(mDriveBL);
    }
  }
}
