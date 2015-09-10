
#ifndef RedBlackTree_h
#define RedBlackTree_h

#include "RedBlackNode.h"
#include "BinarySearchTree.h"

// Non-branching node: Node with at most 1 child.

// Implementation of a Red Black Tree with black-colored root.
// INVARIANTS: A) NO RED NODE HAS A RED CHILD.
// B) EVERY PATH FROM SOME NODE TO ANY OF ITS NON-BRANCHING DESCENDANTS
// HAS THE SAME AMOUNT OF BLACK NODES.
template<class T>
class RedBlackTree : public BinarySearchTree<T>
{
protected:
  RedBlackNode<T> * root = nullptr;

public:
  RedBlackTree<T>();
  virtual ~RedBlackTree<T>();

  virtual bool empty();

  virtual void clear();
  virtual void clear(RedBlackNode<T> * node);

  virtual bool isRoot(RedBlackNode<T> * node);
  virtual void setRoot(const T element);
  virtual void setRoot(RedBlackNode<T> * node);
  virtual void forceSetRoot(RedBlackNode<T> * node);
  virtual RedBlackNode<T> * getRoot() const;

  virtual void insert(T info);
  virtual void insert(RedBlackNode<T> * node);
  virtual void insert(RedBlackNode<T> * parent, RedBlackNode<T> * node);

  void insertFixup(RedBlackNode<T> * node);

  void remove(RedBlackNode<T> * node);
  void removeFixup(RedBlackNode<T> * node);

  void rotateLeft(RedBlackNode<T> * node);
  void rotateRight(RedBlackNode<T> * node);

  virtual void preOrder() const;
  virtual void preOrder(RedBlackNode<T> * node) const;

  virtual void inOrder() const;
  virtual void inOrder(RedBlackNode<T> * node) const;

  virtual void inverseInOrder() const;
  virtual void inverseInOrder(RedBlackNode<T> * node) const;

  virtual void postOrder() const;
  virtual void postOrder(RedBlackNode<T> * node) const;

  virtual void isLeaf() const;
  virtual void isLeaf(RedBlackNode<T> * node) const;

  virtual int getHeight() const;
  virtual int getHeight(RedBlackNode<T> * node) const ;

  virtual int getDepth() const;
  virtual int getDepth(RedBlackNode<T> * node) const;

  virtual int getLevel() const;
  virtual int getLevel(RedBlackNode<T> * node) const;

  virtual int getBalanceFactor() const;
  virtual int getBalanceFactor(RedBlackNode<T> * node) const ;

  virtual bool isAvl() const;
  virtual bool isAvl(RedBlackNode<T> * node) const;
};

template <class T>
RedBlackTree<T>::RedBlackTree()
{

}

template <class T>
RedBlackTree<T>::~RedBlackTree()
{
  clear();
}

template <class T>
bool RedBlackTree<T>::empty()
{
  return root == nullptr;
}

template <class T>
void RedBlackTree<T>::clear()
{
  clear(root);
}

template <class T>
void RedBlackTree<T>::clear(RedBlackNode<T> * node)
{
  if (node) {
    clear(node->getLeft());
    clear(node->getRight());

    delete node;
  }
}

template <class T>
RedBlackNode<T> *  RedBlackTree<T>::getRoot() const
{
  return this->root;
}

template <class T>
bool RedBlackTree<T>::isRoot(RedBlackNode<T> * node)
{
  return node == this->root;
}

template <class T>
void RedBlackTree<T>::setRoot(const T element)
{
  RedBlackNode<T> * node = new RedBlackNode<T>(element);
  setRoot(node);
}

template <class T>
void RedBlackTree<T>::setRoot(RedBlackNode<T> * node)
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
void RedBlackTree<T>::forceSetRoot(RedBlackNode<T> * node)
{
  root = node;
}


template <class T>
void RedBlackTree<T>::preOrder() const
{
  preOrder(root);
}

template <class T>
void RedBlackTree<T>::preOrder(RedBlackNode<T> * node) const
{
  if (node)
  {
    std::cout << *node << std::endl;
    preOrder(node->getLeft());
    preOrder(node->getRight());
  }
}

template <class T>
void RedBlackTree<T>::inOrder() const
{
  inOrder(root);
}

template <class T>
void RedBlackTree<T>::inOrder(RedBlackNode<T> * node) const
{
  if (node) {
    inOrder(node->getLeft());
    std::cout << *node << std::endl;
    inOrder(node->getRight());
  }
}

template <class T>
void RedBlackTree<T>::inverseInOrder() const
{
  inverseInOrder(root);
}

