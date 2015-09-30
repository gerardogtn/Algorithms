#ifndef BTreeDisk_h
#define  BTreeDisk_h
#include <iostream>
#include "NodeDisk.h"
#include "OverflowException.cpp"

template <class Record, int order>
class BTreeDisk
{
private:
  NodeDisk<Record, order> * _current;
  std::string rootName;

  std::string getNode(Record & target);

  bool searchTree(std::string currentId, Record & target);
  bool searchNode(const Record & target, int & position);

  void pushDown(std::string currentId, const Record & newEntry,
      Record & median, std::string & rightBranch);
  void push(const Record & entry, std::string rightBranch, int position);
  void push(NodeDisk<Record, order> * &current, const Record & entry,
      std::string rightBranch, int position);
  void splitNode(std::string currentId, const Record & extraEntry, std::string extraBranch,
      int position, std::string & rightHalf, Record & median);

  bool remove(std::string currentId, const Record & target);
  void removeData(int position);
  void copyInPredecessor(std::string currentId, int position);
  void restore(std::string currentId, int position);
  void moveLeft(std::string currentId, int position);
  void moveRight(std::string currentId, int position);
  void combine(int position);

  void printAscending(std::string currentId);
  void printDescending(std::string currentId);

  void load(std::string nodeId);
  void load(NodeDisk<Record, order> * & current, std::string nodeId);

public:
  BTreeDisk();
  virtual ~BTreeDisk();

  bool search(Record target);
  std::string getNode(std::string currentFile, Record target);
  void insert(const Record & newEntry);
  bool remove(const Record & target);

  void load();

  void printAscending();
  void printDescending();

  bool isBst(){return false;};
  bool isAvl(){return false;};
  bool isRedBlackTree(){return false;};
  bool isBTree(){return true;};
  bool isTwoThreeTree(){return order==3;};

};

template <class Record, int order>
BTreeDisk<Record, order>::BTreeDisk()
{
  _current = nullptr;
  rootName = "NaN";
}

template <class Record, int order>
BTreeDisk<Record, order>::~BTreeDisk()
{
  if (_current){
    delete _current;
  }
}

// REQUIRES: None.
// MODIFIES: None.
// EFFECTS: Returns true if target was found.
template <class Record, int order>
bool BTreeDisk<Record, order>::search(Record target)
{
  return searchTree(rootName, target);
}

// REQUIRES: None.
// MODIFIES: None.
// EFFECTS: Returns true if target was found.
template <class Record, int order>
bool BTreeDisk<Record, order>::searchTree(std::string currentId, Record &target){
  std::string outputFile;
  outputFile = getNode(target);
  if (outputFile != "NaN")
    return true;
  else
    return false;
}

// REQUIRES: None.
// MODIFIES: None.
// EFFECTS: If a node with target exists, return the node. Else return nullptr.
template <class Record, int order>
std::string BTreeDisk<Record, order>::getNode(Record &target)
{
  return getNode(rootName, target);
}

// REQUIRES: current is in BTree or is nullptr.
// MODIFIES: None.
// EFFECTS: If a node with target exists, return the node. Else return nullptr.
template <class Record, int order>
std::string BTreeDisk<Record, order>::getNode(std::string currentId, Record target)
{
  bool isPresent = false;
  int position;

  while (currentId != "NaN")
  {
    load(currentId);
    isPresent = searchNode(target, position);
    if (!isPresent)
    {
      currentId = _current->getChildren(position);
    }
    else
    {
      break;
    }
  }

  return currentId;
}


// REQUIRES: current is the node to be searched.
// MODIFIES: position.
// EFFECTS: Returns true if target is found in array. And modifies position to
// indicate the position where target would be located if the invariants hold.
// NOTE: Since order is small, sequential search is used. For large orders, use
// NOTE: binary search.
template <class Record, int order>
bool BTreeDisk<Record, order>::searchNode(const Record & target, int & position)
{
  position = 0;
  while(position < _current->getCount() && target > _current->getData(position))
  {
    position++;
  }

  bool found = position < _current->getCount() && target == _current->getData(position);
  return found;
}


// REQUIRES: None.
// MODIFIES: this.
// EFFECTS: If inserting newEntry doesn't generate an overflow, insert
// newEntry. Else handle overflow AND insert newEntry. If newEntry is duplicate
// do nothing.
template <class Record, int order>
void BTreeDisk<Record, order>::insert(const Record & newEntry)
{
  Record median;
  std::string rightBranch = "NaN";

  try
  {
    pushDown(rootName, newEntry, median, rightBranch);
  }
  catch(OverflowException e)
  {
    NodeDisk<Record, order> * newRoot = new NodeDisk<Record, order>();
    newRoot->setCount(1);
    newRoot->setData(0, median);
    newRoot->setChildren(0, rootName);
    newRoot->setChildren(1, rightBranch);
    this->rootName = newRoot->getFileName();
    cout << "root:" << this->rootName << endl;
    delete newRoot;
  }
}

