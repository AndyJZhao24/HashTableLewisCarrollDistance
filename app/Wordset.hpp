#ifndef __WORD_SET__HPP
#define __WORD_SET__HPP

const int SIZES[] = { 11, 23, 41, 83, 163, 331, 641, 1283, 2579, 5147, 10243, 20483, 40961, 81929, 163847};

#include <string>

int hashFunction(std::string s, int base, int mod);

void fillEmptyArray(std::string * x, int length); //Fills array with empty strings [""]

class WordSet
{
public: 
	WordSet();
	~WordSet();

	// adds the given string to the WordSet, so that any 
	// future calls to contains(s) will return true.
	void insert(std::string s);

	bool contains(std::string s) const;

	// return how many distinct strings are in the set
	int getCount() const; 

	// return how large the underlying array is.
	int getCapacity() const;

	void resize(); //Resizes the dynamically allocated array

	std::string getString(int index) const; //Gets string given index

private:
	int count;
	int size;
	int sizePos; //index of current size
	std::string * hashArray; //Array to store the strings
};


#endif