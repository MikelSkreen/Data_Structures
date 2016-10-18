#include "Trie.h"

int main(int argc, char* argv[])
{
	Trie *trie = new Trie;

	if (argc < 3)
	{
		cout << "Missing required input file names\n";
		return -1;
	}

	string prefix;
	ifstream lines(argv[2]);
	ofstream output("output.txt");

	// populate trie
	int wordsLoaded = trie->buildTrie(argv[1]);

	output << "Mikel Skreen - 11390873" << endl;
	output << wordsLoaded - 1 << " words were added to the Trie\n" << endl;

	trie->AutoCompletePrefix("in1.txt", &output);

	output.close();
	lines.close();
}