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
  BNode<T> * balance(BNode<T> * p);

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
    BNode<T> * other = node->getLeft();
    node->setLeft(other->getRight());
    other->setRight(node);
    return other;
}

template <class T>
BNode<T>* AvlTree<T>::rotateleft(BNode<T> * node)
{
    BNode<T> * other = node->getRight();
    node->setRight(other->getLeft());
    other->setLeft(node);
    return other;
}

template <class T>
BNode<T> * AvlTree<T>::balance(BNode<T> * node) // balancing the p node
{
  if( BinaryTree<T>::getBalanceFactor(node)==2 )
  {
      if( BinaryTree<T>::getBalanceFactor(node->getRight()) < 0 )
          node->setRight(rotateright(node->getRight()));
       return rotateleft(node);
  }
  if( BinaryTree<T>::getBalanceFactor(node)==-2 )
  {
      if( BinaryTree<T>::getBalanceFactor(node->getLeft()) > 0  )
          node->setLeft(rotateleft(node->getLeft()));
       return rotateright(node);
  }
  return node;
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
  this->balance(BinaryTree<T>::root);
}


#endif
