// TODO: InsertionSort
// TODO: BucketSort
// TODO: CountingSort
// TODO: MergeSort
// TODO: BinaryTreeSort
// TODO: RadixSort
// TODO: ShellSort
// TODO: HeapSort
// TODO: QuickSort

#include <iostream>

int getArraySize();
int getAlgorithmNumber();
void addNRandomElements(int array[], int n);
void printExecutionTime(int array[], int n, void (*f)(int *, int));
void bubbleSort(int v[] , int n);
void insertionSort(int v[], int n);
void selectionSort(int v[], int n);


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
    case 3:
      sortingAlgorithm = insertionSort;
      break;
    case 10:
      sortingAlgorithm = selectionSort;
      break;
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
// EFFECTS: Returns the int inputed by user.
int getArraySize()
{
  int n;
  std::cout << "Insert the number of elements: " << std::endl;
  std::cin >> n;
  return n;
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

// REQUIRES: None.
// MODIFIES: None.
// EFFECTS: After the user inputs an int, return a new n-sized array filled with
// random ints
void addNRandomElements(int array[], int n)
{
  srand((int)time(nullptr));
  for(int i = 0; i < n; i++)
  {
      array[i] = rand() % 100;
  }

}


// REQUIRES: n is the size of the array.
// MODIFIES: v[]
// EFFECTS: Use bubbleSort algorithm to sort v[]
void bubbleSort(int v[] , int n)
{
    int temp;

    for (int i = 0; i < n; i++)
    {
        for (int j = n-1; j > i; j--)
        {
            if (v[j-1] > v[j])
            {
                temp = v[j-1];
                v[j-1] = v[j];
                v[j] = temp;
            }
        }
    }
}

// REQUIRES: None.
// MODIFIES: v[]
// EFFECTS: Sorts v[] using InsertionSort algorithm.
void insertionSort(int v[], int n)
{
    int index;

    for (int i=1; i < n; i++)
    {
        index = v[i];

        int j = i-1;

        while (j >= 0 && v[j] > index)
        {
            v[j + 1] = v[j];
            j--;
        }

        v[j+1] = index;
    }
}

// REQUIRES: None.
// MODIFIES: v[]
// EFFECTS:  Sorts v[] using selectionSort
void selectionSort(int v[], int n)
{
    int minimo = 0;
    int temp;

    for(int i = 0; i < n-1; i++)
    {
        minimo = i;
        for(int j = i + 1; j < n; j++)
        {
            if (v[minimo] > v[j])
                minimo = j;
        }
        temp = v[minimo];
        v[minimo] = v[i];
        v[i] = temp;
    }
}
// REQUIRES: None.
// MODIFIES: None.
// EFFECTS: Displays the time before and after executing a function.
void printExecutionTime(int array[], int n, void (*f)(int *, int))
{
  auto start_time = std::chrono::high_resolution_clock::now();
  (*f)(array, n);
  auto end_time = std::chrono::high_resolution_clock::now();

  auto timeToExecute = end_time - start_time;

  std::cout << "The execution time in microseconds was: " << std::endl;
  std::cout << std::chrono::duration_cast<std::chrono::microseconds>(timeToExecute).count() << std::endl;
}
