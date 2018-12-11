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
#define dKp 0.0014
#define dKi 0.0000
#define dKd 0.0000

#define aKp 0.006
#define aKi 0.030
#define aKd 0.0600



 #define VISION_PORT 17
 #define PRIMARY_SIG 1
 #define TAG_SIG 2
 using namespace pros;
 using namespace okapi;
// extern float dKp, dKi, dKd, aKp, aKi, aKd, tKp, tKi, tKd;
//  float dKp, dKi, dKd, aKp, aKi, aKd, tKp, tKi, tKd;

 MotorGroup leftmotors({2,4});
 MotorGroup rightmotors({-8,-10});

 auto chassis = ChassisControllerFactory::create(leftmotors,rightmotors,
   IterativePosPIDController::Gains{dKp, dKi, dKd}, // Distance, for distance Control
   IterativePosPIDController::Gains{aKp, aKi, aKd},  //angle, for Driving Straight  IterativePosPIDController::Gains{0.01, 1.2, 1.6},
//   IterativePosPIDController::Gains{tKp, tKi, tKd},   // turn, for turn control
   AbstractMotor::gearset::green,{4.125_in, 10.5_in});

typedef uint16_t vision_color_code_t;


void autonomous() {
  Vision vision_sensor(VISION_PORT);
  vision_color_code_t code1 = vision_sensor.create_color_code(PRIMARY_SIG, TAG_SIG);
  // auto chassis = ChassisControllerFactory::create(leftmotors,rightmotors,
  //   IterativePosPIDController::Gains{dKp, dKi, dKd},  // Distance, for distance Control
  //   IterativePosPIDController::Gains{aKp, aKi, aKd},  //angle, for Driving Straight
  // //  IterativePosPIDController::Gains{tKp, tKi, tKd},   // turn, for turn control
  //   AbstractMotor::gearset::green,
  //   {4.125_in, 10.5_in});

  chassis.moveDistance(300_mm);
  chassis.turnAngle(-90_deg);
  // pros::delay(2000);
  // chassis.turnAngle(90_deg);
  // pros::delay(2000);
  // chassis.turnAngle(-90_deg);
  // delay(2000);
  // delay(2000);
  // chassis.moveDistance(-1500_mm);

}

// drivectl.generatePath({
//   Point{0_ft, 0_ft, 0_deg},  // Profile starting position, this will normally be (0, 0, 0)
//   Point{3_ft, 0_ft, 0_deg}}, // The next point in the profile, 3 feet forward
//   "A" // Profile name
// );
// drivectl.generatePath({
//   Point{3_ft, 0_ft, 0_deg},  // Profile starting position, this will normally be (0, 0, 0)
//   Point{0_ft, 0_ft, 0_deg}}, // The next point in the profile, 3 feet forward
//   "B" // Profile name
// );
// drivectl.generatePath({
//   Point{0_ft, 0_ft, 0_deg},  // Profile starting position, this will normally be (0, 0, 0)
//   Point{0_ft, 0_ft, 90_deg}}, // The next point in the profile, 3 feet forward
//   "C" // Profile name
// );
// drivectl.setTarget("A");
// drivectl.waitUntilSettled();
// drivectl.setTarget("B");
// drivectl.waitUntilSettled();
// drivectl.setTarget("C");
// drivectl.waitUntilSettled();
