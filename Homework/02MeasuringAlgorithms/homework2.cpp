
#include <iostream>
#include "sortingAlgorithms.h"

typedef void (*sortingAlgorithm)(int *, int);

int getAlgorithmNumber();
sortingAlgorithm getAlgorithm(int algorithm);


int main(int argc, const char * argv[])
{
  int n = getArraySize();
  int arrayToSort[n];

  std::string functionNames[12] = {"bubbleSort",
    "cocktailSort",
    "insertionSort",
    "bucketSort",
    "countingSort",
    "mergeSort",
    "binaryTreeSort",
    "radixSort",
    "shellSort",
    "selectionSort",
    "heapSort",
    "quickSort"};

  for (int i = 0; i < 12; i++)
  {
    addNRandomElements(arrayToSort, n);
    void (*sortingFunction)(int *, int) = nullptr;
    sortingFunction = getAlgorithm(i + 1);
    if (sortingFunction == nullptr)
    {
      std::cout << "Algorithm number not valid" << std::endl;
    }
    else {
      std:: cout << functionNames[i];
      printExecutionTime(arrayToSort, n, sortingFunction);
    }
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

sortingAlgorithm getAlgorithm(int algorithm)
{
  switch (algorithm) {
    case 1:
      return bubbleSort;
      break;
    case 2:
      return cocktailSort;
      break;
    case 3:
      return insertionSort;
      break;
    case 4:
      return bucketSort;
      break;
    case 5:
      return countingSort;
      break;
    case 6:
      return mergeSort;
      break;
    case 7:
      return binaryTreeSort;
      break;
    case 8:
      return radixSort;
      break;
    case 9:
      return shellSort;
      break;
    case 10:
      return selectionSort;
      break;
    case 11:
      return heapSort;
      break;
    case 12:
      return quickSort;
      break;
    default:
      return nullptr;
      break;
  }
  return nullptr;
}
