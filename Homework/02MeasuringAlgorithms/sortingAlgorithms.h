// TODO: BucketSort
// TODO: BinaryTreeSort

#include <iostream>
#include <chrono>
#include "BinaryTree.h"

int getArraySize();
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
void cocktailSort(int v[], int n);
void radixSort(int v[], int n);
void countSort(int v[], int n, int exp);
int getMax(int v[], int n);


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

int getMax(int v[], int n)
{

    int max = v[0];

    for(int i=1; i<n; i++)
    {
        if(v[i]>max)
        {
            max = v[i];
        }
    }

    return max;
}

void countSort(int v[], int n, int exp)
{
    int output[n];
    int count[10] = {0};


    for(int i=0; i<n; i++)
    {
        count[(v[i]/exp)%10]++;
    }

    for(int i=1; i<10;i++)
    {
        count[i]+=count[i-1];
    }

    for (int i = n-1; i>=0; i--)
    {
        output[count[( v[i]/exp ) %10 ] -1] = v[i];
        count[(v[i]/exp)%10]--;
    }

    for(int i=0; i < n; i++)
    {
        v[i]=output[i];
    }
}

void radixSort(int v[], int n)
{
    int m = getMax(v, n);

    for(int exp = 1; m/exp>0; exp*=10)
    {
        countSort(v, n, exp);
    }
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
  int i, temp;

  for (i = (n / 2)-1; i >= 0; i--)
    siftDown(v, i, n);

  for (i = n - 1; i >= 1; i--)
  {
    temp = v[0];
    v[0] = v[i];
    v[i] = temp;
    siftDown(v, 0, i-1);
  }
}

void cocktailSort(int v[], int n)
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


void shellSort(int v[], int n)
{
    int temp;

    for(int gap = n/2; gap > 0; gap /= 2)
    {
        for(int i=gap; i<n; i++)
        {
            for(int j=i-gap; j>=0 && v[j]>v[j+gap]; j-=gap)
            {
                temp = v[j];
                v[j]= v[j+gap];
                v[j+gap] = temp;
            }
        }
    }
}

void binaryTreeSort(int v[], int n)
{
  vcn::BinaryTree<int> * tree = new vcn::BinaryTree<int>();

  for (int i = 0; i < n; i++)
  {
    tree->insertOrder(v[i]);
  }
  
  tree->toInOrderArray(v, n);
  delete tree;
}

void bucketSort(int v[], const int n)
{

    int m = 10001;
    int buckets[m];

    for(int i=0; i< m; ++i)
    {
        buckets[i]=0;
    }

    for (int i = 0; i < n; ++i)
    {
        ++buckets[v[i]];
    }

    for (int i =0, j = 0; j < m; ++j)
    {
        for (int k = buckets[j]; k > 0; --k)
        {
            v[i++] = j;
        }
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
