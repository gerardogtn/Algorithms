#ifndef Node_h
#define Node_h

#include <iostream>
#include "IndexOutOfBoundsException.cpp"

// This class assumes that order is small; as such it uses arrays to store
// data and children. If order were large a list would be prefered.
template <class Record, int order>
class Node
{

private:
  int count;
  Record data[order - 1];
  Node<Record, order>  * children[order];

public:
  Node();
  virtual ~Node();

  int getCount(){return count;};
  Record & getData(const int position);
  Node<Record, order> * getChildren(const int position);

  void setCount(const int count){ this->count = count; };
  void setData(const int position, Record  record);
  void setChildren(const int position, Node<Record, order> * node);

  void incrementCount(){ count++;}
  void decrementCount(){ count--;}

  template <typename T, int n>
  friend std::ostream & operator << (std::ostream & os, Node<T, n>  & node);

};

template <class Record, int order>
Node<Record, order>::Node()
{
  this->count = 0;
  for (int i = 0; i < order; i++)
  {
    children[i] = nullptr;
  }
}

template <class Record, int order>
Node<Record, order>::~Node()
{
  for (int i = 0; i< order; i++){
    if (children[i]){
      delete children[i];
    }
  }
}

// REQUIRES: None.
// MODIFIES: None.
// EFFECTS: If position is valid, returns pointer to children. Else nullptr.
template <class Record, int order>
Node<Record, order> * Node<Record, order>::getChildren(const int position)
{
  if (position < order  && position >= 0)
  {
    return this->children[position];
  }
  else
  {
    throw IndexOutOfBoundsException();
  }
}

// REQUIRES: None.
// MODIFIES: None.
// EFFECTS: If position is valid, returns record. Else throw KeyNotFoundException.
template <class Record, int order>
Record & Node<Record, order>::getData(const int position)
{
  if (position < order - 1 && position >= 0)
  {
    return this->data[position];
  }
  else
  {
    throw IndexOutOfBoundsException();
  }
}

// REQUIRES: None.
// MODIFIES: this.
// EFFECTS: Returns true if data set was succesful, false otherwise.
template <class Record, int order>
void Node<Record, order>::setData(const int position, Record record)
{
  if (position < order - 1 && position >= 0)
  {
    this->data[position] = record;
  }
  else
  {
    throw IndexOutOfBoundsException();
  }
}

// REQUIRES: None.
// MODIFIES: this.
// EFFECTS: Returns true if children set was succesful, false otherwise.
template <class Record, int order>
void Node<Record, order>::setChildren(const int position, Node<Record, order> * node)
{
  if (position < order && position >= 0)
  {
    this->children[position] = node;
  }
  else
  {
    throw IndexOutOfBoundsException();
  }
}

template <class Record, int order>
std::ostream & operator << (std::ostream & os, Node<Record, order>  & node)
{
  for (int i = 0; i < order - 1; i++)
  {
    if (i < node.getCount())
    {
      os << node.getData(i) << " ";
    }
    else
    {
      os << "N ";
    }
  }

  return os;
}


#endif
