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
//define motors here (#define (name) (port))
#define MOTOR_DRIVE_FRONT_RIGHT 3
#define MOTOR_DRIVE_FRONT_LEFT 14
#define MOTOR_DRIVE_BACK_RIGHT 11
#define MOTOR_DRIVE_BACK_LEFT 12
#define MOTOR_INTAKE 13
#define MOTOR_INDEXER 2
#define MOTOR_FLYWHEEL 1
#define MOTOR_DESCORER 4
#define KF 0
#define KP 1.0f
#define KI 0.001f
#define KD 0.1f

#define turn 840
#define forward1 1250
#define backward1 1050
#define forward2 580
#define forward3 290
#define turnf 180
#define forward4 300
#define STOPTIP 100
#define turnb 100

#define WALLDISTANCE 3
adi_ultrasonic_t ult;

void set_motors(int speed)
{
  motor_move(MOTOR_DRIVE_FRONT_LEFT, speed);
  motor_move(MOTOR_DRIVE_FRONT_RIGHT, speed);
  motor_move(MOTOR_DRIVE_BACK_RIGHT, speed);
  motor_move(MOTOR_DRIVE_BACK_LEFT, speed);
}

// Set motor to speed based on distance from `ticks`
void motor_move_p(int motor, int ticks, float p)
{
  set_motors(p);
}

// Move to position `ticks` using p for speed
void wait_motor_move_p(int motor, int ticks, float p)
{
  while ((ticks - motor_get_position(motor)) > 10)
  { // 10 = threshold, change to change where stop
    motor_move_p(motor, ticks, p);
    delay(25);
  }
}

void wait_motor_move_p_ac(int motor, int ticks, float p, int actime)
{
  int st = millis();
  int ft = st + actime;
  while ((ticks - motor_get_position(motor)) > 10)
  { // 10 = threshold, change to change where stop
    motor_move_p(motor, ticks, (millis() > ft) ? p : (p < 0) ? -50 : 50);

    delay(20);
  }
}

void wait_motor_move_ac(int motor, int ticks, float p, int actime)
{
  int st = millis();
  int ft = st + actime;
  int sp = (int)motor_get_position(motor);
  printf("ticks - %d pos - %d sp - %d\n\r", ticks, (int)motor_get_position(motor), sp);
  while ((abs(ticks) - abs(((int)motor_get_position(motor)) - sp)) > 10)
  { // 10 = threshold, change to change where stop
    motor_move_p(motor, ticks, (millis() > ft) ? p : (p < 0) ? -50 : 50);
    printf("ticks - %d pos - %d sp - %d\n\r", ticks, (int)motor_get_position(motor), sp);
    delay(20);
  }
}

int avgFilter_ult()
{
  int ultout;
  for (int x = 0; x <= 5; x++)
  {
    ultout += adi_ultrasonic_get(ult);
    delay(25);
  }
  return (ultout / 5);
}

extern int accelZ_init;

void wait_motor_move_ac_ust(int motor, int ticks, float p, int actime)
{

  int st = millis();
  int ft = st + actime;
  adi_port_set_config('A', E_ADI_DIGITAL_IN);

  int sp = (int)motor_get_position(motor);
  printf("ticks - %d pos - %d sp - %d\n\r", ticks, (int)motor_get_position(motor), sp); //avgFilter_ult() > WALLDISTANCE  --&& adi_digital_read(1)
  while (((abs(ticks) - abs(((int)motor_get_position(motor)) - sp)) > 10 && !adi_digital_read('A') ) )  //&& (adi_analog_read_calibrated(ACCELEROMETER_Z) - accelZ_init) < STOPTIP)
  { // 10 =, change to change where stop
    motor_move_p(motor, ticks, (millis() > ft) ? p : (p < 0) ? -50 : 50);
    printf("ticks - %d pos - %d sp - %d\n\r", ticks, (int)motor_get_position(motor), sp);
    delay(20);
  }
}

// Move `ticks` forward from the current position using p for speed
void wait_motor_move_p_rel(int motor, int ticks, float p)
{

  wait_motor_move_p(motor, motor_get_position(motor) + ticks, p);
}

void wait_motor_move_rel_ac(int motor, int ticks, float p, int actime)
{

  wait_motor_move_p_ac(motor, ticks, p, actime);
}

// Move `ticks` forward from the current position using p for speed
void flywheel_go(float speed);

