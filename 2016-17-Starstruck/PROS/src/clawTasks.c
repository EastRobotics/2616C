#include "main.h"
int lastPosition;
bool lastBtn5U;
int tolerance = 5;
int currentEncoder;
void clawControl(void* ignore) {
  encoderReset(encClaw);
  while(1) {
    printf("Outer %d %d %d %d\n",encoderGet(encClaw),currentEncoder,lastPosition,abs(currentEncoder - lastPosition) > tolerance);
    currentEncoder = encoderGet(encClaw);
currentEncoder = encoderGet(encClaw);
    if(joystickGetDigital(1, 5, JOY_UP)) {
      runClaw(90);
      lastBtn5U = true;
      lastPosition = encoderGet(encClaw);
      printf("LP : %d\n", lastPosition);
    } else if(joystickGetDigital(1, 5, JOY_DOWN)) {
      printf("CL : %d\n", encoderGet(encClaw));
      runClaw(-90);
      lastBtn5U = false;
    } else {
      if(lastBtn5U) {
        currentEncoder = encoderGet(encClaw);
        printf("%d\n",currentEncoder -lastPosition);
        while((abs(currentEncoder - lastPosition) > tolerance))
        { // && (!joystickGetDigital(1, 5, JOY_UP)&& !joystickGetDigital(1, 5, JOY_DOWN))) {
  //        lastBtn5U = joystickGetDigital(1,5,JOY_UP)?true:false;
          printf("In while\n");
          int speed = currentEncoder - lastPosition > tolerance ? -30 : (currentEncoder - lastPosition < tolerance ? 30 : 0);
          runClaw(speed);
          currentEncoder = encoderGet(encClaw);
          printf("%d\n",currentEncoder - lastPosition);
      }  runClaw(0);}
    //  printf("%s\n", );
    }

  }

}
void runClaw(int speed) {

  motorSet(mClaw_L, speed);
  motorSet(mClaw_R, -speed);
}
