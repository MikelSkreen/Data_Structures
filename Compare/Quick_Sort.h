#ifndef QUICK_SORT
#define QUICK_SORT

#include <iostream>

class Quick_Sort
{
private:
	void quickSorth(int arr[], int left, int right)
	{

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
	}

		if (left < r)
			quickSorth(arr, left, r);
		if (l < right)
			quickSorth(arr, l, right);
	}

public:
	Quick_Sort(void)
	{

	}

	void QuickSort(int* arr, int n)
	{
		quickSorth(arr, 0, n-1);
		std::cout << "QuickSort Complete\n";
	}

	static bool IsSorted(int* arr, int n)
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