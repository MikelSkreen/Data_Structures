#ifndef INSERTION_SORT
#define INSERTION_SORT

#include <iostream>

class Insertion_Sort
{
public:
	Insertion_Sort(void)
	{

	}

	void InsertionSort(int* arr, int n, int startIndex, int gap)
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
		std::cout << "InsertionSort Complete\n";
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

	void Swap(int& a, int &b)
	{
		int temp = a;
		a = b;
		b = temp;
	}
};

#endif