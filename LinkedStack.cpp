#include "LinkedStack.h"

void LinkedStack::push(string item)
{
  /* to add new items - insert new node into the list */
  currentNode = new Node(item, currentNode);
}

string LinkedStack::pop()
{
  if (isEmpty())
    return "Error: Stack is empty - pop";
  else
  {
   /* get content of the current node, then switch to
      the previous one */
   Node *tmp = currentNode;
   currentNode = currentNode->prev;
   return tmp->data;
  }
}

string LinkedStack::topEl()
{
  if (isEmpty())
    return "Error: Stack is empty - topEl";
  return currentNode->data;
}

bool LinkedStack::isEmpty()
{
  return currentNode == NULL;
}
