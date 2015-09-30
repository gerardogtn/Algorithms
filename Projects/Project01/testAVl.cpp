#include <iostream>
#include <chrono>

#include "../../DataStructures/Trees/AvlTree/AvlTree.h"

int main(int argc, char const *argv[]) {
  const int N = 100000;
  int testValues[N];
  int searchValues[10];
  srand((int) time(NULL));

  for (int i = 0; i < N; i++)
    testValues[i] = rand();

  for (int i = 0; i < 10; i++ )
    searchValues[i] = testValues[rand()%N];

    std::cout << "==================== Arbol AVL" << std::endl;
    AvlTree<int> * avl = new AvlTree<int>();

    std::cout << "++++++insertando: " << std::endl;
    auto avl_ib = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < N; i++)
      avl->insert(testValues[i]);
    auto avl_ie = std::chrono::high_resolution_clock::now();
    auto avl_i = std::chrono::duration_cast<std::chrono::microseconds>(avl_ie-avl_ib);
    std::cout << "Tiempo en microsegundos: " << avl_i.count() << std::endl;

    std::cout << "++++++buscando: " << std::endl;
    auto avl_sb = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 10; i++)
      avl->search(searchValues[i]);
    auto avl_se = std::chrono::high_resolution_clock::now();
    auto avl_s = std::chrono::duration_cast<std::chrono::microseconds>(avl_se-avl_sb);
    std::cout << "Tiempo en microsegundos: " << avl_s.count() << std::endl;
    return 0;
}
