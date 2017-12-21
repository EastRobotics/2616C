#include <GeneralRobotics/LinkedList.h>
LinkedList::LinkedList() {
  head -> mtr = NULL;
  head -> next = NULL;
  listLength = 0;
}
bool LinkedList::insertNode(node *newNode, int position) {
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
bool LinkedList::removeNode(int position) {
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
LinkedList::~LinkedList() {
  node *p = head;
  node *q = head;
  while(q) {
    p = q;
     q = p -> next;
     if (q) delete p;
  }
}
