//
//  BinaryTree.h
//  BinaryTree
//
//  Created by Vicente Cubells Nonell on 06/04/15.
//  Copyright (c) 2015 Vicente Cubells Nonell. All rights reserved.
//

#ifndef BinaryTree_h
#define BinaryTree_h

#include "BNode.h"
#include <list>


template <class T>
class BinaryTree {

protected:
  BNode<T> * root = nullptr;

public:
  BinaryTree() {}
  virtual ~BinaryTree();

  virtual bool empty();

  virtual void clear();
  virtual void clear(BNode<T> * node);

  virtual BNode<T> * getRoot() const;
  virtual void setRoot(const T element);
  virtual void setRoot(BNode<T> * node);
  virtual bool isRoot(BNode<T> * node) const;

  bool insert(BNode<T> * parent, T value);
  bool insert(BNode<T> * parent, BNode<T> * value);

  virtual void insertOrder(T item);
  virtual void insertOrder(BNode<T> * parent, BNode<T> * item);

  virtual void preOrder() const;
  virtual void preOrder(BNode<T> * node) const;

  virtual void inOrder() const;
  virtual void inOrder(BNode<T> * node) const;

  virtual void inverseInOrder() const;
  virtual void inverseInOrder(BNode<T> * node) const;

  void toInOrderArray(T * array, int arraySize);
  void toInOrderArray(BNode<T> * node, T * array, int arraySize, int & i);

  virtual void postOrder() const;
  virtual void postOrder(BNode<T> * node) const;

  void isLeaf() const;
  void isLeaf(BNode<T> * node) const;

  void ancestors(BNode<T> * node) const;

  int getHeight(BNode<T> * node) const ;
  int getDepth(BNode<T> * node) const;
  int getLevel(BNode<T> * node) const;
  int getBalanceFactor(BNode<T> * node) const ;

  bool isAvl(BNode<T> * node) const;

};

template <class T>
BinaryTree<T>::~BinaryTree()
{
  clear();
}

template <class T>
bool BinaryTree<T>::empty()
{
  return root == nullptr;
}

template <class T>
void BinaryTree<T>::clear()
{
  clear(root);
}

template <class T>
void BinaryTree<T>::clear(BNode<T> * node)
{
  if (node) {
    clear(node->getLeft());
    clear(node->getRight());

    delete node;
  }
}

template <class T>
BNode<T> * BinaryTree<T>::getRoot() const
{
  return root;
}

template <class T>
void setRoot(const T element)
{
  BNode<T> * node = new BNode<T>(element);
  setRoot(node);
}

template <class T>
void BinaryTree<T>::setRoot(BNode<T> * node)
{
  if (!empty()) {
    node->setLeft(root);
    root->setParent(node);
    root = node;
  }
  else {
    root = node;
  }
}

template <class T>
void BinaryTree<T>::insertOrder(T item)
{
  BNode<T> * node = new BNode<T>(item);
  insertOrder(this->root, node);
}

template <class T>
void BinaryTree<T>::insertOrder(BNode<T> * parent, BNode<T> * item)
{
  if (empty())
  {
    setRoot(item);
  }
  else
  {
    if(item->getInfo() < parent->getInfo())
    {

      if (parent->getLeft() == nullptr)
      {
        parent->setLeft(item);
        item->setParent(parent);
      }
      else
      {
        insertOrder(parent->getLeft(), item);
      }
    }
    else
    {
      if (parent->getRight() == nullptr)
      {
        parent->setRight(item);
        item->setParent(parent);
      }
      else
      {
        insertOrder(parent->getRight(), item);
      }
    }
  }

}

template <class T>
bool BinaryTree<T>::insert(BNode<T> * parent, T value)
{
  BNode<T> * node = new BNode<T>(value);
  bool inserted = insert(parent, node);

  if (!inserted) delete node;

  return inserted;
}

template <class T>
bool BinaryTree<T>::insert(BNode<T> * parent, BNode<T> * value)
{
  bool inserted = false;

  if (empty() || !parent) {
    setRoot(value);
    inserted = true;
  }
  else {
    if (!parent->getLeft()) {
      parent->setLeft(value);
      value->setParent(parent);
      inserted = true;
    }
    else if (!parent->getRight()) {
      parent->setRight(value);
      value->setParent(parent);
      inserted = true;
    }
  }

  return inserted;
}

