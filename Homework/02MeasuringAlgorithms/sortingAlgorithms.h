// TODO: BucketSort
// TODO: BinaryTreeSort
// TODO: RadixSort
// TODO: ShellSort

#include <iostream>

int getArraySize();
int getAlgorithmNumber();
void addNRandomElements(int array[], int n);
void printExecutionTime(int array[], int n, void (*f)(int *, int));
void bubbleSort(int v[] , int n);
void insertionSort(int v[], int n);
void selectionSort(int v[], int n);
void quickSort(int v[], int n);
void quickSort(int v[], int primero, int ultimo);
int partition(int v[], int lowerBound, int upperBound);
void mergeSort(int v[], int n);
void mergeSort(int v[], int l, int n, int N);
void merge(int v[], int l, int m, int n, int N);
void countingSort(int v[], int n);
int getMaxValue(int v[], int n);
void heapSort(int numbers[], int array_size);
void siftDown(int numbers[], int root, int bottom);


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
    for(int i = 0; i < n-1; i++)
    {
        int temp;
        int minimum = i;
        for(int j = i + 1; j < n; j++)
        {
            if (v[minimum] > v[j])
                minimum = j;
        }
        temp = v[minimum];
        v[minimum] = v[i];
        v[i] = temp;
    }
}

void quickSort(int v[], int n)
{
    quickSort(v, 0, n - 1);
}

void quickSort(int v[], int lowerBound, int upperBound)
{
  if (lowerBound < upperBound)
  {
    int p = partition(v, lowerBound, upperBound);
    quickSort(v, lowerBound, p - 1);
    quickSort(v, p + 1, upperBound);
  }
}

int partition(int v[], int lowerBound, int upperBound)
{
    int pivot = v[upperBound];
    int i = lowerBound;
    for (int j = lowerBound; j < upperBound; j++){
      if (v[j] <= pivot)
      {
        std::swap(v[i], v[j]);
        i++;
      }
    }
    std::swap(v[i], v[upperBound]);
    return i;
}

void mergeSort(int v[], int n)
{
  mergeSort(v, 0, n-1, n);
}

void mergeSort(int v[], int l, int n, int N)
{
    int m = (n+l)/2;
    if (n > l)
    {
        mergeSort (v, l, m, N);
        mergeSort (v, m+1, n, N);
        merge (v, l, m, n, N);
    }
}

void merge(int v[], int l, int m, int n, int N)
{
    int i, j, k;
    int aux[N];

    for(i = m+1; i>l; i--)
    {
        aux[i-1] = v[i-1];
    }

    for (j=m; j<n; j++)
    {
        aux[n+m-j] = v[j+1];
    }

    for(k=l;k<=n;k++)
    {
        if (aux[i] < aux[j])
        {
            v[k] = aux[i++];
        }
        else
        {
            v[k] = aux[j--];
        }
    }
}

// REQUIRES: None.
// MODIFIES: v[]
// EFFECTS: Sorts v[] using radixSort
void radixSort(int v[], int n, int d)
{

}

void countingSort(int v[], int n)
{
  int max = v[0];

  for (int i = 1; i < n; i++)
  {
    max = v[i] > max ? v[i] : max;
  }

  int * count = new int[max + 1];
  int * output = new int[n];

  for (int i = 0; i < n; i++)
  {
    count[v[i]]++;
  }

  for (int i = 1; i <= max; i++)
  {
    count[i] = count[i] + count[i -1];
  }

  for (int i = n - 1; i >= 0; i--)
  {
    output[--count[v[i]]] = v[i];
  }

  delete count;

  for (int i = 0; i < n; i++)
  {
    v[i] = output[i];
  }

  delete output;
}

void heapSort(int v[], int n)
{
	bool notSorted = true;

	while(notSorted)
	{
    notSorted = false;
	  for(int i = 0; i < n - 1; i++)
	  {
	    if( v[i] > v[i + 1] )
	    {
        std::swap(v[i], v[i+1]);
	      notSorted = true;
	    }
	  }

	  if(!notSorted) break;

    notSorted = false;

    for(int i = n - 1; i > 0; i-- )
    {
	    if( v[i - 1] > v[i] )
	    {
	      std::swap( v[i], v[i - 1] );
	      notSorted = true;
	    }
    }

	}
}


void siftDown(int numbers[], int root, int bottom)
{
  int done, maxChild, temp;

  done = 0;
  while ((root*2 <= bottom) && (!done))
  {
    if (root*2 == bottom)
      maxChild = root * 2;
    else if (numbers[root * 2] > numbers[root * 2 + 1])
      maxChild = root * 2;
    else
      maxChild = root * 2 + 1;

    if (numbers[root] < numbers[maxChild])
    {
      temp = numbers[root];
      numbers[root] = numbers[maxChild];
      numbers[maxChild] = temp;
      root = maxChild;
    }
    else
      done = 1;
  }
}

int getMaxValue(int v[], int n)
{
  int maxValue = v[0];
  for (int i = 1; i < n; i++)
  {
    if (v[i] > maxValue)
    {
      maxValue = v[i];
    }
  }
  return maxValue;
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
