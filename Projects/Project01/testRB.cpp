#include <iostream>
#include <chrono>

#include "../../DataStructures/Trees/rojinegro/RedBlack/RedBlack.h"

int main(int argc, char const *argv[]) {
  const int N = 100000;
  int testValues[N];
  int searchValues[10];
  srand((int) time(NULL));

  for (int i = 0; i < N; i++)
    testValues[i] = rand();

  for (int i = 0; i < 10; i++ )
    searchValues[i] = testValues[rand()%N];

  RedBlack<int> * rbt = new RedBlack<int>();
  std::cout << "==================== Arbol rojinegro" << std::endl;

  std::cout << "++++++insertando: " << std::endl;
  auto rbt_ib = std::chrono::high_resolution_clock::now();
  for (int i = 0; i < N; i++)
    rbt->RBinsert(testValues[i]);
  auto rbt_ie = std::chrono::high_resolution_clock::now();
  auto rbt_i = std::chrono::duration_cast<std::chrono::microseconds>(rbt_ie-rbt_ib);
  std::cout << "Tiempo en microsegundos: " << rbt_i.count() << std::endl;

  std::cout << "++++++buscando: " << std::endl;
  auto rbt_sb = std::chrono::high_resolution_clock::now();
  for (int i = 0; i < 10; i++)
    rbt->buscar(searchValues[i]);
  auto rbt_se = std::chrono::high_resolution_clock::now();
  auto rbt_s = std::chrono::duration_cast<std::chrono::microseconds>(rbt_se-rbt_sb);
  std::cout << "Tiempo en microsegundos: " << rbt_s.count() << std::endl;

}
