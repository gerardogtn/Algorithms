
#include <iostream>
#include "BNode.h"

template <class T>
class BinaryTree
{
    BNode<T> * raiz = nullptr;

    std::ostream& imprime(std::ostream& os, BNode<T> * nodo);

public:
    BinaryTree();
    BinaryTree(BNode<T> * info);

    ~BinaryTree();
    void clear();
    void clear(BNode<T> * nodo);

    bool empty();
    BNode<T> * getRaiz();
    void setRaiz(BNode<T> * nodo)
    {
        raiz = nodo;
    }
    bool insert(T value, BNode<T> * padre);

    void preOrden();
    void preOrden(BNode<T> * nodo);
    void preOrden(BNode<T> * nodo, T info);

    void inOrden();
    void inOrden(BNode<T> * nodo);

    void revOrden();
    void revOrden(BNode<T> * nodo);

    void postOrden();
    void postOrden(BNode<T> * nodo);

    template <typename Tn>
    friend std::ostream& operator<<(std::ostream& os, BinaryTree<Tn> &arbol);

    int nivel(BNode<T> * nodo);

    BNode<T> * suma_ineficiente();
    BNode<T> * suma_ineficiente(BNode<T> * nodo);
    T suma();
    T suma_eficiente(BNode<T> * nodo);
    void suma_eficiente(BNode<T> * nodo, BNode<T> * acumulador);
    T suma(BNode<T> * nodo);

    BNode<T> * getPadre(T info);
    void hermanos(BNode<T> * n1);
    bool sonHermanos(T n1, T n2);
    bool sonHermanos(BNode<T> * n1, BNode<T> * n2);

    void primosHermanos(BNode<T> * nodo, BNode<T> * raiz);
    void ancestros(BNode<T> *nodo);

    BNode<T> * buscar (T info);
    BNode<T> * buscar (T info, BNode<T> * nodo);
};

template <class T>
BinaryTree<T>::BinaryTree() {}

template <class T>
BinaryTree<T>::BinaryTree(BNode<T> * info)
{
  raiz = info;
}

template <class T>
BinaryTree<T>::~BinaryTree()
{
  clear(raiz);
}

template <class T>
void BinaryTree<T>::clear()
{
  clear(raiz);
}

template <class T>
void BinaryTree<T>::clear(BNode<T> * nodo)
{
  if (nodo)
  {
    clear(nodo->getIzquierdo());
    clear(nodo->getDerecho());

    delete nodo;
  }
}

template <class T>
bool BinaryTree<T>::empty()
{
  return (raiz == nullptr);
}

template <class T>
BNode<T> * BinaryTree<T>::getRaiz()
{
  return raiz;
}

template <class T>
bool BinaryTree<T>::insert(T value, BNode<T> * padre)
{
  if (!padre)
    raiz = new BNode<T>(value);
  else
  {
    if (!padre->getIzquierdo())
    {
      BNode<T> * nuevo = new BNode<T>(value);
      nuevo->setPadre(padre);
      padre->setIzquierdo(nuevo);
    }
    else if (!padre->getDerecho())
    {
      BNode<T> * nuevo = new BNode<T>(value);
      nuevo->setPadre(padre);
      padre->setDerecho(nuevo);
    }
    else
      return false;
  }
  return true;
}

template <class T>
void BinaryTree<T>::preOrden()
{
  preOrden(raiz);
}

template <class T>
void BinaryTree<T>::preOrden(BNode<T> * nodo) {
    if (nodo)
    {
      std::cout << *nodo << std::endl;
      preOrden(nodo->getIzquierdo());
      preOrden(nodo->getDerecho());
    }
}

template <class T>
void BinaryTree<T>::preOrden(BNode<T> * nodo, T info)
{
  if (nodo)
  {
    if (!(nodo->getInfo() == info))
        std::cout << *nodo->getInfo() << std::endl;
    preOrden(nodo->getIzquierdo());
    preOrden(nodo->getDerecho());
  }
}

template <class T>
void BinaryTree<T>::inOrden()
{
  inOrden(raiz);
}

template <class T>
void BinaryTree<T>::inOrden(BNode<T> * nodo)
{
  if (nodo)
  {
    inOrden(nodo->getIzquierdo());
    std::cout << *nodo << " ";
    inOrden(nodo->getDerecho());
  }
}

template <class T>
void BinaryTree<T>::revOrden()
{
  revOrden(raiz);
}

template <class T>
void BinaryTree<T>::revOrden(BNode<T> * nodo)
{
  if (nodo)
  {
    revOrden(nodo->getDerecho());
    std::cout << *nodo << " ";
    revOrden(nodo->getIzquierdo());
  }
}
template <class T>
void BinaryTree<T>::postOrden()
{
  postOrden(raiz);
}

template <class T>
void BinaryTree<T>::postOrden(BNode<T> * nodo)
{
  if (nodo)
  {
    postOrden(nodo->getIzquierdo());
    postOrden(nodo->getDerecho());
    std::cout << *nodo << " ";
  }
}

