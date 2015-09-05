
//

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
  if (node == nullptr)
  {
    return false;
  }
  else {
    T nodeValue = node->getInfo();
    if (item == nodeValue)
    {
      return true;
    }
    else if (item < nodeValue)
    {
      return search(item, node->getLeft());
    }
    else {
      return search(item, node->getRight());
    }
  }
}

#endif
