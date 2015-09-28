#ifndef TwoThreeTree_h
#define  TwoThreeTree_h

#include <iostream>
#include "BTree.h"

template <class Record>
class TwoThreeTree
{

private:
  BTree<Record, 3> * tree = nullptr;

public:
  TwoThreeTree();
  ~TwoThreeTree();

  void insert(const Record & newEntry);
  bool remove(const Record & target);
  bool search(const Record & target);
  void printTree();
};

template <class Record>
TwoThreeTree<Record>::TwoThreeTree()
{
  tree = new BTree<Record, 3>();
}

template <class Record>
TwoThreeTree<Record>::~TwoThreeTree()
{
  if (tree)
    delete tree;
}

template <class Record>
void TwoThreeTree<Record>::insert(const Record & newEntry)
{
  tree->insert(newEntry);
}

template <class Record>
bool TwoThreeTree<Record>::remove(const Record & target)
{
  return tree->remove(target);
}

template <class Record>
bool TwoThreeTree<Record>::search(const Record & target)
{
  return tree->search(target);
}

template <class Record>
void TwoThreeTree<Record>::printTree()
{
  tree->printTree();
}

#endif
