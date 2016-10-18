#ifndef SHELL_SORT
#define SHELL_SORT

#include <iostream>

class Shell_Sort
{
public:
	Shell_Sort(void)
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
	}

	//Function uses instances of insertion sort
	void ShellSort(int* arr, int n, int* gapVals, int gapValsCount)
	{
		int i = gapValsCount, c = 0;

		while (i != 0)
		{
			InsertionSort(arr, n, 0, gapVals[c]);
			c++;
			i--;
		}
		std::cout << "ShellSort Completed\n";
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