#include "main.h"
const int UP_MAX = 127;
const int UP_MED = 70;
const int UP_MIN = 20;
const int DOWN_MAX = -127;
const int DOWN_MED = -70;
const int DOWN_MIN = -20;
bool last6U = false;

void liftControl(void *ignore) {
  while(1) {
    if(joystickGetDigital(1, 6, JOY_UP)) {
      runLift(UP_MAX);
      last6U = true;
      speakerPlayRtttl("LiftBeep: d=32,o=5,b=108: d");
      while(joystickGetDigital(1, 6, JOY_UP)) {}
    } else if(joystickGetDigital(1, 6, JOY_DOWN)) {
      runLift(DOWN_MAX);
      last6U = false;
      while(joystickGetDigital(1, 6, JOY_DOWN)) {}
    } else
    if(last6U){
      runLift(UP_MIN);
    }
    else if(!last6U) {
      runLift(0);
    }
    delay(20);
  }
}

void runLift(int speed) {
  motorSet(mLiftU_L, -speed);
  motorSet(mLiftL_L, -speed);
  motorSet(mLiftL_R, speed);
  motorSet(mLiftU_R, speed);
}
