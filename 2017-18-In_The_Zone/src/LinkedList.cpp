#include <main.h>
using namespace GeneralRobotics;
typedef struct _Node {
  DriveMotor* mtr;
  int rel;
  Node* next;
};

Node* head;
int listLength;
LinkedList::LinkedList() {
  head -> mtr = NULL;
  head -> rel = 1;
  head -> next = NULL;
  listLength = 0;
}

void LinkedList::makeAndInsertNode(DriveMotor* dm, int relation) {
    Node* newNode = NULL;
    newNode -> mtr = dm;
    newNode -> rel = 1;
    newNode -> next = head;
    insertNode(newNode, 0);
}

int LinkedList::count() {
  return listLength;
}

Node* LinkedList::retrieve(int pos) {
  Node* current = head;
  for(int i = listLength - 1; i > pos && current != NULL; i--) {
    current = current->next;
  }
  return current;
}

bool insertNode(Node *newNode, int position) {
  if ((position <= 0) || (position > listLength + 1)) {
    printf("Index out of bounds");
    return false;
  }
  if (head -> next == NULL) {
    head -> next = newNode;
    listLength++;
    return true;
  }
  int count = 0;
  Node *p = head, *q = head;
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

bool LinkedList::removeNode(int position) {
  if ((position <= 0) || (position > listLength + 1)) {
    print("Index out of bounds");
    return false;
  }
  if(head -> next == NULL) {
    return false;
  }
  int count = 0;
  Node *p = head;
  Node *q = head;
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

LinkedList::~LinkedList() {
  Node *p = head;
  Node *q = head;
  while(q) {
    p = q;
    q = p -> next;
    if (q) delete p;
  }
}
