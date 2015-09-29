//
//  BinaryNode.h
//  BinaryTree
//
//  Created by Vicente Cubells Nonell on 26/03/15.
//  Copyright (c) 2015 Vicente Cubells Nonell. All rights reserved.
//

#ifndef BinaryNode_h
#define BinaryNode_h

#include <iostream>

template <class T>
class BinaryNode {

protected:
  //BinaryNode<T> * parent;
  BinaryNode<T> * left;
  BinaryNode<T> * right;

  T info;

public:

  BinaryNode();
  BinaryNode(const T & _info);
  BinaryNode(const BinaryNode<T> & );

  virtual ~BinaryNode();

  virtual T getInfo() const { return info; }
  virtual void setInfo(const T & value) { info = value; }

  virtual BinaryNode<T> * &getLeft() { return left; }
  virtual void setLeft(BinaryNode<T> * &value) { left = value; }

  virtual BinaryNode<T> * &getRight() { return right; }
  virtual void setRight(BinaryNode<T> * &value) { right = value; }

  //virtual BinaryNode<T> * getParent() const { return parent; }
  //virtual void setParent(BinaryNode<T> * value) { parent = value; }

  template <typename Tn>
  friend std::ostream & operator << (std::ostream & os, const BinaryNode<Tn>  & node);
};

template <class T>
BinaryNode<T>::BinaryNode()
{
  //parent = nullptr;
  left = nullptr;
  right = nullptr;
}

template <class T>
BinaryNode<T>::BinaryNode(const T & _info) : info(_info)
{
  //parent = nullptr;
  left = nullptr;
  right = nullptr;
}

template <class T>
BinaryNode<T>::BinaryNode(const BinaryNode<T> & other)
{
  info = other.info;
  left = other.left;
  right = other.right;
  //parent = other.parent;
}

template <class T>
BinaryNode<T>::~BinaryNode()
{
  info.~T();
  left = nullptr;
  right = nullptr;
  //parent = nullptr;
}


template <class T>
std::ostream & operator << (std::ostream & os, const BinaryNode<T>  & node)
{
  os << node.info;

  return os;
}

#endif
