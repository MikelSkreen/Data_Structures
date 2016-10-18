// Cpt S 223 Homework Assignment - MyString class
// (put your name here)

#ifndef MYSTRINGH
#define MYSTRINGH

#include <iostream>
#include <vector>
//#include <stdio.h>
//#include <stdlib.h>
// Do NOT include <string> or <string.h> in this class. You must implement all the 
// string functionality without the use of the STL string or any string library 
// functions.

class MyString
{
private:
    char* m_str;

	MyString(const char* str, int charCount);
    
    static bool AreEqual(const char* str1, const char* str2, int numCharsToCompare);

	// Copies the specified number of characters from the source to destination
	static void Copy(char* destination, const char* source, int count);
	int getGreatestIndex(char c, const char* str);
	void populateCharArr(const char *set, int* newStr);
	int Length(const int* str);
    // Utility function to compute the length of a string. The null-terminating 
	// character is NOT counted.
    static int Length(const char* str);

	void newArray(char* newArr, int index); //function will create new array with values from m_str beginning after index
	void newArrFromRange(int firsti, int secondi, char *arr) const;
    
public:
    MyString();
	MyString(const MyString& copyme);
	// IMPORTANT: You must add a copy constructor. You should know what this should 
	// look like based on the discussions we had in class.
	MyString(const char* str);
	~MyString();
    
    int GetAnagrams(std::vector<MyString>& candidates, std::vector<MyString>& output);
	int IndexOf(char c, int startIndex = 0) const;
	int IndexOf(const char* str, int startIndex = 0);// const;
    int Length() const;
	int *BuildFreqTable(const char*s);
	void Set(const char* str);
	void Split(char c, std::vector<MyString>& outputVector) const;
	bool Substring(int startIndex, int length, MyString& output) const;
	void Write(std::ostream& stream);
};
#endif
