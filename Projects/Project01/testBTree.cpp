#include <iostream>
#include <chrono>

#include "../../DataStructures/Trees/BTree/BTreeDisk.h"

int main(int argc, char const *argv[]) {
  const int N = 100000;
  int testValues[N];
  int searchValues[10];
  srand((int) time(NULL));

  for (int i = 0; i < N; i++)
    testValues[i] = rand();

  for (int i = 0; i < 10; i++ )
    searchValues[i] = testValues[rand()%N];

  BTreeDisk<int, 10> * rbt = new BTreeDisk<int, 10>();
  std::cout << "==================== Arbol B" << std::endl;

  std::cout << "++++++insertando: " << std::endl;
  auto rbt_ib = std::chrono::high_resolution_clock::now();
  for (int i = 0; i < N; i++)
    rbt->insert(testValues[i]);
  auto rbt_ie = std::chrono::high_resolution_clock::now();
  auto rbt_i = std::chrono::duration_cast<std::chrono::microseconds>(rbt_ie-rbt_ib);
  std::cout << "Tiempo en microsegundos: " << rbt_i.count() << std::endl;

  std::cout << "++++++buscando: " << std::endl;
  std::cout << "++++++buscando: " << std::endl;
  for (int i = 0; i < 10; i++)
  {
    auto rbt_sb = std::chrono::high_resolution_clock::now();
    rbt->search(searchValues[i]);
    auto rbt_se = std::chrono::high_resolution_clock::now();
    auto rbt_s = std::chrono::duration_cast<std::chrono::microseconds>(rbt_se-rbt_sb);
    std::cout << "Busqueda elemento " << i <<": " << rbt_s.count() << std::endl;
  }

}
