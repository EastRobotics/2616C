#include <main.h>

#define Y joystickGetAnalog(1, 3)
#define R joystickGetAnalog(1, 1)
#define X joystickGetAnalog(1, 4)
#define drive threshold(Y)
#define strafe threshold(X)
#define rotate threshold(R)
/* Block of general shorthand definitions */


void driveControl(void *ignore) {
  while (1) {
    printf("%s\n", "Hello");
    motorSet(4, drive - strafe + rotate);
    motorSet(3, drive + strafe + rotate);
    motorSet(7, -(drive + strafe - rotate));
    motorSet(9, -(drive - strafe - rotate));
  }
}
