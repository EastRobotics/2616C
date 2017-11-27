#include <main.h>
#define Y joystickGetAnalog(1, 3)
#define R joystickGetAnalog(1, 1)
#define X joystickGetAnalog(1, 4)

#define drive threshold(Y)
#define strafe threshold(X)
#define rotate threshold(R)

/* Block of general shorthand definitions */
