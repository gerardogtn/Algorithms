
#ifndef AvlTree_h
#define AvlTree_h

#include "../BinarySearchTree.h"

template <class T>
class AvlTree : public BinarySearchTree<T>{

public:
    AvlTree(){}
    ~AvlTree();

    void leftRotation(BNode<T> * node);
    void rigthRotation(BNode<T> * node);
    void leftRightRotation(BNode<T> * node);
    void rightLeftRotation(BNode<T> * node);
    bool isAVL(BNode<T> * node);
    void insert(BNode<T> * parent, BNode<T> * node);
    void insert(T value);
    void remove(T value);
    void balance(BNode<T> * node);

    BNode<T> * getMaxMin(BNode<T> * node) const;
    BNode<T> * getMaxMin() const;

};

template <class T>
AvlTree<T>::~AvlTree(){}

template <class T>
bool AvlTree<T>::isAVL(BNode<T> * node){

        if (node)
        {
            if (abs(this->getBalanceFactor(node)) > 1 )
            {
                return false;
            }
            return  isAVL(node->getRight()) && isAVL(node->getLeft());
        }
        else
        {
            return true;
        }

    }

template <class T>
void AvlTree<T>::rigthRotation(BNode<T> * pivot)
{
    BNode<T> * temp = pivot->getLeft();
    if(pivot->getParent() && pivot->getInfo() <= pivot->getParent()->getInfo())
    {
        pivot->getParent()->setLeft(temp);
    }
    else if (pivot->getParent())
    {
        pivot->getParent()->setRight(temp);
    }
    else
    {
        this->setRoot(temp);
    }
    temp->setParent(pivot->getParent());
    pivot->setParent(temp);
    pivot->setLeft(temp->getRight());
    temp->setRight(pivot);
    if(pivot->getLeft())
    {
      pivot->getLeft()->setParent(pivot);
    }
}

template <class T>
void AvlTree<T>::leftRotation(BNode<T> * pivot)
{
  BNode<T> * temp = pivot->getRight();
  if(pivot->getParent() && pivot->getInfo() <= pivot->getParent()->getInfo())
  {
    pivot->getParent()->setLeft(temp);
  }
  else if (pivot->getParent())
  {
    pivot->getParent()->setRight(temp);
  }
  else
  {
    this->setRoot(temp);
  }
  temp->setParent(pivot->getParent());
  pivot->setParent(temp);
  pivot->setRight(temp->getLeft());
  temp->setLeft(pivot);
  if(pivot->getRight())
  {
    pivot->getRight()->setParent(pivot);
  }
}

template <class T>
void AvlTree<T>::leftRightRotation(BNode<T> * pivot)
{
  BNode<T> * temp = pivot->getRight();
  leftRotation(pivot);
  rigthRotation(temp->getParent());
}

template <class T>
void AvlTree<T>::rightLeftRotation(BNode<T> * pivot)
{
  BNode<T> * temp = pivot->getLeft();
  rigthRotation(pivot);
  leftRotation(temp->getParent());
}

template <class T>
void AvlTree<T>::insert(BNode<T> * parent, BNode<T> * node)
{
  if (this->empty())
  {
    this->setRoot(node);
  }
  else
  {
    if(node->getInfo() < parent->getInfo())
    {
      if (parent->getLeft() == nullptr)
      {
        parent->setLeft(node);
        node->setParent(parent);
      }
      else
      {
        insert(parent->getLeft(), node);
      }
    }
    else if(node->getInfo() > parent->getInfo())
    {
      if (parent->getRight() == nullptr)
      {
        parent->setRight(node);
        node->setParent(parent);
      }
      else
      {
        insert(parent->getRight(), node);
      }
    }
    else
    {
      return;
    }
    balance(parent);
  }
}

template <class T>
void AvlTree<T>::balance(BNode<T> * node)
{
  if(this->getBalanceFactor(node->getParent()) == -2 && this->getBalanceFactor(node->getParent()->getLeft())== -1)
  {
    rigthRotation(node->getParent());
  }
  if(this->getBalanceFactor(node->getParent()) == -2 && this->getBalanceFactor(node->getParent()->getLeft())== 1)
  {
    leftRightRotation(node);
  }
  if(this->getBalanceFactor(node->getParent()) == 2 && this->getBalanceFactor(node->getParent()->getRight())== 1)
  {
      leftRotation(node->getParent());
  }
  if( (this->getBalanceFactor(node->getParent()) == 2 && this->getBalanceFactor(node->getParent()->getRight())== -1))
  {
      rightLeftRotation(node);
  }
}

template <class T>
void AvlTree<T>::insert(T value)
{
  BNode<T> * node = new BNode<T>(value);
  insert(this->root, node);
}

template <class T>
void AvlTree<T>::remove(T value)
{
  BNode<T> * node = this->search(value);
  if(node)
  {
    BNode<T> * parent = node->getParent();
    BNode<T> * nnode = getMaxMin(node);
    if(nnode)
    {
      nnode->setRight(node->getRight());
      if(nnode->getRight())
      {
        nnode->getRight()->setParent(nnode);
      }
      nnode->getParent()->setRight(nnode->getLeft());
      nnode->setParent(node->getParent());
      if(node->getLeft() == nnode)
      {
          if(!nnode->getLeft())
          nnode->setLeft(nullptr);
      }
      else
      {
        nnode->setLeft(node->getLeft());
      }
    }
    if(!node->getParent())
    {
      BinaryTree<T>::setRoot(nnode);
    }
    else if(node->getInfo() <= node->getParent()->getInfo())
    {
      node->getParent()->setLeft(nnode);
    }
    else
    {
      node->getParent()->setRight(nnode);
    }
    delete node;
    balance(parent);
    parent =  parent->getParent();
    balance(parent);
  }
}

template <class T>
BNode<T> * AvlTree<T>::getMaxMin() const
{
    return getMaxMin(this->root);
}


template <class T>
BNode<T> * AvlTree<T>::getMaxMin(BNode<T> * node) const
{
  if (node)
  {
    BNode<T> * workingNode = node->getLeft();
    if(workingNode)
    {
      while (workingNode->getRight() != nullptr)
      {
        workingNode = workingNode->getRight();
      }
      return workingNode;
    }
    return nullptr;
  }
  else
  {
    return nullptr;
  }
}


#endif /* AvlTree_h */
