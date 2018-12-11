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

using namespace okapi;

Motor flywheelMotor = 1_mtr;
Motor intakeMotor = 13_mtr;
Motor indexerMotor = 2_mtr;
Motor descorerMotor = 4_mtr;

MotorGroup leftmotors({2, 4});
MotorGroup rightmotors({-8, -10});

auto drive = ChassisControllerFactory::create(
    leftmotors, rightmotors,
    AbstractMotor::gearset::green,
    {4.125_in, 9.5_in});

void autonomous()
{
intakeMotor.move(127);    
drive.moveDistance(4_ft);
pros::delay(100);
drive.moveDistance(-4_ft);

}
