#include <iostream>
#include "BTree.h"

// This function tests the example at Kruse's textbook.
// Makes a BTree of order 5 representation of the English alphabet.
int main(int argc, const char * argv[])
{
  BTree<char, 3> * tree = new BTree<char, 3>();

  char a = 'a';
  char b = 'b';
  char c = 'c';
  char d = 'd';
  char e = 'e';
  char f = 'f';
  char g = 'g';
  char h = 'h';
  char i = 'i';
  char j = 'j';
  char k = 'k';
  char l = 'l';
  char m = 'm';
  char n = 'n';
  char o = 'o';
  std::cout << "====================== DECLARANDO ARBOL \n" << std::endl;
  tree->printAscending();
  tree->printDescending();

  std::cout << "====================== INSERTANDO 4 ELEMENTOS" << std::endl;
  tree->insert(a);
  tree->insert(g);
  tree->insert(f);
  tree->insert(b);
  std::cout << "A, B, F, G: insertados \n" << std::endl;
  tree->printAscending();
  tree->printDescending();

  std::cout << "====================== BUSCANDO ELEMENTOS" << std::endl;
  std::cout << (tree->search(a)? "Encontre A": "No encontre A") << std::endl;
  std::cout << (tree->search(b)? "Encontre B": "No encontre B") << std::endl;
  std::cout << (tree->search(c)? "Encontre C": "No encontre C") << std::endl;
  std::cout << (tree->search(d)? "Encontre D": "No encontre D") << std::endl;
  std::cout << (tree->search(e)? "Encontre E": "No encontre E") << std::endl;
  std::cout << (tree->search(f)? "Encontre F": "No encontre F") << std::endl;
  std::cout << (tree->search(g)? "Encontre G": "No encontre G") << std::endl;
  std::cout << (tree->search(h)? "Encontre H": "No encontre H") << std::endl;
  std::cout << (tree->search(i)? "Encontre I": "No encontre I") << std::endl;
  std::cout << (tree->search(j)? "Encontre J": "No encontre J") << std::endl;
  std::cout << (tree->search(k)? "Encontre K": "No encontre K") << std::endl;
  std::cout << (tree->search(l)? "Encontre L": "No encontre L") << std::endl;
  std::cout << (tree->search(m)? "Encontre M": "No encontre M") << std::endl;
  std::cout << (tree->search(n)? "Encontre N": "No encontre N") << std::endl;
  std::cout << (tree->search(o)? "Encontre O": "No encontre O") << std::endl;

  std::cout << "====================== INSERTANDO ELEMENTO EXTRA" << std::endl;
  tree->insert(k);
  tree->insert(d);
  tree->insert(h);
  tree->insert(m);
  tree->insert(j);
  tree->insert(b);
  tree->insert(c);
  tree->insert(l);
  tree->insert(n);
  tree->insert(o);
  tree->insert(e);
  tree->insert(i);
  std::cout << "K D H M J: insertada \n" << std::endl;
  tree->printAscending();
  tree->printDescending();

  std::cout << "====================== BUSCANDO ELEMENTOS" << std::endl;
  std::cout << (tree->search(a)? "Encontre A": "No encontre A") << std::endl;
  std::cout << (tree->search(b)? "Encontre B": "No encontre B") << std::endl;
  std::cout << (tree->search(c)? "Encontre C": "No encontre C") << std::endl;
  std::cout << (tree->search(d)? "Encontre D": "No encontre D") << std::endl;
  std::cout << (tree->search(e)? "Encontre E": "No encontre E") << std::endl;
  std::cout << (tree->search(f)? "Encontre F": "No encontre F") << std::endl;
  std::cout << (tree->search(g)? "Encontre G": "No encontre G") << std::endl;
  std::cout << (tree->search(h)? "Encontre H": "No encontre H") << std::endl;
  std::cout << (tree->search(i)? "Encontre I": "No encontre I") << std::endl;
  std::cout << (tree->search(j)? "Encontre J": "No encontre J") << std::endl;
  std::cout << (tree->search(k)? "Encontre K": "No encontre K") << std::endl;
  std::cout << (tree->search(l)? "Encontre L": "No encontre L") << std::endl;
  std::cout << (tree->search(m)? "Encontre M": "No encontre M") << std::endl;
  std::cout << (tree->search(n)? "Encontre N": "No encontre N") << std::endl;
  std::cout << (tree->search(o)? "Encontre O": "No encontre O") << std::endl;

  std::cout << "====================== ELIMINANDO ELEMENTO EXTRA" << std::endl;
  tree->remove(k);
  tree->remove(d);
  tree->remove(h);
  tree->remove(m);
  tree->remove(j);
  std::cout << "K D H M J: borradas \n" << std::endl;
  tree->printAscending();
  tree->printDescending();

  std::cout << "====================== BUSCANDO ELEMENTOS" << std::endl;
  std::cout << (tree->search(a)? "Encontre A": "No encontre A") << std::endl;
  std::cout << (tree->search(b)? "Encontre B": "No encontre B") << std::endl;
  std::cout << (tree->search(c)? "Encontre C": "No encontre C") << std::endl;
  std::cout << (tree->search(d)? "Encontre D": "No encontre D") << std::endl;
  std::cout << (tree->search(e)? "Encontre E": "No encontre E") << std::endl;
  std::cout << (tree->search(f)? "Encontre F": "No encontre F") << std::endl;
  std::cout << (tree->search(g)? "Encontre G": "No encontre G") << std::endl;
  std::cout << (tree->search(h)? "Encontre H": "No encontre H") << std::endl;
  std::cout << (tree->search(i)? "Encontre I": "No encontre I") << std::endl;
  std::cout << (tree->search(j)? "Encontre J": "No encontre J") << std::endl;
  std::cout << (tree->search(k)? "Encontre K": "No encontre K") << std::endl;
  std::cout << (tree->search(l)? "Encontre L": "No encontre L") << std::endl;
  std::cout << (tree->search(m)? "Encontre M": "No encontre M") << std::endl;
  std::cout << (tree->search(n)? "Encontre N": "No encontre N") << std::endl;
  std::cout << (tree->search(o)? "Encontre O": "No encontre O") << std::endl;


  //delete tree;

  return 0;
}
