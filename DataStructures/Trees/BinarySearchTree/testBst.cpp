
#include <iostream>
#include "BinarySearchTree.h"

int main(int argc, const char * argv[])
{
  BinarySearchTree<int> * tree = new BinarySearchTree<int>();

  std::cout << "====================== DECLARANDO ARBOL \n" << std::endl;
  tree->printAscending();

  std::cout << "====================== INSERTANDO 9 ELEMENTOS" << std::endl;
  tree->insert(10);
  tree->insert(7);
  tree->insert(15);
  tree->insert(1);
  tree->insert(3);
  tree->insert(21);
  tree->insert(19);
  tree->insert(8);
  tree->insert(13);


  std::cout << "10, 7, 15, 1, 3, 21, 19, 8, 13: insertados \n" << std::endl;
  tree->printAscending();

  std::cout << "====================== BUSCANDO ELEMENTOS" << std::endl;
  std::cout << (tree->search(1)? "Encontre 1": "No encontre 1") << std::endl;
  std::cout << (tree->search(2)? "Encontre 2": "No encontre 2") << std::endl;
  std::cout << (tree->search(3)? "Encontre 3": "No encontre 3") << std::endl;
  std::cout << (tree->search(4)? "Encontre 4": "No encontre 4") << std::endl;
  std::cout << (tree->search(5)? "Encontre 5": "No encontre 5") << std::endl;
  std::cout << (tree->search(6)? "Encontre 6": "No encontre 6") << std::endl;
  std::cout << (tree->search(7)? "Encontre 7": "No encontre 7") << std::endl;
  std::cout << (tree->search(8)? "Encontre 8": "No encontre 8") << std::endl;
  std::cout << (tree->search(9)? "Encontre 9": "No encontre 9") << std::endl;
  std::cout << (tree->search(10)? "Encontre 10": "No encontre 10") << std::endl;
  std::cout << (tree->search(11)? "Encontre 11": "No encontre 11") << std::endl;
  std::cout << (tree->search(12)? "Encontre 12": "No encontre 12") << std::endl;
  std::cout << (tree->search(13)? "Encontre 13": "No encontre 13") << std::endl;


  std::cout << "====================== ELIMINANDO ELEMENTOS" << std::endl;
  tree->remove(3);
  tree->remove(10);
  tree->remove(15);
  tree->remove(19);
  tree->remove(100);
  std::cout << "3 10 15 19 100: borradas \n" << std::endl;
  tree->printAscending();

  std::cout << "====================== BUSCANDO ELEMENTOS" << std::endl;
  std::cout << (tree->search(1)? "Encontre 1": "No encontre 1") << std::endl;
  std::cout << (tree->search(2)? "Encontre 2": "No encontre 2") << std::endl;
  std::cout << (tree->search(3)? "Encontre 3": "No encontre 3") << std::endl;
  std::cout << (tree->search(4)? "Encontre 4": "No encontre 4") << std::endl;
  std::cout << (tree->search(5)? "Encontre 5": "No encontre 5") << std::endl;
  std::cout << (tree->search(6)? "Encontre 6": "No encontre 6") << std::endl;
  std::cout << (tree->search(7)? "Encontre 7": "No encontre 7") << std::endl;
  std::cout << (tree->search(8)? "Encontre 8": "No encontre 8") << std::endl;
  std::cout << (tree->search(9)? "Encontre 9": "No encontre 9") << std::endl;
  std::cout << (tree->search(10)? "Encontre 10": "No encontre 10") << std::endl;
  std::cout << (tree->search(11)? "Encontre 11": "No encontre 11") << std::endl;
  std::cout << (tree->search(12)? "Encontre 12": "No encontre 12") << std::endl;
  std::cout << (tree->search(13)? "Encontre 13": "No encontre 13") << std::endl;

  std::cout << (tree->isBST()? "Si es BST" : "NO es BST") << std::endl;

  delete tree;
}
