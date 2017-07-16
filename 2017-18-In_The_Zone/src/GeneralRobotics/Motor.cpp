#include "../src/GeneralRobotics/Motor.h"
void Motor::setValue(int speed) {
    motorSet(chnl, speed);
  }

int Motor::getValue() {
  return motorGet(chnl);
}
