////////////////////////////////////////////////////////////////////////////////////////
//  Include File Odometry via Mouse style X/Y Optical Quadrature Encoders
//  Also demonstrates compiler directives for debugging using datalog,
//  automatic datalog debugger window pops, graphing datalogger, use of data structures, etc
//
//  This can be used and embellished freely by CHE Robotics team enhancements should reviewed
//  and committed to the github repository so future teams can benefit from improvements
//
////////////////////////////////////////////////////////////////////////////////////////
//  Design and Setup:
//
////////////////////////////////////////////////////////////////////////////////////////
//  Assumptions:
//
////////////////////////////////////////////////////////////////////////////////////////
#ifdef datalog
    #pragma DebuggerWindows("DatalogGraph")
#endif

typedef struct{
	float x_pos;
	float y_pos;
}BotLocation;

typedef enum dirco {pos = 1,neg = -1} dircoeff ;


typedef struct{
	int x_quad;
	int y_quad;
	float wheelcirc;
	float xticks;
	float yticks;
	//float xdir;
	//float ydir;
	dircoeff ydir;
	dircoeff xdir ;

} odometry;

odometry odom;


BotLocation botpos;

task odometer()
{
	float xq, yq;
	SensorValue[odom.x_quad] = SensorValue[odom.y_quad]  = 0.0;
	xq = yq = 0.0;
	while(1)
	{
		xq =  SensorValue[odom.x_quad]/odom.xticks*odom.wheelcirc*odom.xdir;
		yq =  SensorValue[odom.y_quad]/odom.yticks*odom.wheelcirc*odom.ydir;
		botpos.x_pos += xq;
		botpos.y_pos += yq;
#ifdef datalog
	      datalogDataGroupStart();
        datalogAddValue( 0, botpos.x_pos );
        datalogAddValue(1, botpos.y_pos );
        datalogDataGroupEnd();
#endif
		SensorValue[odom.x_quad] = SensorValue[odom.y_quad]  = 0.0;
		wait1Msec(100);
	}
}
void init_odometry(int x_quad, int y_quad, float whlcir = 9.42, float xtck = 360.0, float ytck = 360.0, dircoeff xdir = pos, dircoeff ydir  = pos)
{
	 /* if((ydir != pos || ydir != neg) && (xdir != pos || xdir != neg))
	  {
	  	writeDebugStream("Invalid Value for direction multipliear!");
	  }*/
	  odom.x_quad = x_quad;
	  odom.y_quad = y_quad;
  	odom.wheelcirc = whlcir;
  	odom.xticks = xtck;
  	odom.yticks = ytck;
  	odom.xdir = xdir;
  	odom.ydir = ydir;
  	startTask(odometer);
#ifdef datalog
		datalogClear();
#endif
}
void get_botlocation(BotLocation *bl)
{
   bl->x_pos = botpos.x_pos;
   bl->y_pos = botpos.y_pos;
}
