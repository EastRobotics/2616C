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

// float dKp= dKi= dKd= aKp= aKi= aKd= tKp= tKi= tKd = 0;
 // Chassis Controller - lets us drive the robot around with open- or closed-loop control
 auto drive = ChassisControllerFactory::create(
   {2,4}, {-8,-10},
   AbstractMotor::gearset::green,
   {4.125_in, 10.5_in}
 );

 void opcontrol() {
   // Joystick to read analog values for tank or arcade control
   // Master controller by default
   Controller controller;

   // Arm related objects
   ADIButton armLimitSwitch('H');
   // ControllerButton armUpButton(ControllerDigital::A);
   // ControllerButton armDownButton(ControllerDigital::B);
   // Motor armMotor = 8_rmtr;

   // Button to run our sample autonomous routine
   ControllerButton runAutoButton(ControllerDigital::X);
//   ControllerButton incPgain
   while (true) {
     // Arcade drive with the left stick
     drive.tank(controller.getAnalog(ControllerAnalog::leftY),
                  controller.getAnalog(ControllerAnalog::rightY));

     // Don't power the arm if it is all the way down
     // if (armLimitSwitch.isPressed()) {
     //   armMotor.move_voltage(0);
     // } else {
     //   // Else, the arm isn't all the way down
     //   if (armUpButton.isPressed()) {
     //     armMotor.move_voltage(127);
     //   } else if (armDownButton.isPressed()) {
     //     armMotor.move_voltage(-127);
     //   } else {
     //     armMotor.move_voltage(0);
     //   }
     // }

     // Run the test autonomous routine if we press the button
     if (runAutoButton.changedToPressed()) {
       // Drive the robot in a square pattern using closed-loop control
       for (int i = 0; i < 4; i++) {
         drive.moveDistance(12_in); // Drive forward 12 inches
         drive.turnAngle(90_deg);   // Turn in place 90 degrees
       }
     }

     // Wait and give up the time we don't need to other tasks.
     // Additionally, joystick values, motor telemetry, etc. all updates every 10 ms.
     pros::Task::delay(10);
   }
 }
