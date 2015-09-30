
#include "BinarySearchTree.h"
#include <assert.h>
#include <iomanip>

template<class T>
class RedBlack : public BinarySearchTree<T>
{
public:
  RedBlack();

  BNode<T> * grandParent(BNode<T> * nodo);
  BNode<T> * uncle(BNode<T> * nodo);
  BNode<T> * sibling(BNode<T> * nodo);
  BNode<T> * maximum_node(BNode<T> * nodo);

  void verifyProperties(RedBlack * arbol);
  void verifyProperty1(BNode<T> * nodo);
  void verifyProperty2(BNode<T> * nodo);
  void verifyProperty3(BNode<T> * nodo);
  void verifyProperty4(BNode<T> * root);
  void verifyProperty4Helper(BNode<T> * nodo, int contNegros, int& blackPath);

  std::string color(BNode<T> * nodo);

  void rotateLeft(RedBlack * arbol, BNode<T> * nodo);
  void rotateRight(RedBlack * arbol, BNode<T> * nodo);

  void RBinsert(T valor);
  void RBinsert1(RedBlack * arbol, BNode<T> * nodo);
  void RBinsert2(RedBlack * arbol, BNode<T> * nodo);
  void RBinsert3(RedBlack * arbol, BNode<T> * nodo);
  void RBinsert4(RedBlack * arbol, BNode<T> * nodo);
  void RBinsert5(RedBlack * arbol, BNode<T> * nodo);

  void RBdelete(T valor);
  void RBdelete1(RedBlack * arbol, BNode<T> * nodo);
  void RBdelete2(RedBlack * arbol, BNode<T> * nodo);
  void RBdelete3(RedBlack * arbol, BNode<T> * nodo);
  void RBdelete4(RedBlack * arbol, BNode<T> * nodo);
  void RBdelete5(RedBlack * arbol, BNode<T> * nodo);
  void RBdelete6(RedBlack * arbol, BNode<T> * nodo);

  void prettyPrint(BNode<T>* p, int indent);

  void verificarArbol(RedBlack<T> * arbol);
};

template<class T>
RedBlack<T>::RedBlack() : BinarySearchTree<T>() {}

template<class T>
BNode<T> * RedBlack<T>::grandParent(BNode<T> * nodo)
{
  if(nodo != nullptr && nodo->getPadre() != nullptr)
    return nodo->getPadre()->getPadre();
  else
    return nullptr;
}

template<class T>
BNode<T> * RedBlack<T>::uncle(BNode<T> * nodo)
{
  BNode<T> * abuelo = grandParent(nodo);
  if(abuelo == nullptr)
    return nullptr;
  else if(nodo->getPadre() == abuelo->getIzquierdo())
    return abuelo->getDerecho();
  else
    return abuelo->getIzquierdo();
}

template<class T>
BNode<T> * RedBlack<T>::sibling(BNode<T> * nodo)
{
  if(nodo != nullptr && nodo->getPadre() != nullptr)
  {
    if(nodo == nodo->getPadre()->getIzquierdo())
      return nodo->getPadre()->getDerecho();
    else
      return nodo->getPadre()->getIzquierdo();
  }
  else
    return nullptr;
}

template<class T>
BNode<T> * RedBlack<T>::maximum_node(BNode<T> * nodo)
{
  assert (nodo != nullptr);
  while (nodo->getDerecho() != nullptr)
  {
    nodo = nodo->getDerecho();
  }
  return nodo;
}

template<class T>
void RedBlack<T>::verifyProperties(RedBlack * arbol)
{
  verifyProperty1(arbol->getRaiz());
  verifyProperty2(arbol->getRaiz());
  verifyProperty3(arbol->getRaiz());
  verifyProperty4(arbol->getRaiz());
}

template<class T>
void RedBlack<T>::verifyProperty1(BNode<T> * nodo)
{
  if(nodo == nullptr)
    return;
  assert(nodo->getColor() == "negro" || nodo->getColor() == "rojo");
  verifyProperty1(nodo->getIzquierdo());
  verifyProperty1(nodo->getDerecho());
}

