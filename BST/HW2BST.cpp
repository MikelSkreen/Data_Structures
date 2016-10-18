#include "HW2BST.h"

using namespace std;

HW2BST::Node::Node(int dataValue)
{
	Data = dataValue;
	Left = Right = NULL;
}

HW2BST::HW2BST(void)
{
	m_root = new Node(0);
	m_root = NULL;
}

HW2BST::~HW2BST(void)
{
	DeleteTree(m_root);
	m_root = NULL;
}

// Should return false if the value already exists in the tree or if memory 
// for a new node could not be allocated.
bool HW2BST::Add(int dataValue)
{
	Node* newNode = new Node(dataValue);
	Node *currentNode = m_root;
	bool success = false;
	int search = 1;


	if (IsEmpty() == 1) // Empty tree
	{
		m_root = newNode;
		return true;
	}

	while (currentNode != NULL) // Non-empty tree
	{
		if (dataValue > currentNode->Data)
		{
			if (currentNode->Right == NULL)
			{
				currentNode->Right = newNode;
				return true;
			}
			else
			{
				currentNode = currentNode->Right;
			}
		}
		else if (dataValue < currentNode->Data)
		{
			if (currentNode->Left == NULL)
			{
				currentNode->Left = newNode;
				return true;
			}
			else
			{
				currentNode = currentNode->Left;
			}
		}
		else if (dataValue == currentNode->Data)
		{
			cout << "Duplicate Nodes. Cannot add." << endl;
			return false;
		}
	}

	return success;
}

// Returns the number of levels in the tree. A tree with no contents (null root) will have 
// zero levels. A tree with just the root and no children has 1 level. For all other cases 
// the number of levels must be counted. There is a linear-time algorithm for this.


int HW2BST::CountLevels()
{
	int i = 0;

	if (!m_root)
		return i;

	queue<Node*> currentLevel, nextLevel;
	currentLevel.push(m_root);

	while (!currentLevel.empty())
	{
		Node *currNode = currentLevel.front();
		currentLevel.pop();
		if (currNode) {
			nextLevel.push(currNode->Left);
			nextLevel.push(currNode->Right);
		}
		if (currentLevel.empty()) {
			swap(currentLevel, nextLevel);
			i++;
		}
	}
	return i-1;
}

void HW2BST::DeleteTree(Node* root)
{
	if (root)
	{
		DeleteTree(root->Left);
		DeleteTree(root->Right);
		delete root;
	}
}

void HW2BST::DisplayContents(Node* node, ostream& outputStream)
{
	if (node)
	{
		DisplayContents(node->Left, outputStream);
		
		// Display the numerical value for this node
		outputStream << node->Data << " ";
		
		// Display the entire right subtree
		DisplayContents(node->Right, outputStream);
	}
}

void HW2BST::DisplayContents(ostream& outputStream)
{
	outputStream << "BST Contents: ";
	DisplayContents(m_root, outputStream);
	outputStream << endl;
}

void HW2BST::DisplayLevels(std::ostream& outputStream)
{
	if (!m_root) 
		return;

	queue<Node*> currentLevel, nextLevel;
	currentLevel.push(m_root);

	while (!currentLevel.empty()) 
	{
		Node *currNode = currentLevel.front();
		currentLevel.pop();
		if (currNode) {
			cout << currNode->Data << " ";
			nextLevel.push(currNode->Left);
			nextLevel.push(currNode->Right);
		}
		if (currentLevel.empty()) {
			cout << endl;
			swap(currentLevel, nextLevel);
		}
	}
}

// Gets the maximum value in the tree. Returns 0 if the tree is empty.
int HW2BST::GetMax()
{
	if (m_root)
	{
		Node* n = m_root;
		while (n->Right)
		{
			n = n->Right;
		}
		return n->Data;
	}
	return 0;
}

bool HW2BST::IsEmpty()
{
	return (NULL == m_root);
}

// Returns true if the value was found and removed, false if it was not found
bool HW2BST::Remove(int dataValue)
{
	// You must implement this function
	HW2BST::Node *previousNode = NULL;
	HW2BST::Node *removedNode = NULL;
	HW2BST::Node *curNode = m_root;

	int direction = 0;

	if (curNode->Data == dataValue) // root node
	{
		removedNode = curNode;
		previousNode = curNode;
		curNode = curNode->Right;
		direction = 2;

		while (curNode->Left != NULL)
		{
			previousNode = curNode;
			curNode = curNode->Left;
			direction = 1;
		}

		removedNode->Data = curNode->Data;

		if (direction == 1)
		{
			previousNode->Left = NULL;
			delete(curNode);
		}
		else if (direction == 2)
		{
			previousNode->Right = NULL;
			delete(curNode);
		}

		m_root = removedNode;

		return true;
	}
	else if (curNode->Data > dataValue)
	{
		previousNode = curNode;
		curNode = curNode->Left;
	}
	else
	{
		previousNode = curNode;
		curNode = curNode->Right;
	}

	while (curNode != NULL) //an item exists here
	{
		if (curNode->Data > dataValue)
		{
			previousNode = curNode;
			curNode = curNode->Left;
			direction = 1;
		}
		else if (curNode->Data < dataValue)
		{
			previousNode = curNode;
			curNode = curNode->Right;
			direction = 2;
		}
		else // found the item to delete
		{
			if (curNode->Left == NULL && curNode->Right == NULL) // leaf node
			{
				if (direction == 1)
				{
					previousNode->Left = NULL;
					delete(curNode);
				}
				else if (direction == 2)
				{
					previousNode->Right = NULL;
					delete(curNode);
				}
			}
			else if (curNode->Left != NULL && curNode->Right != NULL) // two branches
			{
				removedNode = curNode;
				previousNode = curNode;
				curNode = curNode->Right;
				direction = 2;

				while (curNode->Left != NULL)
				{
					previousNode = curNode;
					curNode = curNode->Left;
					direction = 1;
				}

				removedNode->Data = curNode->Data;

				if (direction == 1)
				{
					previousNode->Left = NULL;
					delete(curNode);
				}
				else if (direction == 2)
				{
					previousNode->Right = NULL;
					delete(curNode);
				}
			}
			else // one branch
			{
				if (curNode->Left != NULL)
				{
					previousNode->Left = curNode->Left;
					curNode->Left = NULL;
					delete(curNode);
				}
				if (curNode->Right != NULL)
				{
					previousNode->Right = curNode->Right;
					curNode->Right = NULL;
					delete(curNode);
				}
			}
			return true;
		}
	}

	cout << "Item was not deleted" << endl;

	return false; // node was not deleted properly

}

