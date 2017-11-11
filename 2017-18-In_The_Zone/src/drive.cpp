#include <main.h>
#include <GeneralRobotics/Wheel.h>

#define Y joystickGetAnalog(1, 3)
#define R joystickGetAnalog(1, 1)
#define X joystickGetAnalog(1, 4)
#define drive threshold(Y)
#define strafe threshold(X)
#define rotate threshold(R)
/* Block of general shorthand definitions */


void driveControl(void *ignore) {
  Wheel wheels[4];
  wheels[0] = *new Wheel(4); // Create wheel object for anterior dexter,
  wheels[1] = *new Wheel(7); // anterior sinister,
  wheels[2] = *new Wheel(9); // posterior sinister,
  wheels[3] = *new Wheel(3); // and posterior dexter mekanum wheels.
  while (1) {
    printf("%s\n", "Hello");
    wheels[0].setValue(drive - strafe + rotate);
    wheels[3].setValue(drive + strafe + rotate);
    wheels[1].setValue(-(drive + strafe - rotate));
    wheels[2].setValue(-(drive - strafe - rotate));
  }
}
