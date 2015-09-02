
#include <iostream>
#include "sortingAlgorithms.h"

int getAlgorithmNumber();

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

// REQUIRES: None.
// MODIFIES: None.
// EFFECTS: Shows the user the algorithm options and returns the integer
// representing the selected algorithm.
int getAlgorithmNumber()
{
  std:: cout << "Select the algorithm type: " << std::endl;
  std:: cout << "1 BubbleSort" << std::endl;
  std:: cout << "2 CocktailSort" << std::endl;
  std:: cout << "3 InsertionSort" << std::endl;
  std:: cout << "4 BucketSort" << std::endl;
  std:: cout << "5 CountingSort" << std::endl;
  std:: cout << "6 MergeSort" << std::endl;
  std:: cout << "7 BinaryTreeSort" << std::endl;
  std:: cout << "8 RadixSort" << std::endl;
  std:: cout << "9 ShellSort" << std::endl;
  std:: cout << "10 SelectionSort" << std::endl;
  std:: cout << "11 HeapSort" << std::endl;
  std:: cout << "12 QuickSort" << std::endl;

  int n;
  std::cin >> n;
  return n;
}
