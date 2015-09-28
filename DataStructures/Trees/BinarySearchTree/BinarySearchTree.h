

#ifndef BinarySearchTree_h
#define BinarySearchTree_h

#include "../BinaryTree/BinaryTree.h"

template<class T>
class BinarySearchTree : protected BinaryTree<T>{

private:

  bool search(const T item, BinaryNode<T> * node) const;
  virtual void insert(BinaryNode<T> * item);

  BinaryNode<T> * searchGetNode(const T item) const;
  BinaryNode<T> * searchGetNode(BinaryNode<T> * node, const T item) const;

public:
  BinarySearchTree() {};
  virtual ~BinarySearchTree() {};

  bool search(const T item) const;
  virtual void insert(const T item);
  bool remove(const T item);

  BinaryNode<T> * getSuccessor(BinaryNode<T> * node) const;
  BinaryNode<T> * getPredecessor(BinaryNode<T> * node) const;
};

template <class T>
bool BinarySearchTree<T>::search(const T item) const
{
  return search(item, BinaryTree<T>::root);
}

template <class T>
bool BinarySearchTree<T>::search(const T item, BinaryNode<T> * node) const
{
  BinaryNode<T> * output = searchGetNode(item, node);
  if (output == nullptr)
  {
    return false;
  }
  else
  {
    return true;
  }
}

template <class T>
BinaryNode<T> * BinarySearchTree<T>::searchGetNode(const T item) const
{
  return searchGetNode(item, BinaryTree<T>::root);
}

template <class T>
BinaryNode<T> * BinarySearchTree<T>::searchGetNode(BinaryNode<T> * node, const T item) const
{
  if (node == nullptr)
  {
    return nullptr;
  }
  else
  {
    T nodeValue = node->getInfo();
    if (item == nodeValue)
    {
      return node;
    }
    else if (item < nodeValue)
    {
      return searchGetNode(item, node->getLeft());
    }
    else {
      return searchGetNode(item, node->getRight());
    }
  }
}

template <class T>
void BinarySearchTree<T>::insert(const T item)
{
  this->insertOrder(item);
}

template <class T>
void BinarySearchTree<T>::insert(BinaryNode<T> * item)
{
  this->insertOrder(item);
}

// REQUIRES:
// MODIFIES:
// EFFECTS:
template <class T>
bool BinarySearchTree<T>::remove(const T item)
{
  return true; //STUB
}

template <class T>
BinaryNode<T> * BinarySearchTree<T>::getSuccessor(BinaryNode<T> * node) const
{
  if(!node) return nullptr;

  BinaryNode<T> * output = node->getRight();
  while (output->getLeft()) {
    output = output->getLeft();
  }
  return output;

}


template <class T>
BinaryNode<T> * BinarySearchTree<T>::getPredecessor(BinaryNode<T> * node) const
{
  if(!node) return nullptr;

  BinaryNode<T> * output = node->getLeft();
  while (output->getRight()) {
    output = output->getRight();
  }
  return output;
}

#endif