template<class T>
void RedBlack<T>::verifyProperty2(BNode<T> * nodo)
{
  assert(color(nodo) == "negro");
}

template<class T>
void RedBlack<T>::verifyProperty3(BNode<T> * nodo)
{
  if (nodo == nullptr)
    return;

  if (color(nodo) == "rojo")
  {
    assert(color(nodo->getIzquierdo()) == "negro");
    assert(color(nodo->getDerecho()) == "negro");
    assert(color(nodo->getPadre()) == "negro");
  }
  verifyProperty3(nodo->getIzquierdo());
  verifyProperty3(nodo->getDerecho());
}

template <class T>
void RedBlack<T>::verifyProperty4(BNode<T> * root)
{
  int blackPath = -1;
  std::string mensaje="";
  return verifyProperty4Helper(root, 0, blackPath);
}

template <class T>
void RedBlack<T>::verifyProperty4Helper(BNode<T> * nodo, int contNegros, int& blackPath)
{
  std::string color;
  if (nodo != nullptr)
  {
    color = nodo->getColor();
  }
  else
  {
    color = "";
  }

  if (color == "negro")
  {
    contNegros++;
  }
  if (nodo == nullptr)
  {
    if (blackPath == -1)
    {
      blackPath = contNegros;
    }
    else
    {
      if (contNegros != blackPath)
      {
        std::cout << "No es RedBlack" << std::endl;
      }
    }
    return;
  }
  verifyProperty4Helper(nodo->getIzquierdo(),  contNegros, blackPath);
  verifyProperty4Helper(nodo->getDerecho(), contNegros, blackPath);

  return;
}

template<class T>
std::string RedBlack<T>::color(BNode<T> * nodo)
{
  if(nodo == nullptr)
    return "negro";
  else
    return nodo->getColor();
}

template<class T>
void RedBlack<T>::rotateLeft(RedBlack * arbol, BNode<T> * Xnode)
{
  BNode<T> *Ynodey;
  if(Xnode->getDerecho() == NULL)
  {
    return;
  }
  Ynodey = Xnode->getDerecho();
  if(Ynodey->getIzquierdo() != NULL)
  {
      Ynodey->getIzquierdo()->setPadre(Xnode);
      Xnode->setDerecho(Ynodey->getIzquierdo());
  }
  Ynodey->setPadre(Xnode->getPadre());
  if(Xnode->getPadre() == NULL)
  {
    this->setRaiz(Ynodey);
  }
  else if(Xnode == Xnode->getPadre()->getIzquierdo())
  {
    Xnode->getPadre()->setIzquierdo(Ynodey);
  }
  else
  {
    Xnode->getPadre()->setDerecho(Ynodey);
  }
  Xnode->setDerecho(Ynodey->getIzquierdo());
  Ynodey->setIzquierdo(Xnode);
  Xnode->setPadre(Ynodey);
}

template<class T>
void RedBlack<T>::rotateRight(RedBlack * arbol, BNode<T> * Ynodey)
{
  BNode<T> *Xnode;
  if(Ynodey->getIzquierdo() == NULL)
  {
    return;
  }
  Xnode = Ynodey->getIzquierdo();
  if(Xnode->getDerecho() != NULL)
  {
    Xnode->getDerecho()->setPadre(Ynodey);
    Ynodey->setIzquierdo(Xnode->getDerecho());
  }
  Xnode->setPadre(Ynodey->getPadre());
  if(Ynodey->getPadre() == NULL)
  {
    this->setRaiz(Xnode);
  }else if(Ynodey == Ynodey->getPadre()->getIzquierdo())
  {
    Ynodey->getPadre()->setIzquierdo(Xnode);
  }
  else
  {
    Ynodey->getPadre()->setDerecho(Xnode);
  }
  Ynodey->setIzquierdo(Xnode->getDerecho());
  Xnode->setDerecho(Ynodey);
  Ynodey->setPadre(Xnode);
}