template <class T>
void RedBlackTree<T>::inverseInOrder(RedBlackNode<T> * node) const
{
  if (node)
  {
    inverseInOrder(node->getRight());
    std::cout << *node << std::endl;
    inverseInOrder(node->getLeft());
  }
}

template <class T>
void RedBlackTree<T>::postOrder() const
{
  postOrder(root);
}

template <class T>
void RedBlackTree<T>::postOrder(RedBlackNode<T> * node) const
{
  if (node) {
    postOrder(node->getLeft());
    postOrder(node->getRight());
    std::cout << *node << std::endl;
  }
}

template <class T>
void RedBlackTree<T>::isLeaf() const
{
  isLeaf(root);
}

template <class T>
void RedBlackTree<T>::isLeaf(RedBlackNode<T> * node) const
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
int RedBlackTree<T>::getHeight() const
{
  return getHeight(root);
}

template <class T>
int RedBlackTree<T>::getHeight(RedBlackNode<T> * node) const
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
int RedBlackTree<T>::getLevel() const
{
  return getLevel(root);
}

template <class T>
int RedBlackTree<T>::getLevel(RedBlackNode<T> * node) const
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
int RedBlackTree<T>::getDepth() const
{
  return getDepth(root);
}

template <class T>
int RedBlackTree<T>::getDepth(RedBlackNode<T> * node) const
{
  return getLevel(node) - 1;
}

template <class T>
int RedBlackTree<T>::getBalanceFactor() const
{
  return getBalanceFactor(root);
}

template <class T>
int RedBlackTree<T>::getBalanceFactor(RedBlackNode<T> * node) const
{
  if (node)
  {
    return getHeight(node->getRight()) - getHeight(node->getLeft());
  }
  return 0;
}

template <class T>
bool RedBlackTree<T>::isAvl() const
{
  return isAvl(root);
}

template <class T>
bool RedBlackTree<T>::isAvl(RedBlackNode<T> * node) const
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

template <class T>
void RedBlackTree<T>::insert(T info)
{
  RedBlackNode<T> * node = new RedBlackNode<T>(info);
  insert(node);
}

template <class T>
void RedBlackTree<T>::insert(RedBlackNode<T> * node)
{
  insert(getRoot(), node);
}

template <class T>
void RedBlackTree<T>::insert(RedBlackNode<T> * parent, RedBlackNode<T> * item)
{
  if (empty())
  {
    setRoot(item);
  }
  else
  {
    item->makeRed();
    if(item->getInfo() < parent->getInfo())
    {

      if (parent->getLeft() == nullptr)
      {
        parent->setLeft(item);
        item->setParent(parent);
      }
      else
      {
        insert(parent->getLeft(), item);
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
        insert(parent->getRight(), item);
      }
    }
  }
  if (!isRoot(item) && item->getParent()){
    insertFixup(item);
  }
}


template <class T>
void RedBlackTree<T>::insertFixup(RedBlackNode<T> * node)
{

  while (node->getParent()->isRed())
  {
    if (node->getParent()->getParent() == node->getParent()->getParent()->getLeft())
    {
      RedBlackNode<T> * temp = node->getParent()->getParent()->getRight();
      if (temp && temp->isRed())
      {
        node->getParent()->makeBlack();
        temp->makeBlack();
        node->getParent()->getParent()->makeRed();
        node = node->getParent()->getParent();
      }
      else if (node->getParent() && node == node->getParent()->getRight())
      {
        node = node->getParent();
        rotateLeft(node);
      }
      node->getParent()->makeBlack();
      node->getParent()->getParent()->makeRed();
      rotateRight(node->getParent()->getParent());
    }
    else
    {
      RedBlackNode<T> * temp = node->getParent()->getParent()->getLeft();

      if (temp && temp->isRed())
      {
        node->getParent()->makeBlack();
        temp->makeBlack();
        node->getParent()->getParent()->makeRed();
        node = node->getParent()->getParent();
      }
      else if (node->getParent() && node == node->getParent()->getLeft())
      {
        node = node->getParent();
        rotateRight(node);
      }
      node->getParent()->makeBlack();
      node->getParent()->getParent()->makeRed();
      rotateLeft(node->getParent()->getParent());
    }
  }
  getRoot()->makeBlack();
}

/*


else
{
auto y = z->parent_->parent_->left_;

if (y->color_ == Red)
{
z->parent_->color_ = Black;
y->color_ = Black;
z->parent_->parent_->color_ = Red;
z = z->parent_->parent_;
}
else if(z == z->parent_->left_)
{
z = z->parent_;
right_rotate(t,z);
}
z->parent_->color_ = Black;
z->parent_->parent_->color_ = Red;
left_rotate(t,z->parent_->parent_);
}
}
t->root()->color_ = Black;
*/

