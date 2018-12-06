#include "main.h"

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
MotorGroup liftMotors({12,-15});  // 2 motors treated as one

Motor shooterRMotor = 11_rmtr;   //Define and instantiate all of the motors
Motor shooterLMotor = 14_mtr;
Motor intakeMotor = 18_rmtr;
Motor armMotor = 8_rmtr;
Motor frontMotor = 13_rmtr;

void opcontrol() {              // Define the Chassis
	auto drive = ChassisControllerFactory::create(    //Std Chassis No PID
     						-19, 20,
    						AbstractMotor::gearset::green,
    					  {4.125_in, 9.5_in}
  							);
Controller controller;
ControllerButton shooter(ControllerDigital::X);    //Define each of the controller buttons
ControllerButton shooteroff(ControllerDigital::Y);
ControllerButton LiftUp(ControllerDigital::L1);
ControllerButton LiftDown(ControllerDigital::L2);
ControllerButton FrontLiftUp(ControllerDigital::R1);
ControllerButton FrontLiftDown(ControllerDigital::R2);

	while (true){
			printf("running shooter  %f\n",shooterRMotor.getActualVelocity());
			drive.tank(controller.getAnalog(ControllerAnalog::leftY),
								 controller.getAnalog(ControllerAnalog::rightY));
    	if(shooter.changedToPressed()) {
					shooterRMotor.moveVelocity(200);
					shooterLMotor.moveVelocity(200);
				};
		  if(shooteroff.changedToReleased()) {
			    shooterRMotor.moveVelocity(0);
					shooterLMotor.moveVelocity(0);
				};
			if(LiftUp.changedToPressed()) {
					liftMotors.moveVelocity(-200);
			};
			if(LiftUp.changedToReleased()) {
				  liftMotors.moveVelocity(0);
				};
			if(LiftDown.changedToPressed()) {
					liftMotors.moveVelocity(200);
				};
			if(LiftDown.changedToReleased()) {
				liftMotors.moveVelocity(0);
				};
			if(FrontLiftUp.changedToPressed()) {
				frontMotor.moveVelocity(-200);
				};
			if(FrontLiftUp.changedToReleased()) {
				frontMotor.moveVelocity(0);
				};
			if(FrontLiftDown.changedToPressed()) {
				frontMotor.moveVelocity(200);
				};
			if(FrontLiftDown.changedToReleased()) {
				frontMotor.moveVelocity(0);
				};
			pros::Task::delay(20);
	 }
}
