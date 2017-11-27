#include <map>
#include <main.h>
#ifndef _GeneralRobotics_h_

#define _GeneralRobotics_h_

#define Y joystickGetAnalog(1, 3)
#define R joystickGetAnalog(1, 1)
#define X joystickGetAnalog(1, 4)

#define drive threshold(Y)
#define strafe threshold(X)
#define rotate threshold(R)
namespace GeneralRobotics {
  class Motor {
    int pwm_value;
    unsigned char port_number;
    public:
      int getPortNumber() {
        return this->port_number;
      };
      int getValue() {
        return this->pwm_value;
      };
      void setValue(int value) {
        this->pwm_value = value;
      };

  };
  class DriveMotor : public Motor {
    private:
      unsigned char port_number;
    public:
      DriveMotor() {
        port_number = 0;
      };
      DriveMotor(unsigned char channel) {
        port_number = channel;
      };
  };
  struct node {
    DriveMotor *mtr;
    int rel;
    node *next;
  };

  class LinkedList {
    private:
      node *head;
      int listLength;
    public:
      LinkedList() {
        head -> mtr = NULL;
        head -> rel = 1;
        head -> next = NULL;
        listLength = 0;
      }
      void makeAndInsertNode(DriveMotor* dm, int relation) {
        node* newNode = NULL;
        newNode -> mtr = dm;
        newNode -> rel = 1;
        newNode -> next = head;
        insertNode(newNode, 0);
      }
      int count() {
        return listLength;
      }
      node* retrieve(int pos) {
        node* current = head;
	      for(int i = listLength - 1; i > pos && current != NULL; i--) {
		        current = current->next;
        }
        return current;
      }
      bool insertNode(node *newNode, int position) {
        if ((position <= 0) || (position > listLength + 1)) {
          print("Index out of bounds");
          return false;
        }
        if (head -> next == NULL) {
          head -> next = newNode;
          listLength++;
          return true;
        }
        int count = 0;
        node *p = head, *q = head;
        while(q) {
          if (count == position) {
            p -> next = newNode;
            newNode -> next = q;
            listLength++;
            return true;
          }
          p = q;
          q = p -> next;
          count++;
        }
        if (count == position) {
            p -> next = newNode;
            newNode -> next = q;
            listLength++;
            return true;
          }
        return false;
      }

      bool removeNode(int position) {
        if ((position <= 0) || (position > listLength + 1)) {
          print("Index out of bounds");
          return false;
        }
        if(head -> next == NULL) {
          return false;
        }
        int count = 0;
        node *p = head;
        node *q = head;
        while(q) {
          if (count == position) {
            p -> next = q -> next;
            delete q;
            listLength--;
            return true;
          }
          p = q;
          q = p -> next;
          count++;
        }
        print("Nothing removed from list");
        return false;
      }
      ~LinkedList() {
        node *p = head;
        node *q = head;
        while(q) {
          p = q;
           q = p -> next;
           if (q) delete p;
        }
      }
  };

  class Drive {
    public:
      enum DriveType {Mecanum = 4, StdX = 4, StdOmni = 4, CustomX = 6, CustomOmni = 6 };
      int type;
      LinkedList v;
      std::map<char,int> vectors;
      void move(int speed) {
        for (int i = 0; i < v.count(); i++) {
          v.retrieve(i) -> mtr -> setValue(speed * v.retrieve(i) -> rel);
        }
      }
      Drive(int type, LinkedList v) {
        this->type = type;
        this->v = v;
      }
      void driveControl(void* ignore) {
        LinkedList mtrs = *new LinkedList();
        mtrs.makeAndInsertNode(new DriveMotor(4), 1);
        mtrs.makeAndInsertNode(new DriveMotor(7), 1);
        mtrs.makeAndInsertNode(new DriveMotor(9), -1);
        mtrs.makeAndInsertNode(new DriveMotor(3), -1);
        Drive driveSet = *new Drive(4, mtrs);
        while (1) {
          driveSet.move(drive);
        }
      }

  };

}

#endif
