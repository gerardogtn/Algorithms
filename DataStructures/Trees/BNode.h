//
//  BNode.h
//  BinaryTree
//
//  Created by Vicente Cubells Nonell on 26/03/15.
//  Copyright (c) 2015 Vicente Cubells Nonell. All rights reserved.
//

//No hay un clear declarado



#ifndef BNode_h
#define BNode_h

#include <iostream>

template <class T>
class BNode {

protected:
  BNode<T> * parent = nullptr;
  BNode<T> * left = nullptr;
  BNode<T> * right = nullptr;

  T info;

public:

  BNode() { }
  BNode(const T & _info) : info (_info) { }
  BNode(const BNode<T> & );

  virtual ~BNode();

  virtual T getInfo() const { return info; }
  virtual void setInfo(const T & value) { info = value; }

  virtual BNode<T> * getLeft() const { return left; }
  virtual void setLeft(BNode<T> * value) { left = value; }

  virtual BNode<T> * getRight() const { return right; }
  virtual void setRight(BNode<T> * value) { right = value; }

  virtual BNode<T> * getParent() const { return parent; }
  virtual void setParent(BNode<T> * value) { parent = value; }

  bool isLeaf();
  bool hasOneChild();
  bool hasTwoChildren();

  template <typename Tn>
  friend std::ostream & operator << (std::ostream & os, const BNode<Tn>  & node);
};

template <class T>
BNode<T>::BNode(const BNode<T> & other)
{
  info = other.info;
  left = other.left;
  right = other.right;
  parent = other.parent;
}

template <class T>
BNode<T>::~BNode()
{
  info.~T();
  left = right = parent = nullptr;
}

template <class T>
bool BNode<T>::isLeaf()
{
  return (this->getRight() == nullptr && this->getLeft() == nullptr);
}

template <class T>
bool BNode<T>::hasOneChild()
{
  return (this->getRight() != nullptr || this->getLeft() != nullptr) && !this->hasTwoChildren();
}

template <class T>
bool BNode<T>::hasTwoChildren()
{
  return this->getRight() != nullptr && this->getLeft() != nullptr;
}

template <class T>
std::ostream & operator << (std::ostream & os, const BNode<T>  & node)
{
  os << node.info;

  return os;
}

#endif
