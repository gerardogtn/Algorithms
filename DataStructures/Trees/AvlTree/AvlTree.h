#ifndef Avltree_h
#define Avltree_h


#include "BinarySearchTree.h"
#include <iomanip>
#include <iostream>
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

  virtual bool remove(const T item);
  virtual bool remove(BNode<T> * item);
  void prettyPrint(BNode<T> * node, int indent);

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
  BNode<T> * pivot = node->getParent();
  BNode<T> * temp = node->getRight();
  bool isRoot = BinaryTree<T>::isRoot(pivot);

  node->setParent(pivot->getParent());
  node->setRight(pivot);
  pivot->setLeft(temp);
  pivot->setParent(node);

  if (isRoot)
  {
    BinaryTree<T>::forceSetRoot(node);
  }
  else
  {
    node->getParent()->setRight(node);
  }
  if(temp)
  {
    temp->setParent(pivot);
  }

  return node;

}

template <class T>
BNode<T>* AvlTree<T>::rotateleft(BNode<T> * node)
{

  BNode<T> * pivot = node->getParent();
  BNode<T> * temp = node->getLeft();
  bool isRoot = BinaryTree<T>::isRoot(pivot);

  node->setParent(pivot->getParent());
  node->setLeft(pivot);
  pivot->setRight(temp);
  pivot->setParent(node);

  if (isRoot)
  {
    BinaryTree<T>::forceSetRoot(node);
  }
  else
  {
    node->getParent()->setLeft(node);
  }
  if(temp)
  {
    temp->setParent(pivot);
  }

  return node;
}

template <class T>
void AvlTree<T>::balance(BNode<T> * node)
{
  if (!node) return;
  if(BinaryTree<T>::getBalanceFactor(node->getParent()) == 2)
  {
    rotateleft(node);
  }
  if( BinaryTree<T>::getBalanceFactor(node->getParent()) == -2)
  {
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

// REQUIRES: None.
// MODIFIES: this.
// EFFECTS:  Returns true if the element was found and was deleted.
template <class T>
bool AvlTree<T>::remove(const T item)
{
  return remove(BinarySearchTree<T>::searchGetNode(item));
}

// REQUIRES: item is in Avl Tree
// MODIFIES: this.
// EFFECTS: Returns true if item was deleted.
// INVARIANT: Avl is balanced.
template <class T>
bool AvlTree<T>::remove(BNode<T> * item)
{
  if (item == nullptr)
  {
    return false;
  }
  else
  {
    BNode<T> * parent = item->getParent();
    BNode<T> * leftChild = item->getLeft();
    BNode<T> * rightChild = item->getRight();
    BNode<T> * next = BinaryTree<T>::getMaxMin(item);
    bool insertLeft = parent->getInfo() < item->getInfo();
    if (insertLeft)
    {
      next->getParent()->setRight(next->getLeft());
      next->setLeft(leftChild);
      leftChild->setParent(next);
      next->setParent(parent);
      parent->setLeft(next);
      next->setRight(rightChild);
      rightChild->setParent(next);
    }
    else
    {
      next->getParent()->setRight(next->getLeft());
      next->setLeft(leftChild);
      leftChild->setParent(next);
      next->setParent(parent);
      parent->setRight(next);
      next->setRight(rightChild);
      rightChild->setParent(next);
    }
    delete item;

    balance(next);
  }
  return true;

}

template <class T>
void AvlTree<T>::prettyPrint(BNode<T> * p, int indent)
{
  if(p != nullptr)
  {
    if(p->getRight()) {
      prettyPrint(p->getRight(), indent+4);
    }
    if (indent) {
      std::cout << std::setw(indent) << ' ';
    }
    if (p->getRight()) std::cout<<" /\n" << std::setw(indent) << ' ';
    std::cout<< p->getInfo() << "\n ";
    if(p->getLeft()) {
      std::cout << std::setw(indent) << ' ' <<" \\\n";
      prettyPrint(p->getLeft(), indent+4);
    }
  }
}

#endif