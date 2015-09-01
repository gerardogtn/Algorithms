#include <iostream>
#include "sortingAlgorithms.h"

int main(int argc, const char * argv[])
{
  int n = getArraySize();
  int arrayToSort[n];
  int algorithm = getAlgorithmNumber();

  addNRandomElements(arrayToSort, n);

  void (*sortingAlgorithm)(int *, int) = nullptr;

  switch (algorithm) {
    case 1:
      sortingAlgorithm = bubbleSort;
      break;
    case 2:
      sortingAlgorithm = cocktailSort;
      break;
    case 3:
      sortingAlgorithm = insertionSort;
      break;
    case 4:
      break;
    case 5:
      sortingAlgorithm = countingSort;
      break;
    case 6:
      sortingAlgorithm = mergeSort;
      break;
    case 7:
      break;
    case 8:
      break;
    case 9:
      break;
    case 10:
      sortingAlgorithm = selectionSort;
      break;
    case 11:
      sortingAlgorithm = heapSort;
      break;
    case 12:
      sortingAlgorithm = quickSort;
    default:
      break;
  }

  if (sortingAlgorithm == nullptr)
  {
    std::cout << "Algorithm number not valid" << std::endl;
  }
  else {
    printExecutionTime(arrayToSort, n, sortingAlgorithm);
  }

  return 0;
}
