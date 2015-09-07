

#ifndef BinarySearchTree_h
#define BinarySearchTree_h

#include "BinaryTree.h"

template<class T>
class BinarySearchTree : public BinaryTree<T>{

public:
  BinarySearchTree();
  virtual ~BinarySearchTree();

  virtual void insert(const T item);
  virtual void insert(BNode<T> * item);

  bool search(const T item) const;
  bool search(const T item, BNode<T> * node) const;
  BNode<T> * searchGetNode(const T item) const;
  BNode<T> * searchGetNode(const T item, BNode<T> * node) const;
  BNode<T> * searchGetNode(BNode<T> * itemToDelete, BNode<T> * node) const;

};

template <class T>
BinarySearchTree<T>::BinarySearchTree() : BinaryTree<T>()
{

}

template <class T>
BinarySearchTree<T>::~BinarySearchTree()
{
  this->clear();
}

template <class T>
void BinarySearchTree<T>::insert(const T item)
{
  this->insertOrder(item);
}

template <class T>
void BinarySearchTree<T>::insert(BNode<T> * item)
{
  this->insertOrder(item);
}


template <class T>
bool BinarySearchTree<T>::search(const T item) const
{
  return search(item, BinaryTree<T>::root);
}

template <class T>
bool BinarySearchTree<T>::search(const T item, BNode<T> * node) const
{
  BNode<T> * output = searchGetNode(item, node);
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
BNode<T> * BinarySearchTree<T>::searchGetNode(const T item) const
{
  return searchGetNode(item, BinaryTree<T>::root);
}

template <class T>
BNode<T> * BinarySearchTree<T>::searchGetNode(const T item, BNode<T> * node) const
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
BNode<T> * BinarySearchTree<T>::searchGetNode(BNode<T> * itemToDelete, BNode<T> * node) const
{
  if (node == nullptr)
  {
    return nullptr;
  }
  else
  {
    if (itemToDelete == node)
    {
      return node;
    }
    else if (itemToDelete->getInfo() < node->getInfo())
    {
      return searchGetNode(itemToDelete, node->getLeft());
    }
    else {
      return searchGetNode(itemToDelete, node->getRight());
    }
  }
}

#endif
