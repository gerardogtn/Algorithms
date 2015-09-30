#ifndef RedBlackNode_h
#define RedBlackNode_h value

#include "BNode.h"

template <class T>
class RedBlackNode : public BNode<T>
{
private:
  bool red = false;

  RedBlackNode<T> * parent = nullptr;
  RedBlackNode<T> * left = nullptr;
  RedBlackNode<T> * right = nullptr;

  T info;

public:
  RedBlackNode();
  RedBlackNode(const T & data);
  RedBlackNode(const RedBlackNode<T> & other);
  virtual ~RedBlackNode();

  bool isBlack() {return !this->red;};
  bool isRed() {return this->red;};
  void makeBlack();
  void makeRed();

  void setColor(const bool color);
  void getColor()const;
  void colorSwitch();

  virtual T getInfo() const { return info; }
  virtual void setInfo(const T & value) { info = value; }

  virtual   RedBlackNode<T> * getLeft() const { return left; }
  virtual void setLeft(RedBlackNode<T> * value) { left = value; }

  virtual RedBlackNode<T> * getRight() const { return right; }
  virtual void setRight(RedBlackNode<T> * value) { right = value; }

  virtual RedBlackNode<T> * getParent() const { return parent; }
  virtual void setParent(RedBlackNode<T> * value) { parent = value; }

  template <typename Tn>
  friend std::ostream & operator << (std::ostream & os, const RedBlackNode<Tn>  & node);
};

template <class T>
RedBlackNode<T>::RedBlackNode()
{

}

template <class T>
RedBlackNode<T>::RedBlackNode(const T & data)
{
  this->info = data;
}

template <class T>
RedBlackNode<T>::RedBlackNode(const RedBlackNode<T> & other)
{
  this->info = other.getInfo();
  this->left = other.getLeft();
  this->right = other.getRight();
  this->parent = other.getParent();
}

template <class T>
RedBlackNode<T>::~RedBlackNode()
{
  this->left = nullptr;
  this->right = nullptr;
  this->parent = nullptr;
  info.~T();
}

template <class T>
void RedBlackNode<T>::makeBlack()
 {
  this->red = false;
}

template <class T>
void RedBlackNode<T>::makeRed()
 {
  this->red = true;
}

template <class T>
void RedBlackNode<T>::setColor(const bool color)
{
  this->red = color;
}

template <class T>
void RedBlackNode<T>::getColor() const
{
  return this->red;
}

// REQUIRES: None.
// MODIFIES: this.
// EFFECTS: Negates this->isRed for this and its two children.
// Performs a colorSwitch
template <class T>
void RedBlackNode<T>::colorSwitch()
{
  this->isRed = !this->isRed;
  this->getLeft()->isRed = !this->getLeft()->isRed;
  this->getRight()->isRed = !this->getRight()->isRed;
}

template <class T>
std::ostream & operator << (std::ostream & os, const RedBlackNode<T>  & node)
{
  os << node.info << "(" << (node.red ? "R)" : "B)");

  return os;
}

#endif
