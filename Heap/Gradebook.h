#ifndef GRADEBOOK223_H
#define GRADEBOOK223_H

#include <string>
#include <unordered_map>
#include <vector>

using std::string;

// As usual, add private helper functions in this class if you need to
class Gradebook
{
private:
	struct Node
	{
		string name;
		double grade;
		Node *pDown;

		Node(string n, double g)
		{
			name = n;
			grade = g;
			pDown = NULL;
		}
	};
	Node *hashTable[1069];

	int hash(string str);

public:
	Gradebook(void);

	void AddEntry(std::string& studentName, double grade);
	bool GetGrade(std::string& studentName, double& out_gradeIfFound);
};

#endif