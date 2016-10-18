#include <iostream>
#include <fstream>
#include <string>
#include <locale> 

#include <chrono>
#include <map>
#include <set>

#define AlphabetSize 26

using::std::string;
using::std::cout;
using::std::endl;
using::std::ifstream;
using::std::ofstream;
using::std::getline;


class Trie
{
private:
	struct Trie_Node
	{
		char data;
		int prefix_count;
		bool end;
		Trie_Node *children[AlphabetSize];

		Trie_Node() // Node constructor
		{
			data = '\0';
			prefix_count = 0;
			end = false;

			for (int i = 0; i < AlphabetSize; i++)
			{
				this->children[i] = NULL;
			}
		}
	};
	Trie_Node *root;


public:
	Trie()
	{
		root = new Trie_Node;
	}

	~Trie()
	{
		// destructor
	}


	void Insert(string add)
	{
		Trie_Node *temp = root;
		int length = add.length();
		temp->prefix_count++;

		for (unsigned int i = 0; i < add.length(); ++i)
		{
			int letter = (int)add[i] - (int)'a';
			if (!temp->children[letter])
			{
				Trie_Node *newNode = new Trie_Node();
				newNode->data = add[i];
				temp->children[letter] = newNode;
			}
			temp->children[letter]->prefix_count;
			temp = temp->children[letter];
		}
		temp->end = true;
	}

	bool isWord(string word) const 
	{
		Trie_Node *Cur = root;
		for (unsigned int i = 0; i < word.length(); ++i)
		{
			if (Cur->children[((int)word[i] - (int)'a')] == NULL)
				return false;
			Cur = Cur->children[((int)word[i] - (int)'a')];
		}

		return Cur->end;
	}

	int WordsWithPrefix(string pref) const 
	{
		Trie_Node *Cur = root;
		for (unsigned int i = 0; i < pref.length(); ++i)
		{
			if (Cur->children[((int)pref[i] - (int)'a')] == NULL)
				return 0;
			else
				Cur = Cur->children[((int)pref[i] - (int)'a')];
		}
		return Cur->prefix_count;
	}

	int buildTrie(string fname) 
	{
		ifstream dictionary(fname);
		string curWord;
		int i = 0;

		if (!dictionary.is_open())
		{
			cout << "ERROR: Could not open file " << fname << endl;
			return 0;
		}

		while (dictionary) 
		{
			i++;
			getline(dictionary, curWord);
			this->Insert(curWord);
		}
		dictionary.close();

		return i;
	}

	void AutoCompletePrefix(string fname, ofstream *output)
	{
		ifstream lines(fname);
		string curPrefix;
		string temp;

		if (!lines.is_open())
		{
			cout << "ERROR: Could not open file " << fname << endl;
			return;
		}

		Trie_Node *cur = root;

		while (getline(lines, curPrefix))
		{
			int index = 0;
			cur = root;

			for (int i = 0; i < curPrefix.size(); i++)
			{
				cur = cur->children[(int)curPrefix[i] - (int)'a'];
			}

			curPrefix.pop_back();

			wordBuild(cur, curPrefix, temp, output);
		}
	}

	void wordBuild(Trie_Node *cur,string prefix, string suffix, ofstream *output)
	{
		suffix += cur->data;

		if (cur->end)
		{
			*output << prefix << suffix << endl;
		}

		for (int i = 0; i < AlphabetSize; i++)
		{
			if (cur->children[i])
			{
				wordBuild(cur->children[i], prefix, suffix, output);
			}
		}
	}
};