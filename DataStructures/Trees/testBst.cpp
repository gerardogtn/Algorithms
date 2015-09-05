
#include <iostream>
#include "BinarySearchTree.h"

int main(int argc, const char * argv[])
{

  BinarySearchTree<int> * bst = new BinarySearchTree<int>();
  BNode<int> * five = new BNode<int>(5);
  BNode<int> * three = new BNode<int>(3);
  BNode<int> * four = new BNode<int>(4);
  BNode<int> * six = new BNode<int>(6);
  BNode<int> * nine = new BNode<int>(9);
  BNode<int> * ten = new BNode<int>(10);

  bst->insert(five);
  bst->insert(three);
  bst->insert(four);
  bst->insert(six);
  bst->insert(nine);
  bst->insert(ten);
  bst->insert(9);

  std::cout << "Imprimiendo en orden ascendente" << std::endl;
  bst->inOrder();

  std::cout << "Imprimiendo en orden descendente" << std::endl;
  bst->inverseInOrder();

  std::cout << (bst->search(5)? "Encontre 5" : "No encontre 5") << std::endl;
  std::cout << (bst->search(6)? "Encontre 6" : "No encontre 6") << std::endl;
  std::cout << (bst->search(8)? "Encontre 8" : "No encontre 8") << std::endl;

  //std::cout << "Insertando 8" << std::endl;
  //bst->insert(11);

  std::cout << (bst->search(8)? "Encontre 8" : "No encontre 8") << std::endl;

  std::cout << "============= TEST HEIGHT, DEPTH, LEVEL ==================" << std::endl;
  std::cout << "Altura de la raiz: " << bst->getHeight() <<  std::endl;
  std::cout << "Profundidad de la raiz: " << bst->getDepth() <<  std::endl;
  std::cout << "Nivel de la raiz: " << bst->getLevel() <<  std::endl;

  std::cout << "Altura del elemento 10: " << bst->getHeight(ten) << std::endl;
  std::cout << "Profundidad del elemento 10: " << bst->getDepth(ten) << std::endl;
  std::cout << "Nivel del elemento 10: " << bst->getLevel(ten) << std::endl;

  std::cout << "=============== TEST BALANCE FACTOR ====================" << std::endl;
  std::cout << "Balance Factor, elemento 5: " << bst->getBalanceFactor(five)<< std::endl;
  std::cout << "Balance Factor, elemento 3: " << bst->getBalanceFactor(three)<< std::endl;
  std::cout << "Balance Factor, elemento 4: " << bst->getBalanceFactor(four)<< std::endl;
  std::cout << "Balance Factor, elemento 6: " << bst->getBalanceFactor(six)<< std::endl;
  std::cout << "Balance Factor, elemento 9: " << bst->getBalanceFactor(nine)<< std::endl;
  std::cout << "Balance Factor, elemento 10: " << bst->getBalanceFactor(ten)<< std::endl;

  std::cout << (bst->isAvl() ? "Es avl" : "No es avl")<< std::endl;
  bst->clear();


  std::cout << "\n \nArbol 2" << std::endl;

  BinarySearchTree<int> * bst2 = new BinarySearchTree<int>();
  BNode<int> * m_ten = new BNode<int>(10);
  BNode<int> * m_six = new BNode<int>(6);
  BNode<int> * m_four = new BNode<int>(4);
  BNode<int> * m_twelve = new BNode<int>(12);
  BNode<int> * m_eleven = new BNode<int>(11);
  BNode<int> * m_thirteen = new BNode<int>(13);

  bst2->insert(m_ten);
  bst2->insert(m_six);
  bst2->insert(m_four);
  bst2->insert(m_twelve);
  bst2->insert(m_thirteen);
  bst2->insert(m_eleven);

  std::cout << "Imprimiendo en orden ascendente" << std::endl;
  bst2->inOrder();

  std::cout << "Imprimiendo en orden descendente" << std::endl;
  bst2->inverseInOrder();


  std::cout << "=============== TEST BALANCE FACTOR ====================" << std::endl;
  std::cout << "Balance Factor, elemento 10: " << bst2->getBalanceFactor(m_ten)<< std::endl;
  std::cout << "Balance Factor, elemento 6: " << bst2->getBalanceFactor(m_six)<< std::endl;
  std::cout << "Balance Factor, elemento 4: " << bst2->getBalanceFactor(m_four)<< std::endl;
  std::cout << "Balance Factor, elemento 12: " << bst2->getBalanceFactor(m_twelve)<< std::endl;
  std::cout << "Balance Factor, elemento 13: " << bst2->getBalanceFactor(m_thirteen)<< std::endl;
  std::cout << "Balance Factor, elemento 11: " << bst2->getBalanceFactor(m_eleven)<< std::endl;

  std::cout << (bst2->isAvl() ? "Es avl" : "No es avl")<< std::endl;
  bst2->clear();

  return 0;
}
