
#pragma once

using namespace okapi;

Motor flywheelMotor = 1_mtr;
Motor intakeMotor = 13_mtr;
Motor indexerMotor = 2_mtr;
Motor descorerMotor = 4_mtr;

 MotorGroup leftmotors({12, 14});
 MotorGroup rightmotors({3 ,11});

rightmotors.okapi::AbstractMotor::setReversed(true);

auto drive = ChassisControllerFactory::create(
    leftmotors, rightmotors,
    AbstractMotor::gearset::green,
    {4.125_in, 9.5_in});
