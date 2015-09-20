#ifndef Node_h
#define Node_h

#include <iostream>

template <class Record, int order>
class Node
{

private:
  // Number of records in each node (if count != 0, node has count + 1 children)
  int count;
  Record *data;
  Node<Record, order>  *children;

public:
  Node();
  virtual ~Node();

};

template <class Record, int order>
Node<Record, order>::Node()
{
  this->count = 0;
  this->data = new Record[order - 1];
  this->children = new Node[order];
}

template <class Record, int order>
Node<Record, order>::~Node()
{
  delete this->data;
  delete this->children;
}

#endif
