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

void ArraySorter::MergeSort(int* arr, int n)
{
	merge_sort(arr, 0, n-1);
}

void ArraySorter::merge_sort(int iArray[], int startIndex, int endIndex)
{
	int midIndex;

	//Check for base case
	if (startIndex >= endIndex)
	{
		return;
	}

	//First, divide in half
	midIndex = (startIndex + endIndex) / 2;

	//First recursive call 
	merge_sort(iArray, startIndex, midIndex);

	//Second recursive call 
	merge_sort(iArray, midIndex + 1, endIndex);

	//The merge function
	merge(iArray, startIndex, endIndex);

}

void ArraySorter::merge(int a[], int startIndex, int endIndex)
{

	int size = (endIndex - startIndex) + 1;
	int *b = new int[size]();

	int i = startIndex;
	int mid = (startIndex + endIndex) / 2;
	int k = 0;
	int j = mid + 1;


	while (i <= mid && j <= endIndex)
	{
		b[k++] = (a[i] < a[j]) ? a[i++] : a[j++];
	}

	while (i <= mid)
	{
		b[k++] = a[i++];
	}
	while (j <= endIndex)
	{
		b[k++] = a[j++];
	}

	for (k = 0; k < size; k++)
	{
		a[startIndex + k] = b[k];
	}

	delete[]b;

}

void ArraySorter::quickSorth(int arr[], int left, int right) {

	int l = left;
	int r = right;
	int tmp;
	int pivot = arr[(left + right) / 2];

	while (l <= r) 
	{
		while (arr[l] < pivot)
		{
			l++;
		}

		while (arr[r] > pivot)
		{
			r--;
		}

		if (l <= r) 
		{
			tmp = arr[l];
			arr[l] = arr[r];
			arr[r] = tmp;
			l++;
			r--;
		}
	};

	if (left < r)
		quickSorth(arr, left, r);
	if (l < right)
		quickSorth(arr, l, right);
}

void ArraySorter::QuickSort(int* arr, int n)
{
	quickSorth(arr, 0, n-1);
}

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
