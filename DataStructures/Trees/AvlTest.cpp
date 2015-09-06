#include <iostream>
#include "AvlTree.h"

int main (int argc, const char * argv[])
{

  AvlTree<int> * avlt = new AvlTree<int>();
  BNode<int> * m_two = new BNode<int>(2);
  BNode<int> * m_three = new BNode<int>(3);
  BNode<int> * m_four = new BNode<int>(4);
  BNode<int> * m_six = new BNode<int>(6);
  BNode<int> * m_ten = new BNode<int>(10);
  BNode<int> * m_eleven = new BNode<int>(11);
  BNode<int> * m_twelve = new BNode<int>(12);
  BNode<int> * m_thirteen = new BNode<int>(13);
  BNode<int> * m_fifteen = new BNode<int>(15);


  avlt->insert(m_two);
  avlt->insert(m_three);
  avlt->insert(m_four);
  avlt->insert(m_six);
  avlt->insert(m_ten);
  avlt->insert(m_eleven);
  // avlt->insert(m_twelve);
  // avlt->insert(m_thirteen);
  // avlt->insert(m_fifteen);

  std::cout << "Imprimiendo en orden ascendente" << std::endl;
  avlt->inOrder();
  //
  // std::cout << "Imprimiendo en orden descendente" << std::endl;
  // avlt->inverseInOrder();

  std::cout << "=============== TEST BALANCE FACTOR ====================" << std::endl;
  std::cout << "Balance Factor, elemento 2: " << avlt->getBalanceFactor(m_two)<< std::endl;
  std::cout << "Balance Factor, elemento 3: " << avlt->getBalanceFactor(m_three)<< std::endl;
  std::cout << "Balance Factor, elemento 4: " << avlt->getBalanceFactor(m_four)<< std::endl;
  std::cout << "Balance Factor, elemento 6: " << avlt->getBalanceFactor(m_six)<< std::endl;
  std::cout << "Balance Factor, elemento 10: " << avlt->getBalanceFactor(m_ten)<< std::endl;
  std::cout << "Balance Factor, elemento 11: " << avlt->getBalanceFactor(m_eleven)<< std::endl;
  std::cout << "Balance Factor, elemento 12: " << avlt->getBalanceFactor(m_twelve)<< std::endl;
  std::cout << "Balance Factor, elemento 13: " << avlt->getBalanceFactor(m_thirteen)<< std::endl;
  std::cout << "Balance Factor, elemento 15: " << avlt->getBalanceFactor(m_fifteen)<< std::endl;

  std::cout << "La raiz es: " << *avlt->getRoot() << std::endl;

  std::cout << (avlt->isAvl() ? "Es avl" : "No es avl")<< std::endl;

  avlt->clear();

  return 0;
}
