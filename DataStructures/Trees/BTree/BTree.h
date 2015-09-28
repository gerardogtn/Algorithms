#ifndef BTree_h
#define  BTree_h
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

  bool remove(Node<Record, order> * current, const Record & target);
  void removeData(Node<Record, order> * current, int position);
  void copyInPredecessor(Node<Record, order> * current, int position);
  void restore(Node<Record, order> * current, int position);
  void moveLeft(Node<Record, order> * current, int position);
  void moveRight(Node<Record, order> * current, int position);
  void combine(Node<Record, order> * current, int position);

  void printNode(Node<Record, order> * current);

public:
  BTree();
  virtual ~BTree();

  bool search(Record target);
  Node<Record, order> * getNode(Node<Record, order> * current, Record target);

  void insert(const Record & newEntry);
  bool remove(const Record & target);

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

// REQUIRES: None.
// MODIFIES: this.
// EFFECTS:Returns true if delete was succesful. Else (if target was not found)
// Return false.
// TODO: When deleting oldRoot a malloc error occurs.
template <class Record, int order>
bool BTree<Record, order>::remove(const Record & target){
  bool output = remove(root, target);

  if (root && root->getCount() == 0)
  {
    Node<Record, order> * oldRoot = root;
    root = root->getChildren(0);
    oldRoot->setChildren(0, nullptr);
    //delete oldRoot;
  }

  return output;
}

// REQUIRES: current is nullptr or belongs to tree.
// MODIFIES: this.
// EFFECTS:Returns true if delete was succesful. Else (if target was not found)
// Return false.
template <class Record, int order>
bool BTree<Record, order>::remove(Node<Record, order> * current,
    const Record & target)
{
  int position;
  bool result = false;

  if (current == nullptr)
  {
    return false;
  }
  else
  {
    if (searchNode(current, target, position))
    {
      result = true;
      if (current->getChildren(position))
      {
        copyInPredecessor(current, position);
        remove(current->getChildren(position), current->getData(position));
      }
      else
      {
        removeData(current, position);
      }
    }
    else
    {
      result = remove(current->getChildren(position), target);
    }

    if (current->getChildren(position))
    {
      if (current->getChildren(position)->getCount() < (order - 1)/2)
      {
        restore(current, position);
      }
    }
  }

  return result;
}

// REQUIRES: current is not nullptr.
// MODIFIES: current
// EFFECTS: Shifts current->data one position to the right starting from position.
template <class Record, int order>
void BTree<Record, order>::removeData(Node<Record, order> * current,
    int position)
{
  for (int i = position; i < current->getCount() - 1; i++)
  {
    current->setData(i, current->getData(i + 1));
  }
  current->decrementCount();
}


// REQUIRES: current is in tree and not a leaf node.
// MODIFIES: this.
// EFFECTS: Replace current->getData(position) with current's predecessor.
template <class Record, int order>
void BTree<Record, order>::copyInPredecessor(Node<Record, order> * current,
    int position)
{
  Node<Record, order> * leaf = current->getChildren(position);

  while (leaf->getChildren(leaf->getCount()))
  {
    leaf = leaf->getChildren(leaf->getCount());
  }

  current->setData(position, leaf->getData(leaf->getCount() - 1));
}


// REQUIRES: current is in tree and is not a leaf node. Its children at
// position doesn't have enough entries.
// MODIFIES: this
// EFFECTS: An entry is moved to children at position to have enough entries.
template <class Record, int order>
void BTree<Record, order>::restore(Node<Record, order> * current,
    int position)
{
  if (position == 0)
  {
    if (current->getChildren(1)->getCount() > (order - 1) / 2)
      moveLeft(current, 1);
    else
      combine(current, 1);
  }
  else if (position == current->getCount())
  {
    if (current->getChildren(position - 1)->getCount() > (order - 1) / 2)
      moveRight(current, position - 1);
    else
      combine(current, position);
  }
  else
  {
    if (current->getChildren(position - 1)->getCount() > (order - 1) / 2)
      moveRight(current, position - 1);
    else if (current->getChildren(position + 1)->getCount() > (order - 1) / 2)
      moveLeft(current, position + 1);
    else
      combine(current, position);
  }
}

// REQUIRES: current's child at position has more than enough entries, and
// current's child at position -1 doesn't have enough entries.
// MODIFIES: current
// EFFECTS: Move an entry in entry's child at position to entry's child at
// position -1
template <class Record, int order>
void BTree<Record, order>::moveLeft(Node<Record, order> * current,
    int position)
{
  Node<Record, order> * leftBranch = current->getChildren(position - 1);
  Node<Record, order> * rightBranch = current->getChildren(position);

  leftBranch->setData(leftBranch->getCount(), current->getData(position - 1));
  leftBranch->incrementCount();
  leftBranch->setChildren(leftBranch->getCount(), rightBranch->getChildren(0));

  current->setData(position - 1, rightBranch->getData(0));
  rightBranch->decrementCount();

  // move entries to fill hole
  for (int i = 0; i < rightBranch->getCount(); i++)
  {
    rightBranch->setData(i, rightBranch->getData(i + 1));
    rightBranch->setChildren(i, rightBranch->getChildren(i + 1));
  }

  rightBranch->setChildren(rightBranch->getCount(),
      rightBranch->getChildren(rightBranch->getCount() + 1));
}

template <class Record, int order>
void BTree<Record, order>::moveRight(Node<Record, order> * current,
    int position)
{
  Node<Record, order> * leftBranch = current->getChildren(position);
  Node<Record, order> * rightBranch = current->getChildren(position + 1);

  rightBranch->setChildren(rightBranch->getCount() + 1,
      rightBranch->getChildren(rightBranch->getCount()));

  // move entries to fill hole
  for (int i = rightBranch->getCount(); i > 0 ; i--)
  {
    rightBranch->setData(i, rightBranch->getData(i - 1));
    rightBranch->setChildren(i, rightBranch->getChildren(i - 1));
  }

  rightBranch->incrementCount();
  rightBranch->setData(0, current->getData(position));

  rightBranch->setChildren(0, leftBranch->getChildren(leftBranch->getCount()));
  leftBranch->decrementCount();

  current->setData(position, leftBranch->getData(leftBranch->getCount()));
}


// REQUIRES: current is a node in Tree such that both child at position and
// child at position - 1 dont have enough entries.
// MODIFIES: this
// EFFECTS: The children at position and position - 1 are combined.
template <class Record, int order>
void BTree<Record, order>::combine(Node<Record, order> * current,
    int position)
{
  Node<Record, order> * leftBranch = current->getChildren(position - 1);
  Node<Record, order> * rightBranch = current->getChildren(position);

  leftBranch->setData(leftBranch->getCount(), current->getData(position - 1));
  leftBranch->incrementCount();
  leftBranch->setChildren(leftBranch->getCount(), rightBranch->getChildren(0));

  for (int i = 0; i < rightBranch->getCount(); i++)
  {
    leftBranch->setData(leftBranch->getCount(), rightBranch->getData(i));
    leftBranch->incrementCount();
    leftBranch->setChildren(leftBranch->getCount(), rightBranch->getChildren(i + 1));
  }

  current->decrementCount();

  for (int i = position - 1; i < current->getCount(); i++)
  {
    current->setData(i, current->getData(i + 1));
    current->setChildren(i + 1, current->getChildren(i +  2));
  }

  delete rightBranch;
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
#endif
