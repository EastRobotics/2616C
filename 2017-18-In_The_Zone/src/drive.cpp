#include <GeneralRobotics.h>

GeneralRobotics::Drive::Drive(int type, LinkedList v) {
  this->type = type;
  this->v = v;
}

void GeneralRobotics::Drive::moveTank(Point p1, Point p2, int Rspeed, int Tspeed) {
  for (int i = 0; i < v.count(); i++) {
    v.retrieve(i) -> mtr -> setValue(speed);
  }
  while(gyroval < 90 - (atan(((p2->y) - (p1->y))/((p2->x) - (p1->x)))))) {}
    
  for (int i = 0; i < v.count(); i++) {
    v.retrieve(i) -> mtr -> setValue(speed * v.retrieve(i) -> rel);
  }
}


void driveControl(void* ignore) {
  using namespace GeneralRobotics;
  LinkedList mtrs = *new LinkedList();
  mtrs.makeAndInsertNode(new DriveMotor(4), 1);
  mtrs.makeAndInsertNode(new DriveMotor(7), 1);
  mtrs.makeAndInsertNode(new DriveMotor(9), -1);
  mtrs.makeAndInsertNode(new DriveMotor(3), -1);
  printf("hello\n");
  Drive driveSet = *new Drive(4, mtrs);
  while (1) {
    driveSet.move(driveVal);
  }
}
