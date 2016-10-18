#include "ArraySorter.h"


ArraySorter::ArraySorter(void)
{
}

void ArraySorter::InsertionSort(int* arr, int n)
{
	InsertionSort(arr, n, 0, 1);
}

void ArraySorter::InsertionSort(int* arr, int n, int startIndex, int gap)
{
	for (int i = gap; i < n; i++)
	{
		int Tmp = arr[i];
		int j = i;
		while (j >= gap && Tmp < arr[j - gap])
		{
			arr[j] = arr[j - gap];
			j -= gap;
		}
		arr[j] = Tmp;
	}
}

// Checks to see if the array is in sorted order
bool ArraySorter::IsSorted(int* arr, int n)
{
	for (int i = 1; i < n; i++)
	{
		// If an item is less than the one before it, then we're not sorted
		if (arr[i] < arr[i - 1])
		{
			return false;
		}
	}

	return true;
}

//Function uses instances of insertion sort
void ArraySorter::ShellSort(int* arr, int n, int* gapVals, int gapValsCount)
{
	int i = gapValsCount, c = 0;

	while (i != 0)
	{
		InsertionSort(arr, n, 0, gapVals[c]);
		c++;
		i--;
	}
}
