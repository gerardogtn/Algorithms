
#include <iostream>
#include "sortingAlgorithms.h"
void printArray(int array[], int n);

int main(int argc, const char * argv[])
{
  int n = getArraySize();
  int * arrayToSort = new int[n];
  addNRandomElements(arrayToSort, n);
  printArray(arrayToSort, n);
  binaryTreeSort(arrayToSort, n);
  std::cout  << std::endl;
  printArray(arrayToSort, n);
  delete arrayToSort;
  return 0;
}

void printArray(int array[], int n)
{
  for (int i = 0; i < n; i++)
  {
    if (i % 10 == 9)
    {
      std::cout << array[i] << "  " << std::endl;
    }
    else
    {
      std::cout << array[i] << "  ";
    }
  }
}
