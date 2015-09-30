
#include <iostream>
#include "BinaryTree.h"

template<class T>
class BinarySearchTree : public BinaryTree<T>
{
public:
    BinarySearchTree();
    virtual BNode<T>* insertar(T valor);
    BNode<T> * removeNodo(BNode<T> * nodo, T valor);

    BNode<T> * minNodo(BNode<T> * nodo)
    {
      BNode<T> * actual = nodo;
      while (actual->getIzquierdo() != nullptr)
        actual = actual->getIzquierdo();
      return actual;
    }
    void print();
};

template<class T>
BinarySearchTree<T>::BinarySearchTree() : BinaryTree<T>() {}

template<class T>
BNode<T>* BinarySearchTree<T>::insertar(T valor)
{
  BNode<T> * nodo = new BNode<T>(valor);
  BNode<T> * padre;
  nodo->setDerecho(nullptr);
  nodo->setIzquierdo(nullptr);
  padre = nodo->getPadre();
  if(this->empty())
  {
    this->setRaiz(nodo);
  }
  else
  {
    BNode<T> * actual = new BNode<T>();
    actual = this->getRaiz();
    while (actual)
    {
      padre = actual;
      if(nodo->getInfo() >= actual->getInfo())
      {
        actual = actual->getDerecho();
      }
      else
      {
        actual = actual->getIzquierdo();
      }
    }
    if(nodo->getInfo() >= padre->getInfo())
    {
      padre->setDerecho(nodo);
      nodo->setPadre(padre);
    }
    else
    {
      padre->setIzquierdo(nodo);
      nodo->setPadre(padre);
    }
  }
  return nodo;
}

template<class T>
void BinarySearchTree<T>::print()
{
    std::cout<<*this;
}
