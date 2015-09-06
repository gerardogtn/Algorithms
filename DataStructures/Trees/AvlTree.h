#ifndef Avltree_h
#define Avltree_h

#include "BinarySearchTree.h"

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

  virtual bool remove(const T item);
  virtual bool remove(BNode<T> * item);

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
BNode<T>* AvlTree<T>::rotateright(BNode<T> * node)
{
  BNode<T> * pivot = node->getParent();
  BNode<T> * temp = node->getRight();
  bool isRoot = BinaryTree<T>::isRoot(pivot);

  std::cout << "================ ANTES ==================" << std::endl;
  std::cout << "Node es:" << *node << std::endl;
  std::cout << "Hijo izquierdo node: " << *node->getLeft() << std::endl;
  std::cout << "Hijo derecho node: " << node->getRight() << std::endl;
  if (node->getParent())
  {
    std::cout << "Padre de node: " << *node->getParent() << std::endl;
  }
  else {
    std::cout << "Padre de node: no tiene padre" << std::endl;
  }


  std::cout << "Pivot es:" << *pivot << std::endl;
  std::cout << "Hijo izquierdo Pivot: " << *pivot->getLeft() << std::endl;
  std::cout << "Hijo derecho Pivot: " << pivot->getRight() << std::endl;
  std::cout << "Padre de Pivot: " << pivot->getParent() << std::endl;


  node->setParent(pivot->getParent());
  node->setRight(pivot);
  pivot->setLeft(temp);
  pivot->setParent(node);



  if (isRoot)
  {
    BinaryTree<T>::forceSetRoot(node);
  }
  else
  {
    node->getParent()->setLeft(node);
  }

  std::cout << "================ DESPUES ==================" << std::endl;
  std::cout << "Node es:" << *node << std::endl;
  std::cout << "Hijo izquierdo node: " << *node->getLeft() << std::endl;
  std::cout << "Hijo derecho node: " << *node->getRight() << std::endl;
  if (node->getParent())
  {
    std::cout << "Padre de node: " << *node->getParent() << std::endl;
  }
  else {
    std::cout << "Padre de node: no tiene padre" << std::endl;
  }

  std::cout << "Pivot es:" << *pivot << std::endl;
  std::cout << "Hijo izquierdo Pivot: " << pivot->getLeft() << std::endl;
  std::cout << "Hijo derecho Pivot: " << pivot->getRight() << std::endl;
  std::cout << "Padre de Pivot: " << *pivot->getParent() << std::endl;

  std::cout << "Groot's left child: " << *BinaryTree<T>::getRoot()->getLeft() << std::endl;

  return node;
}

template <class T>
BNode<T>* AvlTree<T>::rotateleft(BNode<T> * node)
{
  BNode<T> * other = node->getParent();
  if (BinaryTree<T>::isRoot(other))
  {
    node->setParent(other->getParent());
    other->setParent(node);
    other->setRight(node->getLeft());
    node->setLeft(other);
    BinaryTree<T>::setRoot(node);
  }
  else
  {
    node->setParent(other->getParent());
    other->getParent()->setRight(node);
    other->setParent(node);
    node->setLeft(other);
    other->setRight(nullptr);

  }

  return other;
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
template <class T>
bool AvlTree<T>::remove(const T item)
{
  return remove(BinarySearchTree<T>::searchGetNode(item));
}

// REQUIRES: item is in Avl Tree
// MODIFIES: this.
// EFFECTS: Returns true if item was deleted.
// INVARIANT: Avl is balanced.
template <class T>
bool AvlTree<T>::remove(BNode<T> * item)
{
  if (item == nullptr)
  {
    return false;
  }
  else
  {
    BNode<T> * parent = item->getParent();
    BNode<T> * leftChild = item->getLeft();
    BNode<T> * rightChild = item->getRight();
    BNode<T> * next = BinaryTree<T>::getMaxMin(item);
    bool insertLeft = parent->getInfo() < item->getInfo();
    if (insertLeft)
    {
      next->getParent()->setRight(next->getLeft());
      next->setLeft(leftChild);
      leftChild->setParent(next);
      next->setParent(parent);
      parent->setLeft(next);
      next->setRight(rightChild);
      rightChild->setParent(next);
    }
    else
    {
      next->getParent()->setRight(next->getLeft());
      next->setLeft(leftChild);
      leftChild->setParent(next);
      next->setParent(parent);
      parent->setRight(next);
      next->setRight(rightChild);
      rightChild->setParent(next);
    }
    delete item;

    balance(next);
  }
  return true;

}


#endif
