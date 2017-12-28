#include "main.h"
#include "string.h"
#define grabButton joystickGetDigital(2, 7, JOY_UP)
#define liftPortCount 2
typedef struct {
  unsigned char mtrPort[liftPortCount];
  int speed;
  int encActualPos;
  int encDesiredPos;
  int usActualPos;
  int usLimit;
  bool exec;
  int encLimit;
  unsigned int timeout;
  char message[25];
} LiftData;
typedef struct {
  unsigned char mtrPort;
  int speed;
  int actualPos;
  int desiredPos;
  int liftSwingOutEncMin; // minimum value in order for the lift to pass by the mobile goal holder safely
  bool exec;
  unsigned int timeout;
  char message[25];
} SwingData;

LiftData liftControl;
SwingData swingControl;

void initLiftData(void) {
  liftControl.speed = 127;
  liftControl.exec = false;
}

void lift(void *ignore) {   // Lift task function
  int startTime;
  while (1) {

    liftControl.encActualPos = encoderGet(liftEnc);

    if (liftControl.exec) {
      if (motorGet(liftControl.mtrPort[0]) == 0) {
        startTime = millis();
      }
      for (int m = 0; m < liftPortCount; m++) {
        motorSet(liftControl.mtrPort[m], liftControl.speed);
      }
      if (startTime - millis() > (unsigned int) liftControl.timeout) {
        for (int m = 0; m < liftPortCount; m++) {
          motorSet(liftControl.mtrPort[m], 0);
          liftControl.exec = false;
          strncpy(liftControl.message, "Timeout", 7);
        }
      }
      if (encoderGet(liftEnc) >= liftControl.encLimit) {
        for (int m = 0; m < liftPortCount; m++) {
          motorSet(liftControl.mtrPort[m], 0);
          liftControl.exec = false;
          strncpy(liftControl.message, "Hit Encoder Limit", 17);
        }
      }
      if (encoderGet(liftEnc) >= liftControl.encDesiredPos) {
        for (int m = 0; m < liftPortCount; m++) {
          motorSet(liftControl.mtrPort[m], 0);
          liftControl.exec = false;
          strncpy(liftControl.message, "Hit Desired", 11);
        }
      }
    }
  }
}


void swing(void* ignore) {
  while (1) {
    if (swingControl.exec) {

    }
  }
}
void autoGrab(void* ignore) {
    if (grabButton) {
      liftControl.speed = 127;

    }
}
