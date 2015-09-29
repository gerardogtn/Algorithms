//
//  BinaryTree.h
//  BinaryTree
//
//  Created by Vicente Cubells Nonell on 06/04/15.
//  Copyright (c) 2015 Vicente Cubells Nonell. All rights reserved.
//

#ifndef BinaryTree_h
#define BinaryTree_h

#include "BinaryNode.h"
#include <list>


template <class T>
class BinaryTree {

protected:
  BinaryNode<T> * root;

  virtual void clear(BinaryNode<T> * node);

  void preOrder(BinaryNode<T> * node) const;
  void inOrder(BinaryNode<T> * node) const;
  void postOrder(BinaryNode<T> * node) const;
  void inverseInOrder(BinaryNode<T> * node) const;

  int getHeight(BinaryNode<T> * node) const;
  int getDepth(BinaryNode<T> * node) const;
  int getLevel(BinaryNode<T> * node) const;
  int getBalanceFactor(BinaryNode<T> * node) const;

  virtual bool isAvl(BinaryNode<T> * node) const;

  // BinaryNode<T> * copy (const BinaryNode<T> * node) const;

public:
  BinaryTree();
  virtual ~BinaryTree();

  virtual BinaryNode<T> * getRoot();
  virtual void setRoot(const T element);
  virtual void setRoot(BinaryNode<T> * node);
  virtual void forceSetRoot(BinaryNode<T> * node);
  virtual bool isRoot(BinaryNode<T> * node);

  bool empty();
  virtual void clear();

  //bool insert(BinaryNode<T> * parent, const T value);
  //bool insert(BinaryNode<T> * parent, BinaryNode<T> * value);

  void preOrder() const;
  void inOrder() const;
  void postOrder() const;
  void inverseInOrder() const;

  int getHeight() const;
  int getDepth() const;
  int getLevel() const;
  int getBalanceFactor() const;

  virtual bool isAvl() const;
  bool isBTree()const {return false;};
  bool isTwoThreeTree()const {return false;};
  virtual bool isRedBlackTree() const {return false;};
  // TODO: implement isBST
  virtual bool isBST() const {return false;};

  // BinaryTree<T> * copy() const;

  BinaryNode<T> * getSuccessor(BinaryNode<T> * node) const;
  BinaryNode<T> * getPredecessor(BinaryNode<T> * node) const;
};

template <class T>
BinaryTree<T>::BinaryTree()
{
  root = nullptr;
}

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
void BinaryTree<T>::clear(BinaryNode<T> * node)
{
  if (node) {
    clear(node->getLeft());
    clear(node->getRight());

    delete node;
  }
}

template <class T>
BinaryNode<T> * BinaryTree<T>::getRoot()
{
  return root;
}

template <class T>
void BinaryTree<T>::setRoot(const T element)
{
  BinaryNode<T> * node = new BinaryNode<T>(element);
  setRoot(node);
}

template <class T>
void BinaryTree<T>::setRoot(BinaryNode<T> * node)
{
  if (!empty()) {
    node->setLeft(root);
    //root->setParent(node);
    root = node;
  }
  else {
    root = node;
  }
}

template <class T>
void BinaryTree<T>::forceSetRoot(BinaryNode<T> * node)
{
  root = node;
}

template <class T>
bool BinaryTree<T>::isRoot(BinaryNode<T> * node){
  return node == this->root;
}

// template <class T>
// bool BinaryTree<T>::insert(BinaryNode<T> * parent, const T value)
// {
//   BinaryNode<T> * node = new BinaryNode<T>(value);
//   bool inserted = insert(parent, node);
//
//   if (!inserted) delete node;
//
//   return inserted;
// }

// template <class T>
// bool BinaryTree<T>::insert(BinaryNode<T> * parent, BinaryNode<T> * value)
// {
//   bool inserted = false;
//
//   if (empty() || !parent) {
//     setRoot(value);
//     inserted = true;
//   }
//   else {
//     if (!parent->getLeft()) {
//       parent->setLeft(value);
//       value->setParent(parent);
//       inserted = true;
//     }
//     else if (!parent->getRight()) {
//       parent->setRight(value);
//       value->setParent(parent);
//       inserted = true;
//     }
//   }
//
//   return inserted;
// }

