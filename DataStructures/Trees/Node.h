#ifndef Node_h
#define Node_h

#include <iostream>

template <class Record, int order>
class Node
{

private:
  // Number of records in each node (if count != 0, node has count + 1 children)
  int count;
  Record **data;
  Node<Record, order>  **children;

public:
  Node();
  virtual ~Node();

};

template <class Record, int order>
Node<Record, order>::Node()
{
  this->count = 0;
  this->data = new Record *[order - 1];
  this->children = new Node *[order];

  for (int i = 0; i < order - 1; i++){
    data[i] = nullptr;
    children[i] = nullptr;
  }
  children[order - 1] = nullptr;
}

template <class Record, int order>
Node<Record, order>::~Node()
{
  for (int i = 0; i < order - 1; i++)
  {
    if (data[i]){
      delete data[i];
    }
    if (children[i]){
      delete children[i];
    }
  }

  if (children[order - 1]){
    delete children[order - 1];
  }

  delete[] data;
  delete[] children;
}

#endif
