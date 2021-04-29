
#ifndef LINKED_STACK
#define LINKED_STACK

#include <string>
#include <iostream>
using namespace std;

class Node
{
public:
  Node()
  {
    data = "";
    prev = NULL;
  }
  Node(string item, Node *previous = NULL)
  {
    data = item;
    prev = previous;
  }
  string data;
  Node *prev;
};

class LinkedStack
{
 public:
  LinkedStack()
  {
    currentNode = NULL;
  }
  void push(string);
  string pop();
  string topEl();
  bool isEmpty();
private:
  Node *currentNode;
};

#endif
