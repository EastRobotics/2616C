#include <main.h>

#define mogoVal joystickGetAnalog('2','3')
#define mogoVal_actual threshold(mogoVal)

void mogoControl(void *ignore) {
  while (true) {
      motorSet(2, mogoVal_actual);
      motorSet(8, mogoVal_actual);
  }
}
