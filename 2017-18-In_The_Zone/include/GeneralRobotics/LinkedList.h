#include <GeneralRobotics/Motor.h>
struct node {
  Motor *mtr;
  node *next;
};

class LinkedList {
  private:
    node *head;
    int listLength;
  public:
    LinkedList();
    bool insertNode(node *newNode, int position);
    bool removeNode(int position);
    ~LinkedList();
};
