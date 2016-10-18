#include "Gradebook.h"

using namespace std;

Gradebook::Gradebook(void)
{
	for (int i = 0; i < 1069; i++)
	{
		hashTable[i] = NULL;
	}
}

void Gradebook::AddEntry(string& studentName, double grade)
{
	int encode = hash(studentName);
	int alreadyInserted = 0;

	//memset(hashTable, NULL, 1069);

	if (!hashTable[encode])
	{
		Node* insert = new Node(studentName, grade);
		hashTable[encode] = insert;
	}
	else if (hashTable[encode])
	{
		//if (hashTable[encode]->name == studentName)
			//printf("Student has already been input");
		while (hashTable[encode]->pDown != NULL)
		{
			if ((hashTable[encode]->name == studentName) && (hashTable[encode]->grade == grade)) // if student has already been input
			{
				printf("Student has already been inserted into hash/n");
				alreadyInserted = 1;
			}
			hashTable[encode] = hashTable[encode]->pDown;
		}
		if (alreadyInserted == 0)
		{
			Node* insert = new Node(studentName, grade);
			hashTable[encode]->pDown = insert;
		}
	}
	// Implement this function
	// You must add the student and grade to the hash table UNLESS 
	// a student with the specified name already exists in the table
}

int Gradebook::hash(string key)
{
	int sum = 0;
	for (int i = 0; i < key.size(); i++)
	{
		sum += 2* key[i];
	}
	sum = sum % 1069;

	return sum;
}

bool Gradebook::GetGrade(std::string& studentName, double& out_gradeIfFound)
{
	bool success = false;

	int lookup = hash(studentName);
	Node* temp = hashTable[lookup];

	if (temp->name == studentName)
	{
		success = true;
		out_gradeIfFound = temp->grade;
	}
	else
	{
		while (temp->pDown != NULL)
		{
			if (temp->name == studentName)
			{
				success = true;
				out_gradeIfFound = temp->grade;
			}
			temp = temp->pDown;
		}
		if (temp->name == studentName)
		{
			success = true;
			out_gradeIfFound = temp->grade;
		}
	}

	return success;
	// Implement
}