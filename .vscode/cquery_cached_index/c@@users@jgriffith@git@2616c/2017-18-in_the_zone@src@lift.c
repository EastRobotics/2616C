#include <main.h>
#define liftVal joystickGetAnalog(2,2)
#define liftVal_actual threshold(liftVal)
#define swingUp joystickGetDigital(2,6, JOY_UP)
#define swingDown joystickGetDigital(2,6, JOY_DOWN)
void liftControl(void *ignore) {
  while (true) {
      motorSet(6, liftVal_actual);
      motorSet(5, liftVal_actual);
      printf("%d\n", swingUp);
  }
}
//
// void swingControl(void *ignore) {
//   while(true) {
//     switch(swingUp) {
//         case 1:
//         motorSet(10, 63);
//           while(swingUp) {
//
//           }
//         case 0:
//         motorSet(10, 0);
//           break;
//     }
//
//   }
// }
