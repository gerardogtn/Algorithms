#ifndef Avltree_h
#define Avltree_h


#include "BinarySearchTree.h"
#include <iomanip>
#include <iostream>
#include <list>

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

  virtual bool removeNode(const T item);
  virtual bool removeNode(BNode<T> * item);
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
BNode<T> * AvlTree<T>::rotateright(BNode<T> * node)
{
  BNode<T> * pivot = node->getParent();
  BNode<T> * tempRight = node->getRight();
  BNode<T> * tempLeft = node->getLeft();

  if(tempLeft != nullptr && tempRight == nullptr)
  {
    BNode<T> * tempA = node->getRight();

    node->setParent(pivot->getParent());
    node->setRight(pivot);
    pivot->setParent(node);
    pivot->setLeft(tempA);

    if(tempA != nullptr)
    {
      tempA->setParent(pivot);
    }
    if(BinaryTree<T>::isRoot(pivot))
    {
      BinaryTree<T>::forceSetRoot(node);
    }
    else
    {
      node->getParent()->setLeft(node);
    }
  }
  else if (tempRight != nullptr)
  {
    BNode<T> * tempA = tempRight->getLeft();
    BNode<T> * tempB = tempRight->getRight();

    tempRight->setParent(pivot->getParent());
    node->setParent(tempRight);
    pivot->setParent(tempRight);
    tempRight->setRight(pivot);
    tempRight->setLeft(node);
    node->setRight(tempA);
    pivot->setLeft(tempB);

    if (tempA != nullptr)
    {
      tempA->setParent(node);
    }
    if(tempB != nullptr)
    {
      tempB->setParent(pivot);
    }
    if(BinaryTree<T>::isRoot(pivot))
    {
      BinaryTree<T>::forceSetRoot(tempRight);
    }
    else
    {
      if(tempRight->getParent()->getInfo() <= tempRight->getInfo())
      {
        tempRight->getParent()->setRight(tempRight);
      }
      else
      {
        tempRight->getParent()->setLeft(tempRight);
      }
    }
  }
  return node;
}

template <class T>
BNode<T>* AvlTree<T>::rotateleft(BNode<T> * node)
{
  BNode<T> * pivot = node->getParent();
  BNode<T> * tempRight = node->getRight();
  BNode<T> * tempLeft = node->getLeft();

  if(tempRight != nullptr && tempLeft == nullptr)
  {
    BNode<T> * tempA = node->getLeft();

    node->setParent(pivot->getParent());
    node->setLeft(pivot);
    pivot->setParent(node);
    pivot->setRight(tempA);
    if(tempA != nullptr)
    {
      tempA->setParent(pivot);
    }
    if(BinaryTree<T>::isRoot(pivot))
    {
      BinaryTree<T>::forceSetRoot(node);
    }
    else
    {
      if(node->getParent()->getInfo() > node->getInfo())
      {
        node->getParent()->setLeft(node);
      }
      else
      {
        node->getParent()->setRight(node);
      }
    }
  }
  else if(tempLeft != nullptr)
  {
    BNode<T> * tempA = tempLeft->getLeft();
    BNode<T> * tempB = tempLeft->getRight();

    tempLeft->setParent(pivot->getParent());
    tempLeft->setLeft(pivot);
    tempLeft->setRight(node);
    pivot->setParent(tempLeft);
    node->setParent(tempLeft);
    node->setLeft(tempB);
    pivot->setRight(tempA);

    if(tempA != nullptr)
    {
      tempA->setParent(pivot);
    }
    if(tempB != nullptr)
    {
      tempB->setParent(node);
    }
    if(BinaryTree<T>::isRoot(pivot))
    {
      BinaryTree<T>::forceSetRoot(tempLeft);
    }
    else
    {
      if(tempLeft->getParent()->getInfo() <= tempLeft->getInfo())
      {
        tempLeft->getParent()->setRight(tempLeft);
      }
      else
      {
        tempLeft->getParent()->setLeft(tempLeft);
      }
    }
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

template <class T>
bool AvlTree<T>::removeNode(const T item)
{
  BNode<T> * nodeToDelete = BinarySearchTree<T>::searchGetNode(item);
  if (nodeToDelete)
  {
    this->removeNode(nodeToDelete);
    return true;
  }
  else
  {
    return false;
  }
}

template <class T>
bool AvlTree<T>::removeNode(BNode<T> * item)
{
  if(item->isLeaf())
  {
    BNode<T> * parentOfRemoved = item->getParent();
    item->setParent(nullptr);
    if(parentOfRemoved->getInfo() <= item->getInfo())
    {
      parentOfRemoved->setRight(nullptr);
    }
    else
    {
      parentOfRemoved->setLeft(nullptr);
    }
    if(BinaryTree<T>::isRoot(parentOfRemoved))
    {
      if(BinaryTree<T>::getBalanceFactor(parentOfRemoved)==2)
      {
        balance(parentOfRemoved->getRight());
        return true;
      }
      else
      {
        balance(parentOfRemoved->getLeft());
        return true;
      }
    }
    else
    {
      if(BinaryTree<T>::getBalanceFactor(parentOfRemoved)==2)
      {
        balance(parentOfRemoved->getRight());
        return true;
      }
      else if(BinaryTree<T>::getBalanceFactor(parentOfRemoved)==-2)
      {
        balance(parentOfRemoved->getParent()->getLeft());
        return true;
      }
      else if(BinaryTree<T>::getBalanceFactor(parentOfRemoved->getParent())==2)
      {
        balance(parentOfRemoved->getParent()->getRight());
        if(!this->isAvl())
        {
          BNode<T> * nuevoABalancear = parentOfRemoved->getParent()->getParent()->getRight();
          if(nuevoABalancear->getRight() != nullptr)
          {
            balance(nuevoABalancear->getRight());
          }
          else if (nuevoABalancear->getLeft() != nullptr)
          {
            balance(nuevoABalancear->getLeft());
          }
        }
        return true;
      }
      else if(BinaryTree<T>::getBalanceFactor(parentOfRemoved->getParent())==-2)
      {
        balance(parentOfRemoved->getParent()->getLeft());
        if(!this->isAvl())
        {
          balance(parentOfRemoved->getParent()->getParent()->getLeft());
        }
        return true;
      }

    }
  }
  else
  {
    BNode<T> * maxMin = BinaryTree<T>::getMaxMin(item);
    item->setInfo(maxMin->getInfo());
    if(maxMin->isLeaf())
    {

      maxMin->getParent()->setRight(nullptr);
      maxMin->setParent(nullptr);
    }
    else
    {
      item->getLeft()->setRight(maxMin->getLeft());
      maxMin->getLeft()->setParent(item->getLeft());
      maxMin->setParent(nullptr);
      maxMin->setLeft(nullptr);
    }

  }
  return false;
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
