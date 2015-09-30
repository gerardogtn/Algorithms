#include <iostream>
#include <iterator>
#include <cstring>
#include <chrono>
#include "RedBlack.h"

int main()
{
  RedBlack<int> * RB = new RedBlack<int>();
  srand((int) time(NULL));

    int numeros[100000];
    int busqueda[10];

    for(int i=0;i<100000;i++)
    {
        numeros[i] = rand()%100000;
    }

    for(int i=0; i<100000;i++)
    {
        RB->RBinsert(numeros[i]);
    }
    for(int i=0;i<10;i++)
    {
        busqueda[i] = numeros[i];
    }


    auto begin = std::chrono::high_resolution_clock::now();
    for(int i = 0; i < 10; i++)
    {
        if (RB->buscar(busqueda[i]))
        {
            std::cout << "El valor: " << busqueda[i] << " se encuentra en el árbol" << std::endl;
        }
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto tiempo = std::chrono::duration_cast<std::chrono::microseconds>(end-begin);
    std::cout<<"Árbol RojiNegro: "<<tiempo.count()<<" micro segundos"<<std::endl;

  return 0;
}
