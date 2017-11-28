#include <GeneralRobotics.h>

struct _Node {
  GeneralRobotics::DriveMotor* mtr;
  int rel;
  _Node* next;
};

GeneralRobotics::Drive::Drive(int type, LinkedList v) {
  this->type = type;
  this->v = v;
}

void GeneralRobotics::Drive::move(int speed) {
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
