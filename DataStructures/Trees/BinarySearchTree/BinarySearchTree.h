

#ifndef BinarySearchTree_h
#define BinarySearchTree_h

#include "../BinaryTree/BinaryTree.h"

template<class T>
class BinarySearchTree : public BinaryTree<T>{

private:
  BinaryNode<T> *  searchGetNode(const T & target) const;
  BinaryNode<T> *  searchGetNode(BinaryNode<T> * current, const T & target) const;

  virtual bool insert(BinaryNode<T> * &current, const T & target);
  bool remove(BinaryNode<T> * &current, const T & target);
  bool removeRoot(BinaryNode<T> * &current);

protected:

public:
  BinarySearchTree();
  virtual ~BinarySearchTree();

  bool search(const T & item) const;
  virtual bool insert(const T & target);
  bool remove(const T & target);

  void printAscending();
  void printDescending();

  void toInOrderArray(T * array, int arraySize);
  void toInOrderArray(BinaryNode<T> * node, T * array, int arraySize, int & i);

  using BinaryTree<T>::isBST;
  virtual bool isBST(){return true;};

};

template <class T>
BinarySearchTree<T>::BinarySearchTree() : BinaryTree<T>(){};

template <class T>
BinarySearchTree<T>::~BinarySearchTree() {};

// REQUIRES: None.
// MODIFIES: None.
// EFFECTS: If target is found in some node, return node. Else return nullptr.
template <class T>
bool BinarySearchTree<T>::search(const T & item) const
{
  BinaryNode<T> * node = searchGetNode(this->root, item);
  if (node)
    return true;
  else
    return false;
}

// REQUIRES: None.
// MODIFIES: None.
// EFFECTS: If target is found in some node, return node. Else return nullptr.
template <class T>
BinaryNode<T> * BinarySearchTree<T>::searchGetNode(const T & item) const
{
  return searchGetNode(this->root, item);
}

// REQUIRES: None.
// MODIFIES: None.
// EFFECTS: If target is found in some node, return node. Else return nullptr.
template <class T>
BinaryNode<T> * BinarySearchTree<T>::searchGetNode(BinaryNode<T> * current,
    const T & target) const
{
  bool output = false;
  while (current != nullptr && !output)
  {
    if (target == current->getInfo())
      output = true;
    else if (target < current->getInfo())
      current = current->getLeft();
    else
      current = current->getRight();
  }

  return current;
}

// REQUIRES: None.
// MODIFIES: this.
// EFFECTS: If item is not duplicate, insert item in valid position. Else do
// nothing
template <class T>
bool BinarySearchTree<T>::insert(const T &item)
{
  return insert(this->root, item);
}

// REQUIRES: current is in tree or nullptr.
// MODIFIES: this.
// EFFECTS: If item is not duplicate, insert item in valid position. Else do
// nothing
template <class T>
bool BinarySearchTree<T>::insert(BinaryNode<T> * & current, const T &target)
{
  // If this->empty() then current is root.
  if (current == nullptr)
  {
    current = new BinaryNode<T>(target);
    return true;
  }
  else if (target < current->getInfo())
    return insert(current->getLeft(), target);
  else if (target > current->getInfo())
    return insert(current->getRight(), target);
  else
    return false;
}


// REQUIRES: None
// MODIFIES: this.
// EFFECTS: If target is found, delete node with info == target and return true.
// else return false.
template <class T>
bool BinarySearchTree<T>::remove(const T & target)
{
  return remove(this->root, target);
}

// REQUIRES: current is in tree or is nullptr.
// MODIFIES: this.
// EFFECTS: If target is found, delete node with info == target and return true.
// else return false.
template <class T>
bool BinarySearchTree<T>::remove(BinaryNode<T> * & current, const T & target)
{
  if (current == nullptr || current->getInfo() == target)
    return removeRoot(current);
  else if (target < current->getInfo())
    return remove(current->getLeft(), target);
  else
    return remove(current->getRight(), target);
}

// REQUIRES: current is nullptr or is in tree.
// MODIFIES: this
// EFFECTS: If current is nullptr, return false. Otherwise root is removed,
// current is set as new root and return true.
// INVARIANT: Tree is a BST.
template <class T>
bool BinarySearchTree<T>::removeRoot(BinaryNode<T> * &current)
{
  if (current == nullptr)
    return false;

  BinaryNode<T> * deleteTarget = current;

  if (current->getRight() == nullptr)
    current = current->getLeft();
  else if (current->getLeft() == nullptr)
    current = current->getRight();
  else
  {
    deleteTarget = current->getLeft();
    BinaryNode<T> * parent = current;

    while (deleteTarget->getRight() != nullptr)
    {
      parent = deleteTarget;
      deleteTarget = deleteTarget->getRight();
    }

    current->setInfo(deleteTarget->getInfo());

    if (parent == current)
      current->setLeft(deleteTarget->getLeft());
    else
      parent->setRight(deleteTarget->getLeft());
  }
  delete deleteTarget;
  return true;
}

template <class T>
void BinarySearchTree<T>::printAscending()
{
  this->inOrder();
}

template <class T>
void BinarySearchTree<T>::printDescending()
{
  this->inverseInOrder();
}


#endif