template<class T>
void RedBlack<T>::RBinsert(T valor)
{
  BNode<T> * nodo = this->insertar(valor);
  nodo->setColor("rojo");
  RBinsert1(this, nodo);
  verifyProperties(this);
}

template<class T>
void RedBlack<T>::RBinsert1(RedBlack * arbol, BNode<T> * nodo)
{
  if(nodo->getPadre() == nullptr)
    nodo->setColor("negro");
  else
    RBinsert2(this, nodo);
}

template<class T>
void RedBlack<T>::RBinsert2(RedBlack * arbol, BNode<T> * nodo)
{
  if(nodo->getPadre()->getColor() == "negro")
    return;
  else
    RBinsert3(this, nodo);
}

template<class T>
void RedBlack<T>::RBinsert3(RedBlack * arbol, BNode<T> * nodo)
{
  if(color(uncle(nodo)) == "rojo")
  {
    nodo->getPadre()->setColor("negro");
    uncle(nodo)->setColor("negro");
    grandParent(nodo)->setColor("rojo");
    RBinsert1(arbol, grandParent(nodo));
  }
  else
  {
    RBinsert4(arbol, nodo);
  }
}

template<class T>
void RedBlack<T>::RBinsert4(RedBlack * arbol, BNode<T> * nodo)
{
  if(nodo == nodo->getPadre()->getDerecho() && nodo->getPadre() == grandParent(nodo)->getIzquierdo())
  {
    rotateLeft(arbol, nodo->getPadre());
    nodo = nodo->getIzquierdo();
  }
  else if(nodo == nodo->getPadre()->getIzquierdo() && nodo->getPadre() == grandParent(nodo)->getDerecho())
  {
    rotateRight(arbol, nodo->getPadre());
    nodo = nodo->getDerecho();
  }
  RBinsert5(arbol, nodo);
}

template<class T>
void RedBlack<T>::RBinsert5(RedBlack * arbol, BNode<T> * nodo)
{
  nodo->getPadre()->setColor("negro");
  grandParent(nodo)->setColor("rojo");
  if (nodo == nodo->getPadre()->getIzquierdo() && nodo->getPadre() == grandParent(nodo)->getIzquierdo())
  {
    rotateRight(arbol, grandParent(nodo));
  }
  else
  {
    assert(nodo == nodo->getPadre()->getDerecho() && nodo->getPadre() == grandParent(nodo)->getDerecho());
    rotateLeft(arbol, grandParent(nodo));
  }
}

template <class T>
void RedBlack<T>::RBdelete(T valor)
{
  BNode<T> * hijo;
  BNode<T> * nodo;
  nodo = this->buscar(valor);
  if (nodo == nullptr)
    return;

  if (nodo->getIzquierdo() != nullptr && nodo->getDerecho() != nullptr)
  {
    BNode<T> * pred = maximum_node(nodo->getIzquierdo());
    nodo->setInfo(pred->getInfo());
    nodo = pred;
  }
  assert(nodo->getIzquierdo() == NULL || nodo->getDerecho() == nullptr);
  hijo = nodo->getDerecho() == nullptr ? nodo->getIzquierdo()  : nodo->getDerecho();
  if (color(nodo) == "negro")
  {
    nodo->getColor() = color(hijo);
    RBdelete1(this, nodo);
  }
  if (nodo->getPadre() == nullptr)
  {
    this->setRaiz(hijo);
  }
  else
  {
    if (nodo == nodo->getPadre()->getIzquierdo())
      nodo->getPadre()->setIzquierdo(hijo);
    else
      nodo->getPadre()->setDerecho(hijo);
  }
  if (hijo != nullptr)
  {
    hijo->setPadre(nodo->getPadre());
  }
  delete nodo;
  verifyProperties(this);
}

template <class T>
void RedBlack<T>::RBdelete1(RedBlack * arbol, BNode<T> * nodo)
{
  if(nodo->getPadre() == nullptr)
    return;
  else
    RBdelete2(this, nodo);
}