template <class T>
void BinaryTree<T>::preOrder() const
{
  preOrder(root);
}

template <class T>
void BinaryTree<T>::preOrder(BNode<T> * node) const
{
  if (node) {
    /* Procesar el nodo */
    std::cout << *node << std::endl;

    /* Invocar a los hijos */
    preOrder(node->getLeft());
    preOrder(node->getRight());

  }
}

template <class T>
void BinaryTree<T>::inOrder() const
{
  inOrder(root);
}

template <class T>
void BinaryTree<T>::inOrder(BNode<T> * node) const
{
  if (node) {

    /* Invocar al hijo izquierdo */
    inOrder(node->getLeft());

    /* Procesar el nodo */
    std::cout << *node << std::endl;

    /* Invocar al hijo derecho */
    inOrder(node->getRight());
  }
}

template <class T>
void BinaryTree<T>::inverseInOrder(BNode<T> * node) const
{
  if (node)
  {
    inverseInOrder(node->getRight());
    std::cout << *node << std::endl;
    inverseInOrder(node->getLeft());
  }
}

// REQUIRES: arraySize is size of array.
// MODIFIES: array.
// EFFECTS: Returns the array representation of the tree in inorder.
template <class T>
void BinaryTree<T>::toInOrderArray(T * array, int arraySize)
{
  int i = 0;
  toInOrderArray(root, array, arraySize, i);
}

// REQUIRES: arraySize is the size of the array.
// MODIFIES: array.
// EFFECTS: Adds the tree's elements to array in inorder.
template <class T>
void BinaryTree<T>::toInOrderArray(BNode<T> * node, T * array,int arraySize, int & i)
{
  if (node)
  {
    toInOrderArray(node->getLeft(), array, arraySize, i);
    array[i] = node->getInfo();
    i++;
    toInOrderArray(node->getRight(), array, arraySize, i);
  }
}

template <class T>
void BinaryTree<T>::postOrder() const
{
  postOrder(root);
}

template <class T>
void BinaryTree<T>::postOrder(BNode<T> * node) const
{
  if (node) {
    /* Invocar a los hijos */
    postOrder(node->getLeft());
    postOrder(node->getRight());

    /* Procesar el nodo */
    std::cout << *node << std::endl;
  }
}

template <class T>
void BinaryTree<T>::isLeaf() const
{
  isLeaf(root);
}

template <class T>
void BinaryTree<T>::isLeaf(BNode<T> * node) const
{
  if (node) {
    if (!node->getLeft() && !node->getRight()) {
      std::cout << *node << std::endl;
    }
    else {
      isLeaf(node->getLeft());
      isLeaf(node->getRight());
    }
  }
}

template <class T>
void BinaryTree<T>::ancestors(BNode<T> * node) const
{
  if (node) {
    std::cout << *node << " -> ";
    ancestors(node->getParent());
  }
}


<<<<<<< HEAD
template <class T>
int BinaryTree<T>::getHeight(BNode<T> * node) const
{
  if (node == nullptr)
  {
    return 0;
  }
  else
  {
    int leftCount = getHeight(node->getLeft());
    int rightCount = getHeight(node->getRight());

    if (leftCount <= rightCount)
    {
      return rightCount +1;
    }
    else
    {
      return leftCount +1;
    }
  }
}

template <class T>
int BinaryTree<T>::getDepth(BNode<T> * node) const
{
  if (node == nullptr)
  {
    return 0;
  }
  else
  {
    return getDepth(node->getParent()) + 1;
  }
}

template <class T>
int BinaryTree<T>::getLevel(BNode<T> * node) const
{
  return getDepth(node) +1;
}

template <class T>
int BinaryTree<T>::getBalanceFactor(BNode<T> * node) const
{
  return (getHeight(node->getRight())-getHeight(node->getLeft()));
}

template <class T>
bool BinaryTree<T>::isAvl(BNode<T> * node) const
{
  int factor = getBalanceFactor(node);
  if (factor > 1 || factor < -1)
  {
    return false;
  }
  else
  {
    return true;
  }
}

=======
>>>>>>> 78b9919714a78936eb76b1829b11e30b1cc6152e

#endif