void autonomous()
{
  double posit, dest;
  char rpm[20];

  //ult = adi_ultrasonic_init(1, 2);
  motor_set_gearing(MOTOR_DRIVE_FRONT_LEFT, E_MOTOR_GEARSET_18);
  motor_set_gearing(MOTOR_DRIVE_BACK_LEFT, E_MOTOR_GEARSET_18);
  motor_set_gearing(MOTOR_DRIVE_FRONT_RIGHT, E_MOTOR_GEARSET_18);
  motor_set_gearing(MOTOR_DRIVE_BACK_RIGHT, E_MOTOR_GEARSET_18);
  motor_set_gearing(MOTOR_DESCORER, E_MOTOR_GEARSET_18);
  motor_set_gearing(MOTOR_INTAKE, E_MOTOR_GEARSET_18);
  motor_set_gearing(MOTOR_INDEXER, E_MOTOR_GEARSET_18);
  motor_set_gearing(MOTOR_FLYWHEEL, E_MOTOR_GEARSET_36);
  //motor_set_brake_mode(10, E_MOTOR_BRAKE_COAST);
  //motor_set_brake_mode(4, E_MOTOR_BRAKE_COAST);
  //motor_set_brake_mode(8, E_MOTOR_BRAKE_COAST);
  //motor_set_brake_mode(2, E_MOTOR_BRAKE_COAST);
  motor_set_reversed(11, 1);
  motor_set_reversed(3, 1);
  motor_set_reversed(13, 1);
  motor_set_reversed(2, 1);
  motor_set_brake_mode(MOTOR_DESCORER,E_MOTOR_BRAKE_COAST);

  motor_move(MOTOR_FLYWHEEL, 127); // flywheel starts
  motor_move(MOTOR_INTAKE, 127);   //intake starts

  posit = motor_get_position(10);
  dest = posit + 9000.0;
  printf("start motors\r\n");

  wait_motor_move_ac(11, forward1, 127, 200);

  set_motors(0);
  delay(1000);
  
  wait_motor_move_ac(11, -backward1, -127, 200);
  set_motors(0);

  delay(1000);
motor_move(MOTOR_INTAKE, 0);
motor_move_absolute(MOTOR_DESCORER, 6000, 200);
  // motor_move_relative(3, -turn, -127);
  // motor_move_relative(14, turn, 127);
  // motor_move_relative(11, -turn, -127);
  // motor_move_relative(12, turn, 127);
  // while (motor_get_target_position(11) > motor_get_position(11))
  // {

  //   printf("turn - %f - %f\r\n", motor_get_target_position(11), motor_get_position(11));
  //   delay(10);
  // }
  // delay(1000);

  // printf("turn\r\n");
  // motor_tare_position(11);
  // wait_motor_move_ac(11, forward2, 127, 200);
  // set_motors(0);
  // printf("shoot\r\n");
  // delay(1000); 
  // motor_move(MOTOR_INTAKE,200);
  // motor_move_relative(MOTOR_INDEXER, 1000, 127);
  // delay(1000);
  // motor_tare_position(11);
  // wait_motor_move_ac(11, forward3, 127, 200);
  // set_motors(-30);

  // set_motors(0);

  // delay(1000);
  // motor_move(MOTOR_INTAKE,200);
  // motor_move_relative(MOTOR_INDEXER, 1000, 127);

  // delay(1000);
  
  // motor_move_relative(3, -turnf, -127);
  // motor_move_relative(14, turnf, 127);
  // motor_move_relative(11, -turnf, -127);
  // motor_move_relative(12, turnf, 127);
  // delay(100);
  // motor_tare_position(11);
  // wait_motor_move_ac_ust(11, forward4, 90, 200);
  // //sprintf(rpm, "AccelZ: %d ", (abs(adi_analog_read_calibrated(ACCELEROMETER_Z)) - accelZ_init));
  // printf("%s\n", rpm);
  // controller_print(E_CONTROLLER_MASTER, 0, 0, rpm);
  // // while (adi_digital_read('A') == 0 && (abs(adi_analog_read_calibrated(ACCELEROMETER_Z)) - accelZ_init) < STOPTIP)
  // // {
  // //   sprintf(rpm, "AccelZ: %d ", (abs(adi_analog_read_calibrated(ACCELEROMETER_Z)) - accelZ_init));
  // //   printf("%s\n", rpm);
  // //   controller_print(E_CONTROLLER_MASTER, 0, 0, rpm);
  // // }
  // // sprintf(rpm, "AccelZ: %d ", (abs(adi_analog_read_calibrated(ACCELEROMETER_Z)) - accelZ_init));
  // // printf("%s\n", rpm);
  // // controller_print(E_CONTROLLER_MASTER, 0, 0, rpm);
  // set_motors(0);
  // delay(200);
  // motor_move_relative(3,turnb, 127);
  // motor_move_relative(14, -turnb, -127);
  // motor_move_relative(11, turnb, 127);
  // motor_move_relative(12, -turnb, -127);
  // delay(100);

  // wait_motor_move_ac(11, -900, -127, 200);
  // delay(1000);
  // motor_move_relative(3, -turnf, -127);
  // motor_move_relative(14, turnf, 127);
  // motor_move_relative(11, -turnf, -127);
  // motor_move_relative(12, turnf, 127);
  // delay(100);
}