// REQUIRES: current is nullptr or is in tree.
// MODIFIES: this.
// EFFECTS: If newEntry is duplicate, do nothing. If there is no insertion
// overflow, insert. Else an OverflowException is thrown.
template <class Record, int order>
void BTreeDisk<Record, order>::pushDown(std::string currentId,
                                    const Record & newEntry,
                                    Record & median,
                                    std::string & rightBranch)
{
  int position;
  if (currentId == "NaN")
  {
    median = newEntry;
    rightBranch = "NaN";
    throw  OverflowException();
  }
  else
  {
    load(currentId);
    if (!searchNode(newEntry, position) && newEntry != 0)
    {
      Record extraEntry;
      std::string extraBranch = "NaN";

      try
      {
        pushDown(_current->getChildren(position), newEntry, extraEntry, extraBranch);
        load(currentId);
      }
      catch (OverflowException e)
      {
        load(currentId);
        if (_current->getCount() < order - 1)
        {
          push(extraEntry, extraBranch, position);
        }
        else
        {
          splitNode(currentId, extraEntry, extraBranch, position, rightBranch, median);
          throw OverflowException();
        }
      }
    }
  }
  return;
}


// REQUIRES: _current is not full and entry belongs in _current at index position.
// MODIFIES: this.
// EFFECTS: Insert entry with its right branch at position.
template <class Record, int order>
void BTreeDisk<Record, order>::push(const Record & entry,
    std::string rightBranch, int position)
{
  push(_current, entry, rightBranch, position);
}

// REQUIRES: _current is not full and entry belongs in _current at index position.
// MODIFIES: this.
// EFFECTS: Insert entry with its right branch at position.
template <class Record, int order>
void BTreeDisk<Record, order>::push(NodeDisk<Record, order> * & current,
    const Record & entry, std::string rightBranch, int position)
{
  // shift data to the right
  for (int i = current->getCount(); i > position; i--)
  {
    current->setData(i, _current->getData(i - 1));
    current->setChildren(i + 1, _current->getChildren(i));
  }

  current->setData(position, entry);
  current->setChildren(position + 1, rightBranch);
  current->incrementCount();
}

// REQUIRES: Current is full and points to a node in BTreeDisk. If there were room,
// the extraEntry with its right-hand pointer extraBranch would belong in
// *current at position. And 0 <= position < order.
// MODIFIES: this.
// EFFECTS: The node current with extraEntry and extraBranch at position are
// divided into nodes *current and *rightHalf separated by median.

template <class Record, int order>
void BTreeDisk<Record, order>::splitNode(std::string currentId,
                                     const Record & extraEntry,
                                     std::string extraBranch,
                                     int position,
                                     std::string & rightName,
                                     Record & median)
{
  load(currentId);
  NodeDisk<Record, order> * rightHalf = new NodeDisk<Record, order>();
  rightName = rightHalf->getFileName();
  int mid = order / 2;

  if (position <= mid)
  {
    for (int i = mid; i < order -1; i++)
    {
      rightHalf->setData(i - mid, _current->getData(i));
      rightHalf->setChildren(i - mid + 1, _current->getChildren(i+1));
    }
    _current->setCount(mid);
    rightHalf->setCount(order - 1 - mid);
    push(extraEntry, extraBranch, position);
  }
  else
  {
    mid++;
    for (int i = mid; i < order -1; i++)
    {
      rightHalf->setData(i - mid, _current->getData(i));
      rightHalf->setChildren(i - mid + 1, _current->getChildren(i+1));
    }
    _current->setCount(mid);
    rightHalf->setCount(order - 1 - mid);
    push(rightHalf, extraEntry, extraBranch, position - mid);
  }

  median = _current->getData(_current->getCount() - 1);
  rightHalf->setChildren(0, _current->getChildren(_current->getCount()));
  _current->decrementCount();

  //delete rightHalf
}

// REQUIRES: None.
// MODIFIES: this.
// EFFECTS:Returns true if delete was succesful. Else (if target was not found)
// Return false.
// TODO: When deleting oldRoot a malloc error occurs.
template <class Record, int order>
bool BTreeDisk<Record, order>::remove(const Record & target)
{
  bool output = remove(rootName, target);

  load(rootName);
  if (_current && _current->getCount() == 0)
  {
    std::string oldRoot = rootName;
    rootName = _current->getChildren(0);
    load();
    _current->setChildren(0, "NaN");
  }

  return output;
}

