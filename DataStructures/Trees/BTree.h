#ifndef BTree_h
#include <iostream>
#include "Node.h"
#include "OverflowException.cpp"

template <class Record, int order>
class BTree
{
private:
  Node<Record, order> * root;

  Node<Record, order> * getNode(Record target);

  bool searchTree(Node<Record, order> * current, Record target);
  bool searchNode(Node<Record, order> * current, const Record & target, int & position);

  void pushDown(Node<Record, order> * current, const Record & newEntry,
      Record & median, Node<Record, order> * &rightBranch);

  void push(Node<Record, order> * current, const Record & entry,
      Node<Record, order> * rightBranch, int position);

  void splitNode(Node<Record, order> * current, const Record & extraEntry,
      Node<Record, order> * extraBranch, int position,
      Node<Record, order> *  &rightHalf, Record & median);

  void printNode(Node<Record, order> * current);

public:
  BTree();
  virtual ~BTree();

  bool search(Record target);
  Node<Record, order> * getNode(Node<Record, order> * current, Record target);

  void insert(const Record & newEntry);

  void printTree();
};

template <class Record, int order>
BTree<Record, order>::BTree()
{
  this->root = new Node<Record, order>();
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
// EFFECTS: Returns true if target was found.
template <class Record, int order>
bool BTree<Record, order>::search(Record target)
{
  return searchTree(root, target);
}

// REQUIRES: None.
// MODIFIES: None.
// EFFECTS: Returns true if target was found.
template <class Record, int order>
bool BTree<Record, order>::searchTree(Node<Record, order> * current, Record target){
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

// REQUIRES: current is in BTree or is nullptr.
// MODIFIES: None.
// EFFECTS: If a node with target exists, return the node. Else return nullptr.
template <class Record, int order>
Node<Record, order> * BTree<Record, order>::getNode(Node<Record, order> * current, Record target)
{
  bool isPresent = false;
  int position;

  while (current)
  {
    isPresent = searchNode(current, target, position);
    if (!isPresent)
    {
      current = current->getChildren(position);
    }
    else
    {
      break;
    }
  }

  return current;
}


// REQUIRES: current is a node in BTree. (not nullptr).
// MODIFIES: position.
// EFFECTS: Returns true if target is found in array. And modifies position to
// indicate the position where target would be located if the invariants hold.
// NOTE: Since order is small, sequential search is used. For large orders, use
// NOTE: binary search.
template <class Record, int order>
bool BTree<Record, order>::searchNode(Node<Record, order> * current,
    const Record & target, int & position)
{
  position = 0;
  while(position < current->getCount() && target > current->getData(position))
  {
    position++;
  }

  bool found = position < current->getCount() && target == current->getData(position);
  return found;
}


// REQUIRES: None.
// MODIFIES: this.
// EFFECTS: If inserting newEntry doesn't generate an overflow, insert
// newEntry. Else handle overflow AND insert newEntry. If newEntry is duplicate
// do nothing.
template <class Record, int order>
void BTree<Record, order>::insert(const Record & newEntry)
{
  Record median;
  Node<Record, order> * rightBranch = nullptr;

  try
  {
    pushDown(root, newEntry, median, rightBranch);
  }
  catch(OverflowException e)
  {
    Node<Record, order> * newRoot = new Node<Record, order>();
    newRoot->setCount(1);
    newRoot->setData(0, median);
    newRoot->setChildren(0, root);
    newRoot->setChildren(1, rightBranch);
    this->root = newRoot;
  }
}

// REQUIRES: current is nullptr or is in tree.
// MODIFIES: this.
// EFFECTS: If newEntry is duplicate, do nothing. If there is no insertion
// overflow, insert. Else an OverflowException is thrown.
template <class Record, int order>
void BTree<Record, order>::pushDown(Node<Record, order> * current,
                                    const Record & newEntry,
                                    Record & median,
                                    Node<Record,order> * &rightBranch)
{
  int position;
  if (current == nullptr)
  {
    median = newEntry;
    rightBranch = nullptr;
    throw  OverflowException();
  }
  else
  {
    if (!searchNode(current, newEntry, position))
    {
      Record extraEntry;
      Node<Record, order> * extraBranch = nullptr;

      try
      {
        pushDown(current->getChildren(position), newEntry, extraEntry, extraBranch);
      }
      catch (OverflowException e)
      {
        if (current->getCount() < order - 1)
        {
          push(current, extraEntry, extraBranch, position);
        }
        else
        {
          splitNode(current,extraEntry, extraBranch, position, rightBranch, median);
          std::cout << "Right branch: " << *rightBranch << std::endl;
          throw OverflowException();
        }
      }
    }
  }
  return;
}


// REQUIRES: current points to a node in BTree, *current is not full, and
// entry belongs in *current at index position.
// MODIFIES: this.
// EFFECTS: Insert entry with its right branch at position.
template <class Record, int order>
void BTree<Record, order>::push(Node<Record, order> * current,
    const Record & entry, Node<Record, order> * rightBranch, int position)
{
  // shift data to the right
  for (int i = current->getCount(); i > position; i--)
  {
    current->setData(i, current->getData(i - 1));
    current->setChildren(i + 1, current->getChildren(i));
  }

  current->setData(position, entry);
  current->setChildren(position + 1, rightBranch);
  current->incrementCount();
}

// REQUIRES: Current is full and points to a node in BTree. If there were room,
// the extraEntry with its right-hand pointer extraBranch would belong in
// *current at position. And 0 <= position < order.
// MODIFIES: this.
// EFFECTS: The node current with extraEntry and extraBranch at position are
// divided into nodes *current and *rightHalf separated by median.

template <class Record, int order>
void BTree<Record, order>::splitNode(Node<Record, order> * current,
                                     const Record & extraEntry,
                                     Node<Record, order> * extraBranch,
                                     int position,
                                     Node<Record, order> *  &rightHalf,
                                     Record & median)
{
  rightHalf = new Node<Record, order>();
  int mid = order / 2;

  if (position <= mid)
  {
    for (int i = mid; i < order -1; i++)
    {
      rightHalf->setData(i - mid, current->getData(i));
      rightHalf->setChildren(i - mid + 1, current->getChildren(i+1));
    }
    current->setCount(mid);
    rightHalf->setCount(order - 1 - mid);
    push(current, extraEntry, extraBranch, position);
  }
  else
  {
    std::cout << "Insertando a la derecha+++++++++++" << std::endl;
    mid++;
    for (int i = mid; i < order -1; i++)
    {
      rightHalf->setData(i - mid, current->getData(i));
      rightHalf->setChildren(i - mid + 1, current->getChildren(i+1));
    }
    current->setCount(mid);
    rightHalf->setCount(order - 1 - mid);
    push(rightHalf, extraEntry, extraBranch, position - mid);
  }

  median = current->getData(current->getCount() - 1);
  rightHalf->setChildren(0, current->getChildren(current->getCount()));
  current->decrementCount();
}

template <class Record, int order>
void BTree<Record, order>::printTree()
{
  std::cout << "++++++++++++ Imprimiendo arbol:" << std::endl;
  printNode(root);
}


template <class Record, int order>
void BTree<Record, order>::printNode(Node<Record, order> * current)
{
  if (current)
  {
    std::cout << *current << std::endl;
    for (int i = 0; i < order; i++)
    {
      printNode(current->getChildren(i));
    }
  }
}
#define  BTree_h
#endif
