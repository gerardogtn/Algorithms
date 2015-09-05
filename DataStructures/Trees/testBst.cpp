
#include <iostream>
#include "BinarySearchTree.h"

int main(int argc, const char * argv[])
{

  BinarySearchTree<int> * bst = new BinarySearchTree<int>();

  bst->insert(5);
  bst->insert(3);
  bst->insert(4);
  bst->insert(6);
  bst->insert(9);

  bst->inOrder();

  std::cout << (bst->search(5)? "Encontre 5" : "No encontre 5") << std::endl;
  std::cout << (bst->search(6)? "Encontre 6" : "No encontre 6") << std::endl;
  std::cout << (bst->search(8)? "Encontre 8" : "No encontre 8") << std::endl;

  return 0;
}
