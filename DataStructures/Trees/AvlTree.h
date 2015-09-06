#ifndef Avltree_h
#define Avltree_h

#include "BinarySearchTree.h"

template <class T>
class AvlTree : public BinarySearchTree<T>{

public:
  AvlTree();
  virtual ~AvlTree();

  BNode<T> * rotateright(BNode<T> * node);
  BNode<T> * rotateleft(BNode<T> * node);
  void balance(BNode<T> * p);

  virtual void insert(const T item);
  virtual void insert(BNode<T> * item);

};

template <class T>
AvlTree<T>::AvlTree() : BinarySearchTree<T>()
{ }

template <class T>
AvlTree<T>::~AvlTree()
{
  this->clear();
}

template <class T>
BNode<T>* AvlTree<T>::rotateright(BNode<T> * node)
{
  BNode<T> * other = node->getParent();
  if (BinaryTree<T>::isRoot(other))
  {
    node->setParent(other->getParent());
    other->setParent(node);
    other->setLeft(node->getRight());
    node->setRight(other);
    BinaryTree<T>::setRoot(node);
  }
  else
  {
    node->setParent(other->getParent());
    other->getParent()->setLeft(node);
    other->setParent(node);
    node->setRight(other);
    other->setLeft(nullptr);
  }

  return other;
}

template <class T>
BNode<T>* AvlTree<T>::rotateleft(BNode<T> * node)
{
  BNode<T> * other = node->getParent();
  if (BinaryTree<T>::isRoot(other))
  {
    node->setParent(other->getParent());
    other->setParent(node);
    other->setRight(node->getLeft());
    node->setLeft(other);
    BinaryTree<T>::setRoot(node);
  }
  else
  {
    node->setParent(other->getParent());
    other->getParent()->setRight(node);
    other->setParent(node);
    node->setLeft(other);
    other->setRight(nullptr);

  }

  return other;
}

// REQUIRES: None.
// MODIFIES: this.
// EFFECTS: If balanceFactor == 2 then rotates left, and
// calls again to verify balance. Else if balanceFactor
// == -2 then rotates right and calls again to verify balance.
// Else nothing.
// SHORT: Balances tree from bottom up.
template <class T>
void AvlTree<T>::balance(BNode<T> * node)
{
  if (!node) return;
  if(BinaryTree<T>::getBalanceFactor(node->getParent()) == 2)
  {
    // if(BinaryTree<T>::getBalanceFactor(node->getRight()) < 0)
    // {
    //   node->setRight(rotateright(node->getRight()));
    // }
    rotateleft(node);
  }
  if( BinaryTree<T>::getBalanceFactor(node->getParent()) == -2)
  {
    // if( BinaryTree<T>::getBalanceFactor(node->getLeft()) > 0)
    // {
    //   node->setLeft(rotateleft(node->getLeft()));
    // }
    rotateright(node);
  }
  if(!this->isAvl())
  {
    balance(node->getParent());
  }
}

template <class T>
void AvlTree<T>::insert(const T item)
{
  BNode<T> * node = new BNode<T>(item);
  insert(node);
}

template <class T>
void AvlTree<T>::insert(BNode<T> * item)
{
  BinarySearchTree<T>::insert(item);
  this->balance(item->getParent());
}


#endif
