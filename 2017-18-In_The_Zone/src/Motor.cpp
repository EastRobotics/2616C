#include <GeneralRobotics.h>
int GeneralRobotics::Motor::getPortNumber() {
  return this->port_number;
}

int GeneralRobotics::Motor::getValue() {
  return this->pwm_value;
};

void GeneralRobotics::Motor::setValue(int value) {
  this->pwm_value = value;
};
