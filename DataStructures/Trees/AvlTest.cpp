#include <iostream>
#include "AvlTree.h"

int main (int argc, const char * argv[])
{

  AvlTree<int> * avlt = new AvlTree<int>();
  BNode<int> * m_one = new BNode<int>(1);
  // BNode<int> * m_two = new BNode<int>(2);
  // BNode<int> * m_three = new BNode<int>(3);
  // BNode<int> * m_four = new BNode<int>(4);
  // BNode<int> * m_five = new BNode<int>(5);
  // BNode<int> * m_six = new BNode<int>(6);
  // BNode<int> * m_seven = new BNode<int>(7);
  // BNode<int> * m_eight = new BNode<int>(8);
  // BNode<int> * m_nine = new BNode<int>(9);
  BNode<int> * m_ten = new BNode<int>(10);
  BNode<int> * m_eleven = new BNode<int>(11);
  // BNode<int> * m_twelve = new BNode<int>(12);
  BNode<int> * m_thirteen = new BNode<int>(13);
  // BNode<int> * m_fourteen = new BNode<int>(14);
  BNode<int> * m_fifteen = new BNode<int>(15);
  // BNode<int> * m_sixteen = new BNode<int>(16);
  // BNode<int> * m_seventeen = new BNode<int>(17);
  // BNode<int> * m_eighteen = new BNode<int>(18);
  // BNode<int> * m_nineteen = new BNode<int>(19);
  // BNode<int> * m_twenty = new BNode<int>(20);
  // BNode<int> * m_twentytwo = new BNode<int>(22);
  BNode<int> * m_twentythree = new BNode<int>(23);
  BNode<int> * m_ninety = new BNode<int>(90);
  BNode<int> * m_twentysix = new BNode<int>(26);
  BNode<int> * m_thirty = new BNode<int>(30);
  BNode<int> * m_thirtyfive = new BNode<int>(35);


  // -------------------Insertar valores ------------//
  avlt->insert(m_ten);
  avlt->insert(m_fifteen);
  avlt->insert(m_twentythree);
  avlt->insert(m_ninety);
  avlt->insert(m_thirteen);
  avlt->insert(m_twentysix);
  avlt->insert(m_thirty);
  avlt->insert(m_thirtyfive);
  avlt->insert(m_one);
  avlt->insert(m_eleven);

  std::cout << "=========== ÁRBOL INICIO ============" << std::endl;
  avlt->prettyPrint(avlt->getRoot(),0);


  // std::cout << "=============== TEST DELETE ====================" << std::endl;
  // std::cout << "Eliminando el 1: " << std::endl;
  // avlt->removeNode(m_one);
  // std::cout << "1 eliminado!" << std::endl;
  // std::cout << "Eliminando el 10: " << std::endl;
  // avlt->removeNode(m_ten);
  // std::cout << "10 eliminado!" << std::endl;
  // std::cout << "Eliminando el 13: " << std::endl;
  // avlt->removeNode(m_thirteen);
  // std::cout << "13 eliminado!" << std::endl;
  // std::cout << "Eliminando el 26: " << std::endl;
  // avlt->removeNode(m_twentysix);
  // std::cout << "26 eliminado!" << std::endl;
  // std::cout << "Eliminando el 30: " << std::endl;
  // avlt->removeNode(m_thirty);
  // std::cout << "30 eliminado!" << std::endl;
  // std::cout << "Eliminando el 90: " << std::endl;
  // avlt->removeNode(m_ninety);
  // std::cout << "90 eliminado!" << std::endl;
  // std::cout << "Eliminando el 35: " << std::endl;
  // avlt->removeNode(m_thirtyfive);
  // std::cout << "35 eliminado!" << std::endl;
  std::cout << "Eliminando el 15: " << std::endl;
  avlt->removeNode(m_fifteen);
  std::cout << "15 eliminado!" << std::endl;
  std::cout << "Eliminando el 30: " << std::endl;
  avlt->removeNode(m_thirty);
  std::cout << "30 eliminado!" << std::endl;
  std::cout << "Eliminando el 23: " << std::endl;
  avlt->removeNode(m_twentythree);
  std::cout << "23 eliminado!" << std::endl;
  std::cout << "Eliminando el 13: " << std::endl;
  avlt->removeNode(13);
  std::cout << "13 eliminado!" << std::endl;

  std::cout << "=========== ÁRBOL FINAL ============" << std::endl;
  avlt->prettyPrint(avlt->getRoot(),0);


  std::cout << "La raiz es: " << *avlt->getRoot() << std::endl;
  std::cout << (avlt->isAvl() ? "Es avl" : "No es avl")<< std::endl;

  //Este celar hace que salga un segmentation fault, solución en proceso
  //avlt->clear();

  return 0;
}
