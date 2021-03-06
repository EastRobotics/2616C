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
 #define KF 0
 #define KP 1.0f
 #define KI 0.001f
 #define KD 0.1f

 #define MOTOR_DRIVE_FRONT_RIGHT 3
#define MOTOR_DRIVE_FRONT_LEFT 14
#define MOTOR_DRIVE_BACK_RIGHT 11
#define MOTOR_DRIVE_BACK_LEFT 12
#define MOTOR_INTAKE 13
#define MOTOR_INDEXER 2
#define MOTOR_FLYWHEEL 1
#define MOTOR_DESCORER 4

//#define desired 89

 void flywheel_go(float speed){
  motor_set_gearing(9,E_MOTOR_GEARSET_36);
  motor_pid_s_t pid = motor_convert_pid(KF, KP, KI, KD);
  motor_set_vel_pid(9, pid);
  motor_move_velocity(9,speed);
}


void opcontrol() {

	int left;
	int right;
	double driveMult = 1;

	int descorerForward;
	int descorerBackward;

	int intakeForward;
	int intakeBackward;

	bool indexerForward;
	bool indexerBackward;

	bool flywheelIncrease;
	bool flywheelDecrease;

  //bool atSpeed;

	int count = 0;

	char rpm[10] = "";


// if(motor_get_actual_velocity(9) >= desired && !atSpeed)
//
// if(atSpeed == 1)
// {controller_rumble(CONTROLLER_MASTER, "-.-");}


	motor_set_gearing(MOTOR_DRIVE_FRONT_LEFT, E_MOTOR_GEARSET_18);
	motor_set_gearing(MOTOR_DRIVE_BACK_LEFT, E_MOTOR_GEARSET_18);
	motor_set_gearing(MOTOR_DRIVE_FRONT_RIGHT, E_MOTOR_GEARSET_18);
	motor_set_gearing(MOTOR_DRIVE_BACK_RIGHT, E_MOTOR_GEARSET_18);
	motor_set_gearing(MOTOR_DESCORER, E_MOTOR_GEARSET_18);
	motor_set_gearing(MOTOR_INTAKE, E_MOTOR_GEARSET_18);
  motor_set_gearing(MOTOR_INDEXER, E_MOTOR_GEARSET_18);
	motor_set_gearing(MOTOR_FLYWHEEL, E_MOTOR_GEARSET_36);

  motor_set_reversed(8,0);
  motor_set_reversed(10,0);
 		flywheel_go(90);
	while(true) {

		left = controller_get_analog(E_CONTROLLER_MASTER, E_CONTROLLER_ANALOG_LEFT_Y);
		right = controller_get_analog(E_CONTROLLER_MASTER, E_CONTROLLER_ANALOG_RIGHT_Y);

		intakeForward = controller_get_digital(E_CONTROLLER_MASTER, E_CONTROLLER_DIGITAL_R1);
		intakeBackward = controller_get_digital(E_CONTROLLER_MASTER, E_CONTROLLER_DIGITAL_R2);

    indexerForward = controller_get_digital(E_CONTROLLER_MASTER, E_CONTROLLER_DIGITAL_L1);
    indexerBackward = controller_get_digital(E_CONTROLLER_MASTER, E_CONTROLLER_DIGITAL_L2);

		descorerForward = controller_get_digital(E_CONTROLLER_MASTER, E_CONTROLLER_DIGITAL_B);
    descorerBackward = controller_get_digital(E_CONTROLLER_MASTER, E_CONTROLLER_DIGITAL_A);

		flywheelIncrease = controller_get_digital(E_CONTROLLER_MASTER, E_CONTROLLER_DIGITAL_UP);
		flywheelDecrease = controller_get_digital(E_CONTROLLER_MASTER, E_CONTROLLER_DIGITAL_DOWN);

		if(controller_get_digital_new_press(E_CONTROLLER_MASTER, E_CONTROLLER_DIGITAL_X)) {
			driveMult = 1;
		} else if(controller_get_digital_new_press(E_CONTROLLER_MASTER, E_CONTROLLER_DIGITAL_Y)) {
			driveMult = 0.7;
			//change low drive speed by changing (0.5) to something different
		}
      // sets the speed of the motors and how they should function
		motor_move(MOTOR_DRIVE_FRONT_LEFT, left * driveMult);
		motor_move(MOTOR_DRIVE_FRONT_RIGHT, -1 * right * driveMult);
		motor_move(MOTOR_DRIVE_BACK_LEFT, left * driveMult);
		motor_move(MOTOR_DRIVE_BACK_RIGHT, -1 * right * driveMult);

		if (descorerForward == 1)
			motor_move(MOTOR_DESCORER, descorerForward * 127);
		else if (descorerBackward == 1)
			motor_move(MOTOR_DESCORER, descorerBackward * -127);
		else
			motor_move(MOTOR_DESCORER, 0);

		if (intakeForward == 1)
			motor_move(MOTOR_INTAKE, intakeForward * 127);
		else if (intakeBackward == 1)
			motor_move(MOTOR_INTAKE, intakeBackward * -127);
		else
			motor_move(MOTOR_INTAKE, 0);

		if (indexerForward == 1)
			motor_move(MOTOR_INDEXER, indexerForward * 100);
		else if (indexerBackward == 1)
			motor_move(MOTOR_INDEXER, indexerBackward * -100);
		else
			motor_move(MOTOR_INDEXER, 0);
       /**
			 * sets the speed for the flywheel and makes it so once the button
			 * is pressed the speed will stay at 127 and when the other button is
			 * pressed the speed will go down to zero
			 */
		if (flywheelIncrease == 1)
		flywheel_go(90);
		  // motor_move(MOTOR_FLYWHEEL, flywheelIncrease * 127);
		else if (flywheelDecrease == 1)
		   motor_move(MOTOR_FLYWHEEL, flywheelDecrease * 0);


			if (!(count % 50)) {
	      // Only print every 50ms, the controller text update rate is slow
				sprintf(rpm, "RPM: %.2f    ", motor_get_actual_velocity(9));
				printf("%s\n",rpm);
				controller_print(E_CONTROLLER_MASTER, 0, 0, rpm);
				delay(0);
			  controller_clear_line(E_CONTROLLER_MASTER, 0);
	    }
	    count++;
	    delay(10);

   }

}
