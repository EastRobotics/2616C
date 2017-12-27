#include <GeneralRobotics/Wheel.h>
struct sAutoMove {
  float flHeading;
  /* This is a variable used to contain the difference between the polar origin
   * and angular value normally referred to as ϴ (theta).
   */
  int iMagnitude;
  /* This is a variable used to contain the base speed, the PWM value at which
   * the robot will use as its base for kinematics calculations and vector
   * movement (usually somewhere between 127 and 100) this number should be as
   * high as possible in most cases because when moving upon a vector the
   * component vectors are the base times sin(ϴ) and the base times cos(ϴ).
   */
  int iDistance;
  /* This is the variable to hold the magnitude of the displacement vector
   *
   */
};
struct sRawMove {
  float flHeading;

  int iMagnitude;

  int iDistance;
};
class DriveSystem {
  Wheel *FR;
  Wheel *FL;
  Wheel *BL;
  Wheel *BR;
public:
  void move() {

  }
  void move(struct autoMove *s) {

  }
};
