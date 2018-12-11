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
MotorGroup liftMotors({12,-15});
//MotorGroup shooterMotors({11,-14});

Motor shooterRMotor = 11_mtr;
Motor shooterLMotor = 14_rmtr;
Motor intakeMotor = 18_rmtr;
Motor armMotor = 8_rmtr;
Motor frontMotor = 13_rmtr;

void opcontrol() {
	// pros::Controller master(pros::E_CONTROLLER_MASTER);
	// pros::Motor left_mtr(1);
	// pros::Motor right_mtr(2);
 //using namespace pros;
	auto drive = ChassisControllerFactory::create(
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
ControllerButton IntakeOn(ControllerDigital::A);
ControllerButton IntakeOff(ControllerDigital::B);
//liftMotors.moveVoltage(127);
	while (true){
		drive.arcade(controller.getAnalog(ControllerAnalog::leftY),
								-controller.getAnalog(ControllerAnalog::rightX));
    if(shooter.changedToPressed()) {
			shooterRMotor.moveVelocity(200);
				shooterLMotor.moveVelocity(200);

			printf("running shooter  %f\n",shooterRMotor.getActualVelocity());
		};
		printf("running shooter  %f\n",shooterRMotor.getActualVelocity());
		if(shooteroff.changedToReleased()) {
			shooterRMotor.moveVelocity(0);
				shooterLMotor.moveVelocity(0);
		};

		if(LiftUp.changedToPressed()) {
			liftMotors.moveVelocity(-200);
	//			shooterLMotor.moveVelocity(200);

			printf("running shooter  %f\n",shooterRMotor.getActualVelocity());
		};
		if(LiftUp.changedToReleased()) {
			liftMotors.moveVelocity(0);
	//			shooterLMotor.moveVelocity(200);

			printf("running shooter  %f\n",shooterRMotor.getActualVelocity());
		};
		if(LiftDown.changedToPressed()) {
				liftMotors.moveVelocity(200);

			printf("running shooter  %f\n",shooterRMotor.getActualVelocity());
		};
		if(LiftDown.changedToReleased()) {
		liftMotors.moveVelocity(0);
			printf("running shooter  %f\n",shooterRMotor.getActualVelocity());
		};
		if(FrontLiftUp.changedToPressed()) {
			frontMotor.moveVelocity(-200);
	//			shooterLMotor.moveVelocity(200);

			printf("running shooter  %f\n",shooterRMotor.getActualVelocity());
		};
		if(FrontLiftDown.changedToReleased()) {
			frontMotor.moveVelocity(0);
	//			shooterLMotor.moveVelocity(200);

			printf("running shooter  %f\n",shooterRMotor.getActualVelocity());
		};
		if(FrontLiftUp.changedToPressed()) {
				frontMotor.moveVelocity(200);

			printf("running shooter  %f\n",shooterRMotor.getActualVelocity());
		};
		if(FrontLiftDown.changedToReleased()) {
	frontMotor.moveVelocity(0);
			printf("running shooter  %f\n",shooterRMotor.getActualVelocity());
		};
		if(IntakeOn.changedToPressed()) {
				intakeMotor.moveVelocity(200);
		};
		if(IntakeOff.changedToPressed()) {
				intakeMotor.moveVelocity(0);
		};
	pros::Task::delay(20);
	 }

}
