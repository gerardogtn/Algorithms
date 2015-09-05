
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

  std::cout << "Imprimiendo en orden ascendente" << std::endl;
  bst->inOrder();

  std::cout << "Imprimiendo en orden descendente" << std::endl;
  bst->inverseInOrder();

  std::cout << (bst->search(5)? "Encontre 5" : "No encontre 5") << std::endl;
  std::cout << (bst->search(6)? "Encontre 6" : "No encontre 6") << std::endl;
  std::cout << (bst->search(8)? "Encontre 8" : "No encontre 8") << std::endl;

  std::cout << "Altura del arbol: " << bst->getHeight() << std::endl;

  std::cout << "Altura del elemento 10: " << bst->getHeight(ten) << std::endl;
  std::cout << "Profundidad del elemento 10: " << bst->getDepth(ten) << std::endl;
  std::cout << "Nivel del elemento 10: " << bst->getLevel(ten) << std::endl;

  bst->clear();

  return 0;
}
