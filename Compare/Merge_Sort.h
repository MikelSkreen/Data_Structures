#ifndef MERGE_SORT
#define MERGE_SORT

#include <iostream>

class Merge_Sort
{
private:
	void merge_sort(int iArray[], int startIndex, int endIndex)
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

	void merge(int a[], int startIndex, int endIndex)
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

public:
	Merge_Sort(void)
	{

	}

	// Checks to see if the array is in sorted order
	bool IsSorted(int* arr, int n)
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
	
	void MergeSort(int* arr, int n)
	{
		merge_sort(arr, 0, n-1);
		std::cout << "MergeSort Complete\n";
	}

	void Swap(int& a, int &b)
	{
		int temp = a;
		a = b;
		b = temp;
	}
};

#endif