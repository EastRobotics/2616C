/////////////////////////////////////////////////////////////////////////////////////////
//
//                          Full Skyrise Autonomous
//
// Theoretically, this autonomous program will build a full Skyrise tower and score
// the pre-load cube on the Skyrise, scoring 32 points total. This is not feasible
// during the autonomous period of a match, during which we would be fully satisfied
// with a 5 section tower, thus scoring 24 points. However, this could ideally be
// fully executed in a Programming Skills run.
//
/////////////////////////////////////////////////////////////////////////////////////////

void SkyriseAuton(const string color)
{
	if(color == "red")
	{
		LiftHeight("up", 127, FlipDown);
		LiftHeight("down", 127, AutoLoaderHeight);
		SkyriseIntake("in");
		GyroTurn("right",127,AutoLoaderToBase);
		LiftHeight("up", 127, Skyrise1);
		SkyriseIntake("out");
		LiftHeight("down",127,AutoLoaderHeight);
		GyroTurn("left",127,BaseToAutoLoader);
		SkyriseIntake("in");
		GyroTurn("right",127,AutoLoaderToBase);
		LiftHeight("up", 127, Skyrise2);
		SkyriseIntake("out");
		LiftHeight("down",127,AutoLoaderHeight);
		GyroTurn("left",127,BaseToAutoLoader);
		SkyriseIntake("in");
		GyroTurn("right",127,AutoLoaderToBase);
		LiftHeight("up", 127, Skyrise3);
		SkyriseIntake("out");
		LiftHeight("down",127,AutoLoaderHeight);
		GyroTurn("left",127,BaseToAutoLoader);
		SkyriseIntake("in");
		GyroTurn("right",127,AutoLoaderToBase);
		LiftHeight("up", 127, Skyrise4);
		SkyriseIntake("out");
		LiftHeight("down",127,AutoLoaderHeight);
		GyroTurn("left",127,BaseToAutoLoader);
		SkyriseIntake("in");
		GyroTurn("right",127,AutoLoaderToBase);
		LiftHeight("up", 127, Skyrise5);
		SkyriseIntake("out");
		LiftHeight("down",127,AutoLoaderHeight);
		GyroTurn("left",127,BaseToAutoLoader);
		SkyriseIntake("in");
		GyroTurn("right",127,AutoLoaderToBase);
		LiftHeight("up", 127, Skyrise6);
		SkyriseIntake("out");
		LiftHeight("down",127,AutoLoaderHeight);
		GyroTurn("left",127,BaseToAutoLoader);
		SkyriseIntake("in");
		GyroTurn("right",127,AutoLoaderToBase);
		LiftHeight("up", 127, Skyrise7);
		SkyriseIntake("out");
		LiftHeight("down",127,AutoLoaderHeight);
	}
	else if(color == "blue")
	{
		LiftHeight("up", 127, FlipDown);
		LiftHeight("down", 127, AutoLoaderHeight);
		SkyriseIntake("in");
		GyroTurn("left",127,AutoLoaderToBase);
		LiftHeight("up", 127, Skyrise1);
		SkyriseIntake("out");
		LiftHeight("down",127,AutoLoaderHeight);
		GyroTurn("right",127,BaseToAutoLoader);
		SkyriseIntake("in");
		GyroTurn("left",127,AutoLoaderToBase);
		LiftHeight("up", 127, Skyrise2);
		SkyriseIntake("out");
		LiftHeight("down",127,AutoLoaderHeight);
		GyroTurn("right",127,BaseToAutoLoader);
		SkyriseIntake("in");
		GyroTurn("left",127,AutoLoaderToBase);
		LiftHeight("up", 127, Skyrise3);
		SkyriseIntake("out");
		LiftHeight("down",127,AutoLoaderHeight);
		GyroTurn("right",127,BaseToAutoLoader);
		SkyriseIntake("in");
		GyroTurn("left",127,AutoLoaderToBase);
		LiftHeight("up", 127, Skyrise4);
		SkyriseIntake("out");
		LiftHeight("down",127,AutoLoaderHeight);
		GyroTurn("right",127,BaseToAutoLoader);
		SkyriseIntake("in");
		GyroTurn("left",127,AutoLoaderToBase);
		LiftHeight("up", 127, Skyrise5);
		SkyriseIntake("out");
		LiftHeight("down",127,AutoLoaderHeight);
		GyroTurn("right",127,BaseToAutoLoader);
		SkyriseIntake("in");
		GyroTurn("left",127,AutoLoaderToBase);
		LiftHeight("up", 127, Skyrise6);
		SkyriseIntake("out");
		LiftHeight("down",127,AutoLoaderHeight);
		GyroTurn("right",127,BaseToAutoLoader);
		SkyriseIntake("in");
		GyroTurn("left",127,AutoLoaderToBase);
		LiftHeight("up", 127, Skyrise7);
		SkyriseIntake("out");
		LiftHeight("down",127,AutoLoaderHeight);
	}
}

void RunAuton() // Alliance color is determined by a jumper plug in analog port 5. No plug = red. Plug = blue.
{
	if(in5==false)
	{
		SkyriseAuton("red");
	}
	if(in5==true)
	{
		SkyriseAuton("blue");
	}
	if(in6==true)  // dummy auton meant to use excess functions to eliminate warnings when compiling
	{
		LiftHeight("up", 127, 100);
		LiftHeight("down",127,0);
		Drive(127);
		TimedStop(1000);
		EncoderDrive(0,0);
		Strafe("left",0);
		TimedStrafe("right",0,0);
		Turn("right",0);
		GyroTurn("left",0,0);
		CubeIntake("up",0);
		CubeIntakeTime("up",0,0);
		SkyriseIntake("in");
		SkyriseIntake("out");
	}
}
