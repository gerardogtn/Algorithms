#include <iostream>
#include "BTree.h"

int main(int argc, const char * argv[])
{
  BTree<int, 3> * tree = new BTree<int, 3>();
  Node<int, 3> * node = new Node<int, 3>();

  std::cout << (tree->search(3)? "Encontre tres" : "No encontre tres") << std::endl;



  delete node;
  delete tree;


  return 0;
}
