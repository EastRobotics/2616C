#include "main.h"
#include "string.h"


void initLiftData(void) {
  liftControl.mtrPort[0] = 2;
  liftControl.mtrPort[1] = 6;
  liftControl.speed = 127;
  liftControl.encLimit = 80;
  liftControl.timeout = 5000;
  liftControl.exec = false;
  liftControl.coneDetectThreshold = 22;
  liftControl.autostack = false;
}
void initSwingData(){
  swingControl.mtrPort = 3;
  swingControl.speed = -53;
  swingControl.encLimit = 240;
  swingControl.liftSwingOutEncMin = 220;
}
void setLiftMotors(void ){
  for (int m = 0; m < liftPortCount; m++) {
    motorSet(liftControl.mtrPort[m], -liftControl.speed);
  }
}

void stopLiftMotors(void ){
  for (int m = 0; m < liftPortCount; m++) {
    motorSet(liftControl.mtrPort[m], 0);
  }
}
void lift(void *ignore) { // Lift task function
  while (1) {
    if (liftControl.exec) {
      if (liftControl.autostack) {
        if (liftControl.coneDetectThreshold > ultrasonicGet(liftUS) &&
            encoderGet(liftEnc) >= liftControl.encLimit) {
          setLiftMotors();

        } else {
          stopLiftMotors();
        }
        strncpy(liftControl.message, "Auto Stack", 10);
      } else {
        if (motorGet(liftControl.mtrPort[0]) == 0) {
          //  for (int m = 0; m < liftPortCount; m++) {
          //    motorSet(liftControl.mtrPort[m], -liftControl.speed);
          setLiftMotors();
          //    fprintf(uart1,"Set %d\n\r", m);
          //  }
        }
        if (encoderGet(liftEnc) >= liftControl.encLimit) {
          for (int m = 0; m < liftPortCount; m++) {
            motorSet(liftControl.mtrPort[m], 0);
            liftControl.exec = false;
            strncpy(liftControl.message, "Hit Encoder Limit", 17);
          }
        }
        if ((encoderGet(liftEnc)) >= liftControl.encDesiredPos) {
          for (int m = 0; m < liftPortCount; m++) {
            motorSet(liftControl.mtrPort[m], 0);
            liftControl.exec = false;
            strncpy(liftControl.message, "Hit Desired", 11);
          }
        }
      }
       imeGet(0, &liftControl.encActualPos);
    }
      fprintf(uart1, "Message: %s\n", liftControl.message);

      delay(200);

  }
}

void swing(void* ignore) {
  while (1) {
    if (swingControl.exec) {
      while (encoderGet(liftEnc) <= swingControl.liftSwingOutEncMin) {
      }
      if (motorGet(swingControl.mtrPort) == 0) {
          motorSet(swingControl.mtrPort, -swingControl.speed);
      }
      if (encoderGet(swingEnc) >= swingControl.encLimit) {
          motorSet(swingControl.mtrPort, 0);
          swingControl.exec = false;
          strncpy(swingControl.message, "Hit Encoder Limit", 17);
      }
      if ((encoderGet(swingEnc)) <= swingControl.desiredPos) {
          motorSet(swingControl.mtrPort, 0);
          swingControl.exec = false;
          strncpy(swingControl.message, "Hit Desired", 11);
      }
    }
      swingControl.actualPos = encoderGet(swingEnc);

      delay(50);
  }
}
void autoGrab(void *ignore) {
  motorSet(8, -127);
  while(digitalRead(CLAW_LIMIT) == HIGH){}
  motorSet(8,0);
  liftControl.encDesiredPos = 290;
  liftControl.exec = true;
  swingControl.desiredPos = 0;
  swingControl.exec = true;
  while(encoderGet(swingEnc) >= swingControl.desiredPos + 25) {}
  delay(350);
  motorSet(8, 127);
  delay(200);
  motorSet(8, 0);
  fprintf(uart1, "%s %d", liftControl.exec ? "True":"False", liftControl.encDesiredPos);
  taskDelete(NULL);
}

void lifttostack(){


}
