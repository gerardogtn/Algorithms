#ifndef BTree_h
#include <iostream>
#include "Node.h"

template <class Record, int order>
class BTree
{
private:
  Node<Record, order> * root;

  bool recursiveSearch(Node<Record, order> * current, Record target);
  Node<Record, order> * getNode(Record target);
  bool searchNode(Node<Record, order> * current, Record target, int & position);

public:
  BTree();
  virtual ~BTree();

  bool search(Record target);
  Node<Record, order> * getNode(Node<Record, order> * current, Record target);


};

template <class Record, int order>
BTree<Record, order>::BTree()
{
  this->root = nullptr;
}

template <class Record, int order>
BTree<Record, order>::~BTree()
{
  if (root){
    delete root;
  }
}

// REQUIRES: None.
// MODIFIES: None.
// EFFECTS: Returns true if target was found. (public method)
template <class Record, int order>
bool BTree<Record, order>::search(Record target)
{
  return recursiveSearch(root, target);
}

// REQUIRES: None.
// MODIFIES: None.
// EFFECTS: Returns true if target was found. (private method)
template <class Record, int order>
bool BTree<Record, order>::recursiveSearch(Node<Record, order> * current, Record target){
  Node<Record, order> * output;
  output = getNode(target);
  if (output)
  {
    return true;
  }
  else
  {
    return false;
  }
}

// REQUIRES: None.
// MODIFIES: None.
// EFFECTS: If a node with target exists, return the node. Else return nullptr.
template <class Record, int order>
Node<Record, order> * BTree<Record, order>::getNode(Record target)
{
  return getNode(root, target);
}

// REQUIRES: None.
// MODIFIES: None.
// EFFECTS: If a node with target exists, return the node. Else return nullptr.
template <class Record, int order>
Node<Record, order> * BTree<Record, order>::getNode(Node<Record, order> * current, Record target)
{
  Node<Record, order> * output = nullptr;
  bool isPresent = false;
  int position;

  while (current && !isPresent)
  {
    isPresent = searchNode(current, target, position);
    current = current->getChildren(position);
  }

  return output;
}

// REQUIRES: None.
// MODIFIES: position.
// EFFECTS: Returns true if target is found in array. And modifies position to
// indicate the position where target would be located if the invariants hold.
// NOTE: the search is sequential. Since order is small.
template <class Record, int order>
bool BTree<Record, order>::searchNode(Node<Record, order> * current, Record target, int & position)
{
  position = 0;
  while(position < current->getCount() && target > current->getChildren(position))
  {
    position++;
  }

  return position < current->getCount() && target == current->getChildren(position);
}

// TODO: Add getChildren, and getCount methods to Node.h.


#define  BTree_h
#endif
