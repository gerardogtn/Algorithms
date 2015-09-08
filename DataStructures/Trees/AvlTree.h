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

  // virtual bool removeNode(const T item);
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

  if (tempRight != nullptr)
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
      tempRight->getParent()->setLeft(tempRight);
    }
  }
  else if(tempLeft != nullptr)
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
  return node;
}

template <class T>
BNode<T>* AvlTree<T>::rotateleft(BNode<T> * node)
{
  BNode<T> * pivot = node->getParent();
  BNode<T> * tempRight = node->getRight();
  BNode<T> * tempLeft = node->getLeft();

  if(tempLeft != nullptr)
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
      if(node->getParent()->getInfo() > node->getInfo())
      {
        tempLeft->getParent()->setRight(tempLeft);
      }
      else
      {
        tempLeft->getParent()->setLeft(tempLeft);
      }
    }
  }
  else if(tempRight != nullptr)
  {
    BNode<T> * tempA = node->getLeft();

    node->setParent(pivot->getParent());
    node->setLeft(pivot);
    pivot->setParent(node);
    pivot->setRight(tempA);
    std::cout << "Hace todo esto bien" << std::endl;
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
//  this->prettyPrint(this->getRoot(),0);
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
// template <class T>
// bool AvlTree<T>::remove(const T item)
// {
//   return remove(BinarySearchTree<T>::searchGetNode(item));
// }

// REQUIRES: item is in Avl Tree
// MODIFIES: this.
// EFFECTS: Returns true if item was deleted.
// INVARIANT: Avl is balanced.
// template <class T>
// bool AvlTree<T>::removeNode(BNode<T> * item)
// {
//   if (item->isLeaf()) {
//     BNode<T> * parent = item->getParent();
//     if (item->getInfo() < parent->getInfo())
//     {
//       parent->setLeft(nullptr);
//     }
//     else
//     {
//       parent->setRight(nullptr);
//     }
//     delete item;
//     balance(parent);
//     return true;
//   }
//   else if (item->hasOneChild())
//   {
//     BNode<T> * child;
//     if (item->getRight() != nullptr)
//     {
//       child = item->getRight();
//       item->setRight(nullptr);
//     }
//     else
//     {
//       child = item->getLeft();
//       item->setLeft(nullptr);
//     }
//     item->setInfo(child->getInfo());
//     removeNode(child);
//   }
//   else
//   {
//     BNode<T> * maxMin = this->getMaxMin(item);
//     item->setInfo(maxMin->getInfo());
//     removeNode(maxMin);
//   }
//   return true;
// }

template <class T>
bool AvlTree<T>::removeNode(BNode<T> * item)
{
  if(item->isLeaf())
  {
    BNode<T> * parentOfRemoved = item->getParent();
    BNode<T> * balanceElement;
    item->setParent(nullptr);
    if(parentOfRemoved->getInfo() < item->getInfo())
    {
      parentOfRemoved->setRight(nullptr);
    }
    else
    {
      parentOfRemoved->setLeft(nullptr);
    }
    if(BinaryTree<T>::isRoot(parentOfRemoved))
    {
      int balanceFactor = BinaryTree<T>::getBalanceFactor(parentOfRemoved);
      if(balanceFactor == -2)
      {
        balance(parentOfRemoved->getLeft());
      }
      else
      {
        balance(parentOfRemoved->getRight());
      }
    }
    if(BinaryTree<T>::getBalanceFactor(parentOfRemoved->getParent())==2)
    {
      if(BinaryTree<T>::isRoot(parentOfRemoved))
      {
        bool hasRight = parentOfRemoved->getLeft()->getRight();
        if(hasRight)
        {
          balanceElement = parentOfRemoved->getLeft()->getRight();
        }
        else
        {
          balanceElement = parentOfRemoved->getLeft()->getLeft();
        }
        if(balanceElement)
        {
          balance(balanceElement);
        }
      }
      else
      {
        BNode<T> * balanceElement = parentOfRemoved->getParent()->getRight();
        balance(balanceElement);
      }
    }
    else
    {
      if(BinaryTree<T>::isRoot(parentOfRemoved))
      {
        bool hasLeft = parentOfRemoved->getLeft()->getLeft();
        if(hasLeft)
        {
          balanceElement = parentOfRemoved->getLeft()->getLeft();
        }
        else
        {
          balanceElement = parentOfRemoved->getLeft()->getRight();
        }
        if(balanceElement)
        {
          balance(balanceElement);
        }
      }
      else
      {
        BNode<T> * balanceElement = parentOfRemoved->getParent()->getLeft();
        balance(balanceElement);
      }
    }


    return true;
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
