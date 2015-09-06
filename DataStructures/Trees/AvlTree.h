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
  BNode<T> * other = BinaryTree<T>::copy(node->getParent());
  if (BinaryTree<T>::isRoot(node->getParent()))
  {
    node->setParent(other->getParent());
    other->setParent(node);
    node->setRight(other);
    BinaryTree<T>::setRoot(node);
    std::cout << "Mensaje de Debug" << std::endl;
  }
  else
  {
    node->setParent(other->getParent());
    other->setParent(node);
    node->setRight(other);
  }

  return other;
}

template <class T>
BNode<T>* AvlTree<T>::rotateleft(BNode<T> * node)
{
  BNode<T> * other = BinaryTree<T>::copy(node->getParent());
  if (BinaryTree<T>::isRoot(node->getParent()))
  {
    node->setParent(other->getParent());
    other->setParent(node);
    node->setLeft(other);
    BinaryTree<T>::setRoot(node);
    std::cout << "Mensaje de Debug" << std::endl;
  }
  else
  {
    node->setParent(other->getParent());
    other->setParent(node);
    node->setLeft(other);
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
