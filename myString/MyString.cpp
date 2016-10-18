// Cpt S 223 Homework Assignment - MyString class
// Mikel Skreen

#include "MyString.h"

using namespace std;

MyString::MyString()
{
    // Make an empty string. Note that this is different from a NULL string.
	m_str = new char[1];
	m_str[0] = 0;
}

MyString::MyString(const MyString& copyme)
{
	int i = 0;
	this->m_str = new char[copyme.Length()+1];

	while (i < Length(copyme.m_str))
	{
		m_str[i] = copyme.m_str[i];
		i++;
	}

	m_str[i] = '\0';
	
}

MyString::MyString(const char* str)
{
    // Special case for a null string
	if (!str)
	{
		m_str = new char[1];
		m_str[0] = 0;
		return;
	}
	
	int len = Length(str);    
    m_str = new char[len + 1];
    Copy(m_str, str, len + 1);
}

// This is a private constructor that assumes both parameters are valid, 
// thus there isn't any error checking done on these parameters.
MyString::MyString(const char* str, int charCount)
{
	m_str = new char[charCount + 1];
	Copy(m_str, str, charCount);
	m_str[charCount] = 0;
}

MyString::~MyString()
{
    if (m_str)
	{
		delete [] m_str;
		m_str = NULL;
	}
#if defined(DEBUG) || defined(_DEBUG)
	else
	{
		std::cout << "DEBUG: WARNING, destructor called when m_str is NULL!" << std::endl;
	}
#endif
}

// Compares the desired number of characters in two strings and returns true if
// they are all equal. If the null-terminator on either string is encountered
// before the desired number of characters have been compared, then false
// will be returned.
bool MyString::AreEqual(const char* str1, const char* str2, int numCharsToCompare)
{
    while (numCharsToCompare--)
    {
        if (!str1[0])
        {
            return (0 == str2[0] && 0 == numCharsToCompare);
        }
        
        if (str1[0] != str2[0])
        {
            return false;
        }
        
        str1++;
        str2++;
    }
    
    // Coming here means we compared the desired number of characters
    // and didn't encounter a mismatch, so we return true.
    return true;
}

// Copies the specified number of characters from the source to destination. 
// No null terminators are used for anything. The specified number of characters 
// will be copied exactly and this could potentially go past a null terminator.
void MyString::Copy(char* destination, const char* source, int count)
{
	while (count--)
	{
		*destination++ = *source++;
	}
}

int MyString::GetAnagrams(vector<MyString>& candidates, vector<MyString>& output)
{
	int *table1;
	int *table2;
	int i = 0, j = 0;
	int isAnagram = 0;

	table1 = BuildFreqTable(this->m_str);

	while (i < candidates.size())
	{
		table2 = BuildFreqTable(candidates[i].m_str);

		while (table1[j] == table2[j])
		{
			j++;
		}
		if (j >= 256)
		{
			output.push_back(candidates[i]);
		}
		j = 0;

		i++;
	}

	return 1;
}

int * MyString::BuildFreqTable(const char*s)
{
	int i;
	int* table = new int[256];
	for (int i = 0; i<256; i++)
		table[i] = 0;

	while (*s)
	{
		table[*s]++;
		s++;
	}

	return table;
}


int MyString::IndexOf(char c, int startIndex) const
{
	int i = startIndex;

	while (m_str)
	{
		if (m_str[i] == c)
			return i;
		i++;
	}
    // Implement this function
	// Start the search for the character at the specified index
	// Return the index of the character if it is found, -1 if it isn't
	return -1;
}

int MyString::getGreatestIndex(char c, const char* str)
{
	for (int i = Length(str) - 1; i >= 0; i--)
	{
		if (str[i] == c)
		{
			return i;
		}
	}
	return -1;
}

void MyString::populateCharArr(const char* set, int* newStr)
{
	for (int i = 0; i< Length(newStr); i++)
	{
		newStr[i] = -1;
	}
	for (int i = 0; i< Length(set); i++)
	{
		newStr[set[i]] = getGreatestIndex(set[i], set);
	}
}

// Implement this function
// Start the search for the string at the specified index
// Return the starting index of the string if it is found, -1 if it isn't
int MyString::IndexOf(const char* str, int startIndex) //const
{
	int i = startIndex;
	int match = 1;
	int* newStr = new int[255];
	populateCharArr(str, newStr);

	while (i < Length(m_str))
	{
		int index = Length(str) - 1;
		i+=index;
		match = 1;
		
		while(match == 1)
		{
			if ((str[index] == m_str[i]) && index == 0)
			{
				return i;
			}
			else if (str[index] == m_str[i])
			{
				index--;
				i--;
			}
			else if (str[index] != m_str[i])
			{
				match = 0;
				i = i - newStr[m_str[i]];
			}
		}
		//i++;
	}

	return -1;
}

int MyString::Length() const
{
    return Length(m_str);
}

int MyString::Length(const char* str)
{
    int len = 0;
    while (*str++)
    {
        len++;
    }
    return len;
}

int MyString::Length(const int* str)
{
	int len = 0;
	while (*str++)
	{
		len++;
	}
	return len;
}

// Sets the string to a new string value. This is the kind of function 
// that only a mutable string class would have.
void MyString::Set(const char* str)
{
	// First delete the old string
	if (m_str)
	{
		delete [] m_str;
	}

	if (str)
	{
		int len = Length(str);    
		m_str = new char[len + 1];
		char* dst = m_str;
		while (*dst++ = *str++);
	}
	else
	{
		m_str = new char[1];
		m_str[0] = 0;
	}
}

void MyString::Split(char c, std::vector<MyString>& outputVector) const
{
	int i = 0, temp = 0;
	char *split = new char[1];

	while (i < Length(m_str))
	{
		if (m_str[i] == c)
		{
			newArrFromRange(temp, i, split); //copies values of m_str within the given range to split
			outputVector.push_back(MyString(split)); //pushes split onto vector
			temp = i+1;
		}
		i++;
	}
}

void MyString::newArrFromRange(int firsti, int secondi, char *arr) const
{
	int i = 0, c = firsti;

	while (c != secondi)
	{
		arr[i] = m_str[c];
		i++;
		c++;
	}
	arr[i] = '\0';
}

void MyString::newArray(char* newArr, int index)
{
	//char* temp = new char(Length() - index);
	int i = 0;
	while (m_str)
	{
		newArr[i++] = m_str[index++];
	}
}

// Gets a substring from this string and stores it in the output string. If 
// the substring cannot be parsed, then false is returned and the output 
// string is not modified.
bool MyString::Substring(int startIndex, int length, MyString& output) const
{
	int thisLength = this->Length(), i = 0;
	char *temp = new char[thisLength + 1];

	while (startIndex < thisLength && length--)
	{
		if (!m_str)
			return false;
		temp[i] = m_str[startIndex];
		i++;
		startIndex++;
	}
	temp[i] = '\0';

	output.Set(temp);

	return true;
}


void MyString::Write(std::ostream& stream)
{
	stream << m_str;
}
