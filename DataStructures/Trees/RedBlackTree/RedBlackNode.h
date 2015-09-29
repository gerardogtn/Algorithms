#ifndef RedBlackNode_h
#define  RedBlackNode_h

#include "../BinaryTree/BinaryNode.h"

template <class Record>
class RedBlackNode : BinaryNode<Record>{

private:
  bool _isRed;

public:
  RedBlackNode();
  RedBlackNode(const Record & target);
  ~RedBlackNode() {};

  virtual void makeRed() { _isRed = true;};
  virtual void makeBlack() { _isRed = false;};

  virtual bool isRed(){return _isRed;};
  virtual bool isBlack(){return !_isRed;};
};

template <class Record>
RedBlackNode<Record>::RedBlackNode()
{
  _isRed = false;
  this->left = nullptr;
  this->right = nullptr;
}

template <class Record>
RedBlackNode<Record>::RedBlackNode(const Record & target)
{
  _isRed = false;
  this->left = nullptr;
  this->right = nullptr;
  this->data = target;
}


#endif
