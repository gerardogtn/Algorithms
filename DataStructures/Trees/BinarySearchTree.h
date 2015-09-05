
//

#ifndef BinarySearchTree_h
#define BinarySearchTree_h

#include "BinaryTree.h"

template<class T>
class BinarySearchTree : public BinaryTree<T>{

protected:
  BNode<T> * root = nullptr;

public:
  BinarySearchTree() {};
  virtual ~BinarySearchTree();
  bool search(const T item) const;
  bool search(const T item, BNode<T> * node) const;

};


template <class T>
bool BinarySearchTree<T>::search(const T item) const
{
  return search(item, root);
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
    if (nodeValue == item)
    {
      return true;
    }
    else if (nodeValue < item )
    {
      return search(item, node->getLeft());
    }
    else {
      return search(item, node->getRight());
    }
  }
}

#endif
