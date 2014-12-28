void TeleOp()
{
	while (true)
	{

		// Driving stuffs.
	  // All linear motion on L stick. Rotational motion on R stick x-axis.

		int Y1 = 0;
		int X1 = 0;
		int X2 = 0;
		float turn = 0;
		float strafe = 0;
		while(true)
		{
			{
				strafe = vexRT[Ch4];
				turn = vexRT[Ch1];
			}
			if(abs(vexRT[Ch3]) > threshold)
				Y1 = vexRT[Ch3];
			else
				Y1 = 0;
			if(abs(strafe) > threshold)
				X1 = strafe;
			else
				X1 = 0;
			if(abs(turn) > threshold)
				X2 = turn;
			else
				X2 = 0;
			motor[LFDrive] = Y1 - X2 - X1;
			motor[LBDrive] =  Y1 - X2 + X1;
			motor[RFDrive] = Y1 + X2 + X1;
			motor[RBDrive] =  Y1 + X2 - X1;


			// Lift on right stick.
			// Up = up. Down = down.

			if(abs(vexRT[Ch1]) >= threshold)
			{
				int power = Ch1;
				Lift(power);
			}
			else
			{
				LockLift();
			}

			// Cube intake on left shoulder buttons.
			// Up = in. Down = out.

			if(vexRT[Btn5U])
			{
				CubeIntake("up",127);
			}
			else if(vexRT[Btn5D])
			{
				CubeIntake("down",127);
			}
			else
			{
				CubeIntake("up",0);
			}

			// Hotkeys for Skyrise heights. Starting on R D-pad, starting at down button going counter-clockwise
			// around the D-pad, then moving in same order around L D-pad. 8 heights, 8 buttons.

			if(vexRT[Btn8D]==1)
			{
				LiftHeight("Down", -127, BaseHeight);
			}
			if(vexRT[Btn8R]==1)
			{
				LiftHeight("Up", 127, Skyrise1);
			}
			if(vexRT[Btn8U]==1)
			{
				LiftHeight("Up", 127, Skyrise2);
			}
			if(vexRT[Btn8L]==1)
			{
				LiftHeight("Up", 127, Skyrise3);
			}
			if(vexRT[Btn7D]==1)
			{
				LiftHeight("Up", 127, Skyrise4);
			}
			if(vexRT[Btn7R]==1)
			{
				LiftHeight("Up", 127, Skyrise5);
			}
			if(vexRT[Btn7U]==1)
			{
				LiftHeight("Up", 127, Skyrise6);
			}
			if(vexRT[Btn7L]==1)
			{
				LiftHeight("Up", 127, Skyrise7);
			}

			// Skyrise intake - controlled by right joystick.
			// Up = in. Down = out.

			if(vexRT[Btn8U] == 1)
			{
				SkyriseIntake("in");
			}
			else if(vexRT[Btn8D] == 1)
			{
				SkyriseIntake("out");
			}
		}
	}
}
