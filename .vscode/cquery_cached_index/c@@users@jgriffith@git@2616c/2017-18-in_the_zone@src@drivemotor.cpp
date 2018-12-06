#include <main.h>

GeneralRobotics::DriveMotor::DriveMotor() {
  this->port_number = 0;
}

GeneralRobotics::DriveMotor::DriveMotor(unsigned char channel) {
  this->port_number = channel;
}
