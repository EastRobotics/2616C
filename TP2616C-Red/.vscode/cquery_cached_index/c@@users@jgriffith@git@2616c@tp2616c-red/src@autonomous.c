#include "main.h"

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
 #define MOTOR_DRIVE_FRONT_RIGHT 3
#define MOTOR_DRIVE_FRONT_LEFT 14
#define MOTOR_DRIVE_BACK_RIGHT 11
#define MOTOR_DRIVE_BACK_LEFT 12
#define MOTOR_INTAKE 13
#define MOTOR_INDEXER 2
#define MOTOR_FLYWHEEL 1
#define MOTOR_DESCORER 4

#define turn 615
#define forward1 1250
#define backward1 1250
#define forward2 355
#define forward3 350
#define turnf 100
#define forward4 50

void set_motors(int speed) {
  motor_move(MOTOR_DRIVE_FRONT_LEFT,speed);
  motor_move(MOTOR_DRIVE_FRONT_RIGHT,speed);
  motor_move(MOTOR_DRIVE_BACK_RIGHT,speed);
  motor_move(MOTOR_DRIVE_BACK_LEFT,speed);
}

// Set motor to speed based on distance from `ticks`
void motor_move_p(int motor, int ticks, float p) {
    set_motors(p);
}

// Move to position `ticks` using p for speed
void wait_motor_move_p(int motor, int ticks, float p) {
  while ((ticks-motor_get_position(motor)) > 10) { // 10 = threshold, change to change where stop
    motor_move_p(motor, ticks, p);
    delay(25);
  }
}

void wait_motor_move_p_ac(int motor, int ticks, float p, int actime) {
  int st = millis();
  int  ft = st + actime;
  while ((ticks-motor_get_position(motor)) > 10) { // 10 = threshold, change to change where stop
    motor_move_p(motor, ticks, (millis() > ft )? p : (p<0)?-50:50 );

    delay(20);
  }
}

void wait_motor_move_ac(int motor, int ticks, float p, int actime) {
  int st = millis();
  int  ft = st + actime;
  int sp = (int)motor_get_position(motor);
      printf("ticks - %d pos - %d sp - %d\n\r",ticks,(int)motor_get_position(motor),sp);
  while ((abs(ticks)-abs(((int)motor_get_position(motor))-sp)) > 10) { // 10 = threshold, change to change where stop
    motor_move_p(motor, ticks, (millis() > ft )? p :  (p<0)?-50:50  );
      printf("ticks - %d pos - %d sp - %d\n\r",ticks,(int)motor_get_position(motor),sp);
    delay(20);
  }
}


// Move `ticks` forward from the current position using p for speed
void wait_motor_move_p_rel(int motor, int ticks, float p) {

  wait_motor_move_p(motor, motor_get_position(motor) + ticks, p);
}

void wait_motor_move_rel_ac(int motor, int ticks, float p, int actime) {

  wait_motor_move_p_ac(motor, ticks, p, actime);
}

void autonomous() {
double posit, dest;
  motor_set_reversed(11, 1);
  motor_set_reversed(3, 1);
       motor_move(MOTOR_INTAKE, -127);//intake starts

  wait_motor_move_ac(14, forward1, 127, 200);

  set_motors(0);
  delay(1000);

  wait_motor_move_ac(14, -backward1, -127, 200);
  set_motors(0);

  delay(1000);
  set_motors(0);
}
