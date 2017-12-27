
#ifndef _GeneralRobotics_h_

#define _GeneralRobotics_h_
namespace GeneralRobotics {
  class Motor {
    int pwm_value;
    unsigned char port_number;
    public:
      int getPortNumber();
      int getValue();
      void setValue(int value);
  };
  class DriveMotor : public Motor {
    private:
      unsigned char port_number;
      int position;
    public:
      DriveMotor(int);
      DriveMotor(unsigned char, int);
  };
 struct Node {
  DriveMotor* mtr;
  int rel;
  Node* next;
 }
  class LinkedList {
    private:
      Node *head;
      int listLength;
    public:
      LinkedList();
      void makeAndInsertNode(DriveMotor*, int);
      int count();
      Node* retrieve(int);
      bool insertNode(Node*, int);
      bool removeNode(int);
      ~LinkedList();
  };

  class Drive {
    public:
      enum DriveType {Mecanum = 4, StdX = 4, StdOmni = 4, CustomX = 6, CustomOmni = 6 };
      int type;
      LinkedList v;
      void move(int);
      Drive(int, LinkedList);
  };
}

#endif
