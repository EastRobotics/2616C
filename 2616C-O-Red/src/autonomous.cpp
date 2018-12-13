#include "main.h"

/**
 * 2616C Turning Point proposed autonomous run from the Red Front Position
 */

using namespace okapi;





void autonomous()
{

    
  //  drive.setMaxVoltage(9000);
    flywheelMotor.move(127);
    intakeMotor.move(127);

    drive.moveDistance(4_ft);
    pros::delay(100);
    drive.moveDistance(-4_ft);
    drive.turnAngle(-90_deg);
    drive.moveDistance(18_in);
    pros::delay(200);

    indexerMotor.moveRelative(360, 127);

    pros::delay(500);
    drive.moveDistance(18_in);
    pros::delay(200);

    indexerMotor.moveRelative(360, 127);
    
    pros::delay(500);
    drive.turnAngle(-30_deg);
    drive.moveDistance(18_in);
    pros::delay(250);
    drive.moveDistance(-6_ft);
    drive.turnAngle(-90_deg);
    drive.moveDistance(12_in);
    drive.moveDistance(-6_ft);
}
