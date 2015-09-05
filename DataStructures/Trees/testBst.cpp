
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

  bst->clear();

  return 0;
}