// REQUIRES: current is nullptr or belongs to tree.
// MODIFIES: this.
// EFFECTS:Returns true if delete was succesful. Else (if target was not found)
// Return false.
template <class Record, int order>
bool BTreeDisk<Record, order>::remove(std::string currentId,
    const Record & target)
{
  load(currentId);
  int position;
  bool result = false;

  if (_current == nullptr)
    return false;
  else
  {
    if (searchNode(target, position))
    {
      result = true;
      if (_current->getChildren(position) != "NaN")
      {
        copyInPredecessor(currentId, position);
        remove(_current->getChildren(position), _current->getData(position));
        load(currentId);
      }
      else
      {
        removeData(position);
      }
    }
    else
    {
      result = remove(_current->getChildren(position), target);
      load(currentId);
    }

    if (_current->getChildren(position) != "NaN")
    {
      load(_current->getChildren(position));
      if (_current->getCount() < (order - 1)/2)
        restore(currentId, position);
      load(currentId);
    }
  }

  return result;
}

// REQUIRES: current is not nullptr.
// MODIFIES: current
// EFFECTS: Shifts current->data one position to the right starting from position.
template <class Record, int order>
void BTreeDisk<Record, order>::removeData(int position)
{
  for (int i = position; i < _current->getCount() - 1; i++)
    _current->setData(i, _current->getData(i + 1));

  _current->decrementCount();
}


// REQUIRES: current is in tree and not a leaf node.
// MODIFIES: this.
// EFFECTS: Replace current->getData(position) with current's predecessor.
template <class Record, int order>
void BTreeDisk<Record, order>::copyInPredecessor(std::string currentId,
    int position)
{
  load(_current->getChildren(position));

  while (_current->getChildren(_current->getCount()) != "NaN")
    load(_current->getChildren(_current->getCount()));

  Record data = _current->getData(_current->getCount() - 1);

  load(currentId);
  _current->setData(position, data);
}


// REQUIRES: current is in tree and is not a leaf node. Its children at
// position doesn't have enough entries.
// MODIFIES: this
// EFFECTS: An entry is moved to children at position to have enough entries.
// TODO: continue here.
template <class Record, int order>
void BTreeDisk<Record, order>::restore(std::string currentId,
    int position)
{
  load(currentId);
  load(_current->getChildren(1));
  int count = _current->getCount();
  load(currentId);

  if (position == 0)
  {
    if (count > (order - 1) / 2)
      moveLeft(currentId, 1);
    else
      combine(1);
  }
  else if (position == count)
  {
    load(_current->getChildren(position - 1));
    count = _current->getCount();
    load(currentId);
    if (count > (order - 1) / 2)
      moveRight(currentId, position - 1);
    else
      combine(position);
  }
  else
  {
    load(_current->getChildren(position - 1));
    count = _current->getCount();
    load(currentId);

    if (count > (order - 1) / 2)
      return moveRight(currentId, position - 1);

    load(_current->getChildren(position + 1));
    count = _current->getCount();
    load(currentId);

    if (count > (order - 1) / 2)
      moveLeft(currentId, position + 1);
    else
      combine(position);
  }
}

// REQUIRES: current's child at position has more than enough entries, and
// current's child at position -1 doesn't have enough entries.
// MODIFIES: current
// EFFECTS: Move an entry in entry's child at position to entry's child at
// position -1
template <class Record, int order>
void BTreeDisk<Record, order>::moveLeft(std::string currentId, int position)
{
  load(currentId);
  std::string leftBranch = _current->getChildren(position - 1);
  std::string rightBranch = _current->getChildren(position);
  Record lastItem = _current->getData(position - 1);

  load(leftBranch);
  _current->setData(_current->getCount(), lastItem);
  _current->incrementCount();
  int leftCount = _current->getCount();

  load(rightBranch);
  std::string rightFirstChild = _current->getChildren(0);
  Record rightFirstData = _current->getData(0);
  _current->decrementCount();

  load(currentId);
  _current->setChildren(leftCount, rightFirstChild);
  _current->setData(position - 1, rightFirstData);


  load(rightBranch);
  // move entries to fill hole
  for (int i = 0; i < _current->getCount(); i++)
  {
    _current->setData(i, _current->getData(i + 1));
    _current->setChildren(i, _current->getChildren(i + 1));
  }

  _current->setChildren(_current->getCount(),
      _current->getChildren(_current->getCount() + 1));
}