template <class T>
void RedBlack<T>::RBdelete2(RedBlack * arbol, BNode<T> * nodo)
{
  if (color(sibling(nodo)) == "rojo")
  {
    nodo->getPadre()->setColor("rojo");
    sibling(nodo)->setColor("negro");
    if (nodo == nodo->getPadre()->getIzquierdo())
      rotateLeft(this, nodo->getPadre());
    else
      rotateRight(this, nodo->getPadre());
  }
  RBdelete3(this, nodo);
}

template <class T>
void RedBlack<T>::RBdelete3(RedBlack * arbol, BNode<T> * nodo)
{
  if (color(nodo->getPadre()) == "negro" && color(sibling(nodo)) == "negro" && color(sibling(nodo)->getIzquierdo()) == "negro" && color(sibling(nodo)->getDerecho()) == "negro")
  {
    sibling(nodo)->setColor("rojo");
    RBdelete1(this, nodo->getPadre());
  }
  else
    RBdelete4(this, nodo);
}

template <class T>
void RedBlack<T>::RBdelete4(RedBlack * arbol, BNode<T> * nodo)
{
  if (color(nodo->getPadre()) == "rojo" && color(sibling(nodo)) == "negro" &&  color(sibling(nodo)->getIzquierdo()) == "negro" && color(sibling(nodo)->getDerecho()) == "negro")
  {
    sibling(nodo)->setColor("rojo");
    nodo->getPadre()->setColor("negro");
  }
  else
    RBdelete5(this, nodo);
}

template<class T>
void RedBlack<T>::RBdelete5(RedBlack * arbol, BNode<T> * nodo)
{
  if (nodo == nodo->getPadre()->getIzquierdo() && color(sibling(nodo)) == "negro" && color(sibling(nodo)->getIzquierdo()) == "rojo" && color(sibling(nodo)->getDerecho()) == "negro")
  {
    sibling(nodo)->setColor("rojo");
    sibling(nodo)->getIzquierdo()->setColor("negro");
    rotateRight(this, sibling(nodo));
  }
  else if (nodo == nodo->getPadre()->getDerecho() && color(sibling(nodo)) == "negro" && color(sibling(nodo)->getDerecho()) == "rojo" && color(sibling(nodo)->getIzquierdo()) == "negro")
  {
    sibling(nodo)->setColor("rojo");
    sibling(nodo)->getDerecho()->setColor("negro");
    rotateLeft(this, sibling(nodo));
  }
  RBdelete6(this, nodo);
}

template<class T>
void RedBlack<T>::RBdelete6(RedBlack * arbol, BNode<T> * nodo)
{
  sibling(nodo)->setColor(color(nodo->getPadre()));
  nodo->getPadre()->setColor("negro");
  if (nodo == nodo->getPadre()->getIzquierdo())
  {
    assert(color(sibling(nodo)->getDerecho()) == "rojo");
    sibling(nodo)->getDerecho()->setColor("negro");
    rotateLeft(this, nodo->getPadre());
  }
  else
  {
    assert(color(sibling(nodo)->getIzquierdo()) == "rojo");
    sibling(nodo)->getIzquierdo()->setColor("negro");
    rotateRight(this, nodo->getPadre());
  }
}

template <class T>
void RedBlack<T>::prettyPrint(BNode<T>* p, int indent)
{
  if (p != nullptr)
  {
    if (p->getDerecho())
    {
      prettyPrint(p->getDerecho(), indent + 4);
    }
    if (indent)
    {
      std::cout << std::setw(indent) << ' ';
    }
    if (p->getDerecho()) std::cout << " /\n" << std::setw(indent) << ' ';
    {
      std::cout << p->getInfo() << "|" << p->getColor() << "\n ";
    }
    if (p->getIzquierdo())
    {
      std::cout << std::setw(indent) << ' ' << " \\\n";
      prettyPrint(p->getIzquierdo(), indent + 4);
    }
  }
}

template<class T>
void RedBlack<T>::verificarArbol(RedBlack<T> * arbol)
{
  verifyProperties(arbol);
}