template <class T>
void BinaryTree<T>::preOrder() const
{
  preOrder(root);
}

template <class T>
void BinaryTree<T>::preOrder(BinaryNode<T> * node) const
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
void BinaryTree<T>::inOrder(BinaryNode<T> * node) const
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
void BinaryTree<T>::inverseInOrder() const
{
  inverseInOrder(root);
}

template <class T>
void BinaryTree<T>::inverseInOrder(BinaryNode<T> * node) const
{
  if (node)
  {
    inverseInOrder(node->getRight());
    std::cout << *node << std::endl;
    inverseInOrder(node->getLeft());
  }
}

template <class T>
void BinaryTree<T>::postOrder() const
{
  postOrder(root);
}

template <class T>
void BinaryTree<T>::postOrder(BinaryNode<T> * node) const
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
int BinaryTree<T>::getHeight() const
{
  return getHeight(root);
}

template <class T>
int BinaryTree<T>::getHeight(BinaryNode<T> * node) const
{
  if (node == nullptr)
  {
    return -1;
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
int BinaryTree<T>::getLevel() const
{
  return getLevel(root);
}

template <class T>
int BinaryTree<T>::getLevel(BinaryNode<T> * node) const
{
  if (node == nullptr)
  {
    return 0;
  }
  else
  {
    return getLevel(node->getParent()) + 1;
  }
}

template <class T>
int BinaryTree<T>::getDepth() const
{
  return getDepth(root);
}

template <class T>
int BinaryTree<T>::getDepth(BinaryNode<T> * node) const
{
  return getLevel(node) - 1;
}

template <class T>
int BinaryTree<T>::getBalanceFactor() const
{
  return getBalanceFactor(root);
}

template <class T>
int BinaryTree<T>::getBalanceFactor(BinaryNode<T> * node) const
{
  if (node)
  {
    return getHeight(node->getRight()) - getHeight(node->getLeft());
  }
  return 0;
}

template <class T>
bool BinaryTree<T>::isAvl() const
{
  return isAvl(root);
}

template <class T>
bool BinaryTree<T>::isAvl(BinaryNode<T> * node) const
{
  if (node)
  {
    if (abs(getBalanceFactor(node)) > 1 )
    {
      return false;
    }
    return  isAvl(node->getRight()) && isAvl(node->getLeft());
  }
  else
  {
    return true;
  }
}

// // REQUIRES: None.
// // MODIFIES: None
// //  EFFECTS: Copies a binary tree.
// template <class T>
// BinaryTree<T> * BinaryTree<T>::copy() const{
//   BinaryTree<T> * output = new BinaryTree<T>();
//   BinaryNode<T> * node = new BinaryNode<T>();
//   node = copy(this->getRoot());
//   output->insert(nullptr, node);
//   return output;
// }
//
// // REQUIRES: None.
// // MODIFIES: None
// //  EFFECTS: Copies the root node of a tree to output.
// // Copies the root of a tree.
// template <class T>
// BinaryNode<T> * BinaryTree<T>::copy(const BinaryNode<T> * node) const{
//   if (node){
//     BinaryNode<T> * output = new BinaryNode<T>();
//     output->setInfo(node->getInfo());
//     output->setRight(copy(node->getRight()));
//     output->setLeft(copy(node->getLeft()));
//     return output;
//   }
//   return nullptr;
// }


template <class T>
BinaryNode<T> * BinaryTree<T>::getSuccessor(BinaryNode<T> * node) const
{
  if(!node) return nullptr;

  BinaryNode<T> * output = node->getRight();
  while (output->getLeft()) {
    output = output->getLeft();
  }
  return output;

}


template <class T>
BinaryNode<T> * BinaryTree<T>::getPredecessor(BinaryNode<T> * node) const
{
  if(!node) return nullptr;

  BinaryNode<T> * output = node->getLeft();
  while (output->getRight()) {
    output = output->getRight();
  }
  return output;
}
#endif