template <class Record, int order>
void BTreeDisk<Record, order>::moveRight(std::string currentId,
    int position)
{
  load(currentId);
  NodeDisk<Record, order> * leftBranch = new NodeDisk<Record, order>();
  NodeDisk<Record, order> * rightBranch = new NodeDisk<Record, order>();

  load(leftBranch, _current->getChildren(position));
  load(leftBranch, _current->getChildren(position + 1));

  rightBranch->setChildren(rightBranch->getCount() + 1,
      rightBranch->getChildren(rightBranch->getCount()));

  // move entries to fill hole
  for (int i = rightBranch->getCount(); i > 0 ; i--)
  {
    rightBranch->setData(i, rightBranch->getData(i - 1));
    rightBranch->setChildren(i, rightBranch->getChildren(i - 1));
  }

  rightBranch->incrementCount();
  rightBranch->setData(0, _current->getData(position));

  rightBranch->setChildren(0, leftBranch->getChildren(leftBranch->getCount()));
  leftBranch->decrementCount();

  _current->setData(position, leftBranch->getData(leftBranch->getCount()));
}


// REQUIRES: current is a node in Tree such that both child at position and
// child at position - 1 dont have enough entries.
// MODIFIES: this
// EFFECTS: The children at position and position - 1 are combined.
template <class Record, int order>
void BTreeDisk<Record, order>::combine(int position)
{
  NodeDisk<Record, order> * leftBranch;
  NodeDisk<Record, order> * rightBranch;

  load(leftBranch, _current->getChildren(position - 1));
  load(rightBranch, _current->getChildren(position));

  leftBranch->setData(leftBranch->getCount(), _current->getData(position - 1));
  leftBranch->incrementCount();
  leftBranch->setChildren(leftBranch->getCount(), rightBranch->getChildren(0));

  for (int i = 0; i < rightBranch->getCount(); i++)
  {
    leftBranch->setData(leftBranch->getCount(), rightBranch->getData(i));
    leftBranch->incrementCount();
    leftBranch->setChildren(leftBranch->getCount(), rightBranch->getChildren(i + 1));
  }

  _current->decrementCount();

  for (int i = position - 1; i < _current->getCount(); i++)
  {
    _current->setData(i, _current->getData(i + 1));
    _current->setChildren(i + 1, _current->getChildren(i +  2));
  }

  //delete rightBranch;
  //delete leftBranch;
}

template <class Record, int order>
void BTreeDisk<Record, order>::load()
{
  return load(this->rootName);
}

template <class Record, int order>
void BTreeDisk<Record, order>::load(NodeDisk<Record, order> * &node,
    std::string fileName)
{
  if (fileName == "NaN")
  {
    node = nullptr;
    return;
  }

  ifstream currentFile(fileName);
  int count;
  Record data[order - 1];
  std::string children[order];

  currentFile >> count;

  for (int i = 0; i < order - 1; i++)
    currentFile >> data[i];

  for (int i = 0; i < order; i++)
    currentFile >> children[i];

  currentFile.close();

  node = new NodeDisk<Record, order>(count, data, children, fileName);
}

template <class Record, int order>
void BTreeDisk<Record, order>::load(std::string fileName)
{
  load(_current, fileName);
}

template <class Record, int order>
void BTreeDisk<Record, order>::printAscending()
{
  printAscending(rootName);
  std::cout << std::endl;
}

template <class Record, int order>
void BTreeDisk<Record, order>::printDescending()
{
  printDescending(rootName);
  std::cout << std::endl;
}

template <class Record, int order>
void BTreeDisk<Record, order>::printAscending(std::string currentId)
{
  NodeDisk<Record, order> * temp;
  load(temp, currentId);

  if (temp)
  {
    for (int i = 0; i < order - 1; i++)
    {
      printAscending(temp->getChildren(i));
      if (i < temp->getCount())
        std::cout << temp->getData(i) << " ";
    }
    printAscending(temp->getChildren(order - 1));
  }

  delete temp;
}

template <class Record, int order>
void BTreeDisk<Record, order>::printDescending(std::string currentId)
{

  NodeDisk<Record, order> * temp;
  load(temp, currentId);

  if (temp)
  {
    printDescending(temp->getChildren(order - 1));
    for (int i = order - 2; i >= 0; i--)
    {
      if (i < temp->getCount())
        std::cout << temp->getData(i) << " ";
      printDescending(temp->getChildren(i));
    }
  }
  delete temp;
}

#endif