template <class T>
void RedBlackTree<T>::remove(RedBlackNode<T> * node)
{
  BNode<T> * temp;
  BNode<T> * next;
  if (node->getLeft() || node->getRight())
  {
    temp = node;
  }
  else
  {
    temp = BinarySearchTree<T>::getSuccessor(node);
  }

  if (temp->getLeft())
  {
    next = temp->getLeft();
  }
  else
  {
    next = temp->getRight();
  }

  temp->setParent(next->getParent());
  if(temp->getParent())
  {
    BinaryTree<T>::forceSetRoot(next);
  }
  else if (temp == temp->getParent()->getLeft())
  {
    temp->getParent()->setLeft(next);
  }
  else {
    temp->getParent()->setRight(next);
  }

  if (temp != node)
  {
    node->setInfo(temp->getInfo());
  }
  if (temp->isBlack())
  {
    removeFixup(next);
  }
}

template <class T>
void RedBlackTree<T>::removeFixup(RedBlackNode<T> * node)
{
  while(!BinaryTree<T>::isRoot(node) && node->isBlack())
  {
    if (node == node->getParent()->getLeft())
    {
      BNode<T> * temp = node->getParent()->getRight();
      if (!temp->isBlack())
      {
        temp->makeBlack();
        temp->getParent()->makeRed();
        rotateLeft(temp);
        temp = node->getParent()->getRight();
      }

      if (temp->getLeft()->isBlack() && temp->getRight()->isBlack())
      {
        temp->makeRed();
        node = node->getParent();
      }
      else if (temp->getRight()->isBlack())
      {
        temp->getLeft()->makeBlack();
        temp->makeRed();
        rotateRight(temp);
        temp = node->getParent()->getRight();
      }
      temp->setColor(!node->getParent()->isBlack());
      node->getParent()->makeBlack();
      temp->getRight()->makeBlack();
      rotateLeft(node->getParent());
      node = BinaryTree<T>::getRoot();
    }
    else
    {
      BNode<T> * temp = node->getParent()->getLeft();
      if (!temp->isBlack())
      {
        temp->makeBlack();
        temp->getParent()->makeRed();
        rotateRight(temp);
        temp = node->getParent()->getLeft();
      }

      if (temp->getRight()->isBlack() && temp->getLeft()->isBlack())
      {
        temp->makeRed();
        node = node->getParent();
      }
      else if (temp->getLeft()->isBlack())
      {
        temp->getRight()->makeBlack();
        temp->makeRed();
        rotateLeft(temp);
        temp = node->getParent()->getLeft();
      }
      temp->setColor(node->getParent()->getColor());
      node->getParent()->makeBlack();
      temp->getLeft()->makeBlack();
      rotateRight(node->getParent());
      node = BinaryTree<T>::getRoot();
    }
  }
  node->makeBlack();
}

// REQUIRES: node is a descendant of root.
// MODIFIES: this.
// EFFECTS: switches info in node and node->Parent. Sets node->leftChild
// to parent->rightChild.
// Performs a left rotation.
template<class T>
void RedBlackTree<T>::rotateLeft(RedBlackNode<T> * node)
{
  RedBlackNode<T> * previousRight = node->getRight();

  node->setRight(previousRight->getLeft());
  if (node->getRight()) node->getRight()->setParent(node);

  if (previousRight->getLeft()) previousRight->getLeft()->setParent(node);

  previousRight->setParent(node->getParent());

  if (!node->getParent())
  {
    BinaryTree<T>::forceSetRoot(previousRight);
  }
  else if (node == node->getParent()->getLeft())
  {
    node->getParent()->setLeft(previousRight);
  }
  else
  {
    node->getParent()->setRight(previousRight);
  }

  previousRight->setLeft(node);
  node->setParent(previousRight);
}

template<class T>
void RedBlackTree<T>::rotateRight(RedBlackNode<T> * node)
{
  RedBlackNode<T> * previousLeft = node->getLeft();

  node->setLeft(previousLeft->getRight());
  if (node->getLeft()) node->getLeft()->setParent(node);

  if (previousLeft->getRight()) previousLeft->getRight()->setParent(node);

  previousLeft->setParent(node->getParent());

  if (!node->getParent())
  {
    BinaryTree<T>::forceSetRoot(previousLeft);
  }
  else if (node == node->getParent()->getRight())
  {
    node->getParent()->setRight(previousLeft);
  }
  else
  {
    node->getParent()->setLeft(previousLeft);
  }

  previousLeft->setRight(node);
  node->setParent(previousLeft);
}

#endif
