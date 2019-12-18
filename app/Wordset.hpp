#ifndef __WORD_SET_P4__HPP
#define __WORD_SET_P4__HPP

const int SIZES[] = { 11, 23, 41, 83, 163, 331, 641, 1283, 2579, 5147, 10243, 20483, 40961, 81929, 163847};
// I promise no test case will require you to expand after 163847, or get to the associated load factor.

#include <string>

// You may assume, in writing this function, that the given
// string consists solely of lower-case letters.
// This treats s as a number in the given base.
// with 'a' is 0, 'b' is 1, ... 'z' is 25.
// To get the "number" that a letter-digit represents,
// subtract 'a' from it.
// e.g., (s[0]-'a') is the most significant "digit" of s.
// After every "digit" is processed, mod the current value by mod.
// This will keep you from having overflow.
int hashFunction(std::string s, int base, int mod);

void fillEmptyArray(std::string * x, int length); //Fills array with empty strings [""]

class WordSet
{
public: 
	WordSet();
	~WordSet();

	// adds the given string to the WordSet, so that any 
	// future calls to contains(s) will return true.
	// Note that we are not implementing remove in this
	// project.
	// If this causes the load factor to be higher than the
	// load limit listed in WordSet.cpp, then you need to
	//  increase the capacity.
	// You should think about the relative advantages and 
	// disadvantages to doing this immediately after the 
	// string has been inserted, before returning, versus
	// at the start of the next insert function.
	// Use the declared hash function as your hash function.
	void insert(std::string s);

	bool contains(std::string s) const;

	// return how many distinct strings are in the set
	int getCount() const; 

	// return how large the underlying array is.
	int getCapacity() const;

	void resize(); //Resizes the dynamically allocated array

	std::string getString(int index) const; //Gets string given index

private:
	// You may declare private functions and member variables here.
	int count;
	int size;
	int sizePos; //index of current size
	std::string * hashArray; //Array to store the strings
};


#endif