template <class T>
int BinaryTree<T>::nivel(BNode<T> *nodo)
{
  if (nodo == nullptr)
      return 0;

  BNode<T> * aux = nodo;
  int nivel = 1;
  while (aux->getPadre())
  {
    ++nivel;
    aux = aux->getPadre();
  }
  return nivel;
}


template <class T>
BNode<T> * BinaryTree<T>::buscar(T info)
{
  return buscar(info, raiz);
}

template <class T>
BNode<T> * BinaryTree<T>::buscar(T info, BNode<T> * node)
{
  if (node == nullptr)
  {
    return nullptr;
  }
  else
  {
    if (info == node->getInfo())
    {
      return node;
    }
    else if (info < node->getInfo())
    {
      return buscar(info, node->getIzquierdo());
    }
    else
    {
      return buscar(info, node->getDerecho());
    }
  }
}

template <class T>
BNode<T> * BinaryTree<T>::getPadre(T info)
{
  BNode<T> * nodo = buscar(info);
  return nodo->getPadre();
}

template <class T>
void BinaryTree<T>::hermanos(BNode<T> * nodo)
{
  BNode<T> * izquierdo = nodo->getPadre()->getIzquierdo();
  BNode<T> * derercho = nodo->getPadre()->getDerecho();
  if (izquierdo && izquierdo != nodo)
  {
    std::cout << *izquierdo->getInfo();
  }
  if (derercho && derercho != nodo)
  {
    std::cout << *derercho->getInfo();
  }
}

template <class T>
bool BinaryTree<T>::sonHermanos(T n1, T n2)
{
  return sonHermanos(buscar(n1), buscar(n2));
}

template <class T>
bool BinaryTree<T>::sonHermanos(BNode<T> * n1, BNode<T> * n2)
{
  if (n1 == nullptr || n2 == nullptr || n1 == n2)
  {
    return false;
  }
  return (n1->getPadre() == n2->getPadre());
}

template <class T>
void BinaryTree<T>::primosHermanos(BNode<T> *nodo, BNode<T> *raiz)
{
  if (raiz)
  {
    if (nivel(nodo) == nivel(raiz) && sonHermanos(nodo->getPadre(), raiz->getPadre()))
    {
      std::cout << *raiz->getInfo() << std::endl;
    }
    primosHermanos(nodo, raiz->getIzquierdo());
    primosHermanos(nodo, raiz->getDerecho());
  }
}

template <class T>
void BinaryTree<T>::ancestros(BNode<T> *nodo)
{
  BNode<T> * padre = nodo->getPadre();
  while (padre)
  {
    std::cout << *padre->getInfo() << std::endl;
    padre = padre->getPadre();
  }
}

template <class T>
BNode<T> * BinaryTree<T>::suma_ineficiente() {
    return suma_ineficiente(raiz);
}

template <class T>
BNode<T> * BinaryTree<T>::suma_ineficiente(BNode<T> * nodo)
{
  T valor;
  if (nodo)
  {
    valor = nodo->getInfo();
    BNode<T> * suma_ineficiente_izq = suma_ineficiente(nodo->getIzquierdo());
    if (suma_ineficiente_izq)
    {
      valor += suma_ineficiente_izq->getInfo();
      delete suma_ineficiente_izq;
    }
    BNode<T> * suma_ineficiente_der = suma_ineficiente(nodo->getDerecho());
    if (suma_ineficiente_der)
    {
      valor += suma_ineficiente_der->getInfo();
      delete suma_ineficiente_der;
    }
    return new BNode<T>(valor);
  }
  return nullptr;
}

template <class T>
T BinaryTree<T>::suma_eficiente(BNode<T> * nodo)
{
  BNode<T> * acumulador = new BNode<T>(0);
  suma_eficiente(nodo, acumulador);
  T valor = acumulador->getInfo();
  delete acumulador;
  return valor;
}

template <class T>
void BinaryTree<T>::suma_eficiente(BNode<T> * nodo, BNode<T> * acumulador)
{
  if (nodo)
  {
    acumulador->setInfo(acumulador->getInfo() + nodo->getInfo());
    suma_eficiente(nodo->getIzquierdo(), acumulador);
    suma_eficiente(nodo->getDerecho(), acumulador);
  }
}

template <class T>
T BinaryTree<T>::suma()
{
  return suma(raiz);
}

template <class T>
T BinaryTree<T>::suma(BNode<T> *nodo)
{
  static T valor;
  if (nodo)
  {
    valor += nodo->getInfo();
    suma(nodo->getIzquierdo());
    suma(nodo->getDerecho());
  }
  return valor;
}

template <class T>
std::ostream& BinaryTree<T>::imprime(std::ostream& os, BNode<T> * nodo)
{
  if (nodo)
  {
    os << *nodo;
    imprime(os, nodo->getIzquierdo());
    imprime(os, nodo->getDerecho());
  }
  return os;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, BinaryTree<T> &arbol)
{
  return arbol.imprime(os, arbol.raiz);
}
