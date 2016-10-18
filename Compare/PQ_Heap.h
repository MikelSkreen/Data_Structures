#ifndef PQHEAPH
#define PQHEAPH

#include <queue>
#include <iostream>

using std::vector;

template <typename T>
class PQ_Heap
{
private:
	vector<T> Heap;
	int K;

	void siftDown()
	{
		int cIndex = 0;
		int currentMax = 0; //variable used to check each parent and its children
		T temp;

		for (int pIndex = 0; cIndex < Heap.size(); pIndex = currentMax)
		{
			currentMax = pIndex;

			for (int curr = 1; curr <= K; curr++) // loop finds which children (if any) have the greatest value including the parents value
			{
				cIndex = childIndex(curr, pIndex);

				if (cIndex > Heap.size() - 1)
					return;

				if (Heap[cIndex] > Heap[currentMax])
				{
					currentMax = cIndex;
				}
			}

			if (Heap[currentMax] == Heap[pIndex])
				return;

			temp = Heap[currentMax]; // if we get to this point then we swap the parents value with the largest child and set the next parent value to the childs index
			Heap[currentMax] = Heap[pIndex];
			Heap[pIndex] = temp;
		}
	}

	void siftUp()
	{
		int cIndex = Heap.size() - 1;
		int pIndex = parentIndex(cIndex);

		while (pIndex != cIndex) // travels up the heap, switching values in wrong order
		{
			if (Heap[cIndex] > Heap[pIndex])
			{
				T temp = Heap[cIndex];
				Heap[cIndex] = Heap[pIndex];
				Heap[pIndex] = temp;
			}

			cIndex = pIndex;
			pIndex = parentIndex(cIndex);
		}
	}

	int childIndex(int child, int parent) // function returns the index of a child given the childs parent and which child you're looking for
	{
		return ((K*parent) + child);
	}

	int parentIndex(int cIndex) // function returns the index of the parent given the childs index
	{
		return ((cIndex - 1) / K);
	}


public:
	PQ_Heap(int k)
	{
		K = k;
	}

	void Add(const T& toCopyAndAdd)
	{
		T add = toCopyAndAdd; // to add an item I push it onto the back of the vector and sift up
		Heap.push_back(add);

		siftUp();
	}

	bool IsEmpty() const
	{
		if (Heap.size() == 0)
			return true;
		else
			return false;
	}

	bool RemoveMax(T& outputItem)
	{
		outputItem = Heap[0]; // to remove an item we set the top of the heap to outputItem and replace the top value with the last, pop the last value off and sift down
		Heap[0] = Heap[Heap.size()-1];
		Heap.pop_back();

		siftDown();

		if (Heap.size() >= 0)
			return true;
		else
			return false;
	}

	void Heapsort(T* arr)
	{
		int size = sizeof(arr)/sizeof(arr[0]);
		T temp;

		for (int i = 0; i != size; i++)
		{
			Add(arr[i]);
		}
		for (int i = 0; i < Heap.size(); i++) // perform the heap sort
		{
			bool success = RemoveMax(temp);
			arr[i] = temp;
			if (success == false)
			{
				std::cout << "HeapSort failed." << std::endl;
				return;
			}
		}
		std::cout << "HeapSort Complete\n";

	}
};
#endif