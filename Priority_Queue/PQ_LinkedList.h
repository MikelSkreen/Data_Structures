#ifndef PQLLH
#define PQLLH

#include "PQBase.h"



template <typename T>
class PQ_LinkedList : public PQBase < T >
{
private:

	struct Node // using nodes to create the linked list
	{
		Node(T data)
		{
			d = data;
			pNext = pPrev = NULL;
		}

		Node()
		{
			d = NULL;
			pNext = pPrev = NULL;
		}

		T d;
		Node *pNext;
		Node *pPrev;
	};

	Node *front;
	Node *back;

	void destroyList()
	{
		Node* temp = NULL;

		while (front != back)
		{
			temp = front;
			front = front->pNext;
			delete front;
		}
	}

public:

	PQ_LinkedList()
	{
		front = NULL;
		back = NULL;
	}

	~PQ_LinkedList()
	{
		//destroyList();
	}

	void Add(const T& toCopyAndAdd)
	{
	// function adds a value by checking its value with the current nodes
	// and inserting it into the doubly linked list.
	//
		Node *insert = new Node(toCopyAndAdd);
		Node *pCur = front;
		if (!front)
		{
			front = insert;
			back = insert;
			return;
		}
		else if (insert->d > front->d)
		{
			insert->pNext = front;
			front->pPrev = insert;
			front = insert;
			return;
		}
		else
		{
			while (pCur != back) //keep incrementing pCur until you reach the spot where insert needs to go
			{
				if (pCur->d >= insert->d)
				{
					pCur = pCur->pNext;
				}
				else if (pCur->d < insert->d) // if insert is greater than current node value then insert
				{
					insert->pNext = pCur;
					insert->pPrev = pCur->pPrev;
					pCur->pPrev->pNext = insert;
					pCur->pPrev = insert;
					return;
				}
			}
			if (insert->d < back->d) // next two conditionals check the last node
			{
				pCur->pNext = insert;
				insert->pPrev = pCur;
				back = insert;
			}
			else if (insert->d >= back->d)
			{
				insert->pNext = back;
				insert->pPrev = back->pPrev;
				back->pPrev->pNext = insert;
				back->pPrev = insert;
			}
		}
	}

	bool RemoveMax(T& outputItem)
	{
		Node* temp = front;
		front = temp->pNext;

		if (temp != NULL)
		{
			outputItem = temp->d;
			return true;
		}
		else { return false; }
	}

	bool IsEmpty() const
	{
		if (front == NULL) { return true; }
		else { return false; }
	}

};


#endif