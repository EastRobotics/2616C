#include "main.h"
#include "pros/misc.h"

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */

using namespace okapi;

// Motor aflywheelMotor = 1_mtr;
// Motor aintakeMotor = 13_mtr;
// Motor aindexerMotor = 2_mtr;
// Motor adescorerMotor = 4_mtr;

// MotorGroup aleftmotors({12, 14});
// MotorGroup arightmotors({3 ,11});

// auto autondrive = ChassisControllerFactory::create(
//     aleftmotors, arightmotors,
//     AbstractMotor::gearset::green,
//     {4.125_in, 9.5_in});

Controller controller;

ControllerButton intakeForward(ControllerDigital::A);
ControllerButton intakeBackward(ControllerDigital::R2);
ControllerButton indexerForward(ControllerDigital::X);
ControllerButton indexerBackward(ControllerDigital::R1);
ControllerButton descorerForward(ControllerDigital::L2);
ControllerButton descorerBackward(ControllerDigital::L1);

void opcontrol()
{
	flywheelMotor.move(127);
	while (true)
	{
		drive.arcade(controller.getAnalog(ControllerAnalog::rightX),
				 controller.getAnalog(ControllerAnalog::leftY));

		if (intakeForward.changedToPressed())
		{
			intakeMotor.move(127);
		}
		if (intakeForward.changedToReleased())
		{
			intakeMotor.move(0);
		}
		if (intakeBackward.changedToPressed())
		{
			intakeMotor.move(-127);
		}
		if (intakeBackward.changedToReleased())
		{
			intakeMotor.move(0);
		}
		if (indexerForward.changedToPressed())
		{
			intakeMotor.move(127);
		}
		if (indexerForward.changedToReleased())
		{
			intakeMotor.move(0);
		}
		if (indexerBackward.changedToPressed())
		{
			intakeMotor.move(-127);
		}
		if (indexerBackward.changedToReleased())
		{
			intakeMotor.move(0);
		}
		if (descorerForward.changedToPressed())
		{
			intakeMotor.move(127);
		}
		if (descorerForward.changedToReleased())
		{
			intakeMotor.move(0);
		}
		if (descorerBackward.changedToPressed())
		{
			intakeMotor.move(-127);
		}
		if (descorerBackward.changedToReleased())
		{
			intakeMotor.move(0);
		}
		pros::delay(20);
	}
}

/* Removed from Opcontrol
	pros::lcd::print(0, "%d %d %d", (pros::lcd::read_buttons() & LCD_BTN_LEFT) >> 2,
		                 (pros::lcd::read_buttons() & LCD_BTN_CENTER) >> 1,
		                 (pros::lcd::read_buttons() & LCD_BTN_RIGHT) >> 0);
		int left = master.get_analog(ANALOG_LEFT_Y);
		int right = master.get_analog(ANALOG_RIGHT_Y);

		left_mtr = left;
		right_mtr = right;
*/
