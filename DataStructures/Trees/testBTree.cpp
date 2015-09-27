#include <iostream>
#include "BTree.h"

// This function tests the example at Kruse's textbook.
// Makes a BTree of order 5 representation of the English alphabet.
int main(int argc, const char * argv[])
{
  BTree<char, 5> * tree = new BTree<char, 5>();
  std::cout << "====================== DECLARANDO ARBOL \n" << std::endl;
  tree->printTree();

  std::cout << "====================== INSERTANDO 4 ELEMENTOS" << std::endl;
  tree->insert('a');
  tree->insert('g');
  tree->insert('f');
  tree->insert('b');
  std::cout << "A, B, F, G: insertados \n" << std::endl;
  tree->printTree();

  std::cout << "====================== BUSCANDO ELEMENTOS" << std::endl;
  std::cout << (tree->search('a')? "Encontre A": "No encontre A") << std::endl;
  std::cout << (tree->search('b')? "Encontre B": "No encontre B") << std::endl;
  std::cout << (tree->search('c')? "Encontre C": "No encontre C") << std::endl;
  std::cout << (tree->search('d')? "Encontre D": "No encontre D") << std::endl;
  std::cout << (tree->search('e')? "Encontre E": "No encontre E") << std::endl;
  std::cout << (tree->search('f')? "Encontre F": "No encontre F") << std::endl;
  std::cout << (tree->search('g')? "Encontre G": "No encontre G") << std::endl;
  std::cout << (tree->search('h')? "Encontre H": "No encontre H") << std::endl;
  std::cout << (tree->search('i')? "Encontre I": "No encontre I") << std::endl;
  std::cout << (tree->search('j')? "Encontre J": "No encontre J") << std::endl;
  std::cout << (tree->search('k')? "Encontre K": "No encontre K") << std::endl;
  std::cout << (tree->search('l')? "Encontre L": "No encontre L") << std::endl;
  std::cout << (tree->search('m')? "Encontre M": "No encontre M") << std::endl;

  std::cout << "====================== INSERTANDO ELEMENTO EXTRA" << std::endl;
  tree->insert('k');
  tree->insert('d');
  tree->insert('h');
  tree->insert('m');
  tree->insert('j');
  std::cout << "K D H M J: insertada \n" << std::endl;
  tree->printTree();

  std::cout << "====================== BUSCANDO ELEMENTOS" << std::endl;
  std::cout << (tree->search('a')? "Encontre A": "No encontre A") << std::endl;
  std::cout << (tree->search('b')? "Encontre B": "No encontre B") << std::endl;
  std::cout << (tree->search('c')? "Encontre C": "No encontre C") << std::endl;
  std::cout << (tree->search('d')? "Encontre D": "No encontre D") << std::endl;
  std::cout << (tree->search('e')? "Encontre E": "No encontre E") << std::endl;
  std::cout << (tree->search('f')? "Encontre F": "No encontre F") << std::endl;
  std::cout << (tree->search('g')? "Encontre G": "No encontre G") << std::endl;
  std::cout << (tree->search('h')? "Encontre H": "No encontre H") << std::endl;
  std::cout << (tree->search('i')? "Encontre I": "No encontre I") << std::endl;
  std::cout << (tree->search('j')? "Encontre J": "No encontre J") << std::endl;
  std::cout << (tree->search('k')? "Encontre K": "No encontre K") << std::endl;
  std::cout << (tree->search('l')? "Encontre L": "No encontre L") << std::endl;
  std::cout << (tree->search('m')? "Encontre M": "No encontre M") << std::endl;

  std::cout << "====================== ELIMINANDO ELEMENTO EXTRA" << std::endl;
  tree->remove('k');
  tree->remove('d');
  tree->remove('h');
  tree->remove('m');
  tree->remove('j');
  std::cout << "K D H M J: borradas \n" << std::endl;
  tree->printTree();

  std::cout << "====================== BUSCANDO ELEMENTOS" << std::endl;
  std::cout << (tree->search('a')? "Encontre A": "No encontre A") << std::endl;
  std::cout << (tree->search('b')? "Encontre B": "No encontre B") << std::endl;
  std::cout << (tree->search('c')? "Encontre C": "No encontre C") << std::endl;
  std::cout << (tree->search('d')? "Encontre D": "No encontre D") << std::endl;
  std::cout << (tree->search('e')? "Encontre E": "No encontre E") << std::endl;
  std::cout << (tree->search('f')? "Encontre F": "No encontre F") << std::endl;
  std::cout << (tree->search('g')? "Encontre G": "No encontre G") << std::endl;
  std::cout << (tree->search('h')? "Encontre H": "No encontre H") << std::endl;
  std::cout << (tree->search('i')? "Encontre I": "No encontre I") << std::endl;
  std::cout << (tree->search('j')? "Encontre J": "No encontre J") << std::endl;
  std::cout << (tree->search('k')? "Encontre K": "No encontre K") << std::endl;
  std::cout << (tree->search('l')? "Encontre L": "No encontre L") << std::endl;
  std::cout << (tree->search('m')? "Encontre M": "No encontre M") << std::endl;


  delete tree;

  return 0;
}
