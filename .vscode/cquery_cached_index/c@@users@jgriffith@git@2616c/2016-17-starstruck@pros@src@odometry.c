#include "main.h"
typedef struct{
	//int x_quad;
 	Encoder y_quad;
	float wheelcirc;
	float xticks;
	float yticks;
	//float xdir;
	//float ydir;
	dircoeff ydir;
	dircoeff xdir;
} Odometry;

Odometry odom;
BotLocation botpos;

void odometer(void* ignore) {
  float yq;
  encoderInit(dOdomEncoder_YT, dOdomEncoder_YL, false);
  printf("Odom start");
  yq = 0;
  while(1) {
    yq = encoderGet(odom.y_quad)/odom.yticks*odom.wheelcirc*odom.ydir;
    botpos.y_pos += yq;
    encoderInit(dOdomEncoder_YT, dOdomEncoder_YL, false);
    delay(100);
  }
}
void initOdometry(/*Encoder x_quad,*/ Encoder y_quad, float whlcir, float xtck, float ytck,/* dircoeff xdir = pos,*/ dircoeff ydir) {
  //odom.x_quad = x_quad;
	odom.y_quad = y_quad;
	odom.wheelcirc = whlcir;
	odom.xticks = xtck;
	odom.yticks = ytck;
	//odom.xdir = xdir;
	odom.ydir = ydir;
  taskCreate(odometer, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);
}
void refreshBotLocation(BotLocation *bl) {
  bl->x_pos = botpos.x_pos;
  bl->y_pos = botpos.y_pos;
}

void resetOdom() {
  botpos.x_pos = botpos.y_pos = 0.0;
}
