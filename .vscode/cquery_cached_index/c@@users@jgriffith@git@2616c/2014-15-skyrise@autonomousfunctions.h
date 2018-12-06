/////////////////////////////////////////////////////////////////////////////////////////
//
//                          Robot Functions
//
// These actions are intended to make the process of programming the robot simpler
// and more straightforward. They were, however, created by a programming noob. Sorry.
//
// Functions created so far are:
// Drive, EncoderDrive, StopDrive
// Strafe, TimedStrafe
// Turn, GyroTurn, StopTurn
// Lift, LiftHeight, LockLift
// CubeIntake, SkyriseIntake
//
// Still to come:
// StopStrafe
//
/////////////////////////////////////////////////////////////////////////////////////////


// Basic "endless" drive. Will move the robot forward or backward at a given power.

void Drive(int power)
{
	motor[LBDrive] = power;
	motor[LFDrive] = power;
	motor[RBDrive] = power;
	motor[RFDrive] = power;
}

//Brake the robot slightly before stopping all drive motors

void StopDrive(int power)
{
	if(power > 0)
	{
		motor[LBDrive] = -30;
		motor[LFDrive] = -30;
		motor[RFDrive] = -30;
		motor[RBDrive] = -30;
		wait1Msec(10);
		motor[LBDrive] = 0;
		motor[LFDrive] = 0;
		motor[RFDrive] = 0;
		motor[RBDrive] = 0;
	}
	else if(power < 0)
	{
		motor[LBDrive] = 30;
		motor[LFDrive] = 30;
		motor[RFDrive] = 30;
		motor[RBDrive] = 30;
		wait1Msec(10);
		motor[LBDrive] = 0;
		motor[LFDrive] = 0;
		motor[RFDrive] = 0;
		motor[RBDrive] = 0;
	}
}

//Brake the robot slightly before stopping all drive motors during a turn

void StopTurn(const string direction)
{
	if(direction == "left")
	{
		motor[LBDrive] = 5;
		motor[LFDrive] = 5;
		motor[RFDrive] = -5;
		motor[RBDrive] = -5;
		wait1Msec(10);
		motor[LBDrive] = 0;
		motor[LFDrive] = 0;
		motor[RFDrive] = 0;
		motor[RBDrive] = 0;
	}
	else if(direction == "right")
	{
		motor[LBDrive] = -5;
		motor[LFDrive] = -5;
		motor[RFDrive] = 5;
		motor[RBDrive] = 5;
		wait1Msec(10);
		motor[LBDrive] = 0;
		motor[LFDrive] = 0;
		motor[RFDrive] = 0;
		motor[RBDrive] = 0;
	}
}

//time-based stop

void TimedStop(int time)
{
	wait1Msec(time);
	StopDrive(1);
}

// Drive for a distance measured by integrated drive encoders

void EncoderDrive(int power, int distance)
{
	nMotorEncoder[LBDrive] = 0;
	nMotorEncoder[RBDrive] = 0;
	while(nMotorEncoder[LBDrive] < distance)
	{
		Drive(power);
	}
	StopDrive(power);
}

// dummy, will eventually brake the robot to avoid skidding after strafing

void StopStrafe(const string direction, int power)
{
	StopDrive(power);
}

// time-based strafe for X-drives or flipped wheel-base mecanum drives (diamond alignment instead of X)

void Strafe(const string direction, int power)
{
	if(direction == "left")
	{
		motor[LBDrive] = -power;
		motor[LFDrive] = power;
		motor[RBDrive] = power;
		motor[RFDrive] = -power;
	}
	else if(direction == "right")
	{
		motor[LBDrive] = power;
		motor[LFDrive] = -power;
		motor[RBDrive] = -power;
		motor[RFDrive] = power;
	}
	else
	{
		StopStrafe(direction, power);
	}
}

// time-based strafe

void TimedStrafe(const string direction, int power, int time)
{
	if(direction == "left")
	{
		Strafe("left",power);
		wait1Msec(time);
		StopDrive(1);
	}
	else if(direction == "right")
	{
		Strafe("right",power);
		wait1Msec(time);
		StopStrafe(direction, power);
	}
}

// "endless" turn

void Turn(const string direction, int power)
{
	if(direction == "left")
	{
		motor[LBDrive] = -power;
		motor[LFDrive] = -power;
		motor[RBDrive] = power;
		motor[RFDrive] = power;
	}
	else
	{
		StopTurn("left");
	}
	if(direction == "right")
	{
		motor[LBDrive] = power;
		motor[LFDrive] = power;
		motor[RBDrive] = -power;
		motor[RFDrive] = -power;
	}
	else
	{
		StopTurn("right");
	}
}

// turn a given angle (measured in 10ths of a degree) in a given direction

void GyroTurn(const string direction, int power, int angle)
{
	while(abs(SensorValue[gyro]) < angle)
	{
		Turn(direction, power);
	}
	StopTurn(direction);
}

// "endless" lift

void Lift(int power)
{
	motor[LCLift] = power;
	motor[LTLift] = power;
	motor[RCLift] = power;
	motor[RTLift] = power;
}

// This will lock the lift at any height by powering the motors at 30 power
// which will be enough to keep the lift still but not move it.

void LockLift()
{
	motor[LCLift] = 30;
	motor[LTLift] = 30;
	motor[RCLift] = 30;
	motor[RTLift] = 30;
}

// raise or lower the lift to any potentiometer value

void LiftHeight(const string direction, int power, int height)
{
	if(direction == "up")
	{
		while(SensorValue(LiftPotentiometer) < height)
		{
			Lift(power);
		}
		LockLift();
	}
	else
	{
		LockLift();
	}
	if(direction == "down")
	{
		while(SensorValue(LiftPotentiometer) > height)
		{
			Lift(-power);
		}
		LockLift();
	}
	else
	{
		LockLift();
	}
}

// "endless" cube intake

void CubeIntake(const string direction, int power)
{
	if(direction == "up")
	{
		motor[LIntake]=power;
		motor[RIntake]=power;
	}
	if(direction == "down")
	{
		motor[LIntake]=-power;
		motor[RIntake]=-power;
	}
}

//time-based cube intake

void CubeIntakeTime(const string direction, int power, int time)
{
	if(direction == "up")
	{
		CubeIntake("up",127);
		wait1Msec(time);
		CubeIntake("up",0);
	}
	if(direction == "down")
	{
		CubeIntake("down",127);
		wait1Msec(time);
		CubeIntake("down",0);
	}
}

// Actuate the pneumatic claw for Skyrise sections

void SkyriseIntake(const string direction)
{
	if(direction == "in")
	{
		SensorValue[SkyriseClaw] = 1;
	}
	else if(direction == "out")
	{
		SensorValue[SkyriseClaw] = 0;
	}
}
