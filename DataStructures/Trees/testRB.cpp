#include <iostream>
#include "RedBlackTree.h"

int main(int argc, const char * argv[])
{
  RedBlackTree<int> * tree = new RedBlackTree<int>();

  RedBlackNode<int> * one = new RedBlackNode<int>(1);
  RedBlackNode<int> * five = new RedBlackNode<int>(5);
  RedBlackNode<int> * ten = new RedBlackNode<int>(10);
  RedBlackNode<int> * fifteen = new RedBlackNode<int>(15);
  RedBlackNode<int> * twenty = new RedBlackNode<int>(20);

  std::cout << *one << *five << *ten << *fifteen << *twenty << std::endl;

  std::cout << "UNO" << std::endl;
  tree->insert(five);
  tree->inOrder();

  std::cout << "DOS" << std::endl;
  tree->insert(one);
  tree->inOrder();

  std::cout << "TRES" << std::endl;
  tree->insert(ten);
  tree->inOrder();

  std::cout << "CUATRO" << std::endl;
  tree->insert(fifteen);
  tree->inOrder();

  std::cout << "CINCO" << std::endl;
  tree->insert(twenty);
  tree->inOrder();


  //delete tree;
}
