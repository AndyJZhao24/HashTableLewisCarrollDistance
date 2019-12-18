#include "Wordset.hpp"
#include <string>
#include <math.h>
#include <iostream>

const int BASE_TO_USE = 37; 
const double LOAD_LIMIT = 0.25;


// returns s, as a number in the given base, mod the given modulus
int hashFunction(std::string s, int base, int mod)
{	
	unsigned long long preModNum = 0; //int representing string after coversion but before modding
	for(unsigned int i = 0; i < s.length(); i++)
	{
		preModNum += (s[i] - 'a') * pow(base, s.length() - (i+1));  //represents letterRank * base^(position-1)
	}
	return (int)(preModNum % mod); //returns modded integer
}

void fillEmptyArray(std::string * x, int length)
{
	for(unsigned int i = 0; i < length; i++)
	{
		x[i] = "";
	}
}


WordSet::WordSet()
{
	count = 0;
	size = SIZES[0];
	sizePos = 0;
	hashArray = new std::string[size];
	fillEmptyArray(hashArray, size);

}

WordSet::~WordSet()
{
	delete[] hashArray;
}

void WordSet::resize()
{
	sizePos++; //increment sizePos to represent new index of SIZES
	int formerSize = size; //save former size to loop through old array
	size = SIZES[sizePos]; //reassign size
	count = 0; //reset count because rehashing everything
	std::string * oldHashArray = new std::string[formerSize];

	for(int i = 0; i < formerSize; i++)
	{
		oldHashArray[i] = hashArray[i];
	}

	hashArray = new std::string[size];
	fillEmptyArray(hashArray, size);

	for(int i = 0; i < formerSize; i++)
	{
		if(oldHashArray[i] != "")
		{
			insert(oldHashArray[i]); //Rehash and  reinsert currently inserted strings;
		}
	}
	delete[] oldHashArray; //Garbage collection
}

void WordSet::insert(std::string s)
{
	int sPos = hashFunction(s, BASE_TO_USE, size); //Get the position at which to insert string

	if(hashArray[sPos] == "") //If no collision
	{
		hashArray[sPos] = s;
		count++;
	}
	else //If collision
	{
		int choice = 1;
		while(true)
		{
			sPos = (hashFunction(s,  BASE_TO_USE, size) + (int)pow(choice, 2)) % size; //Find next position
			if(hashArray[sPos] == "")
			{
				hashArray[sPos] = s;
				count++;
				break;
			}
			
			choice++; //increment if empty position not found

		}
	}

	//Check load factor
	if((double)count/size > LOAD_LIMIT)
	{
		resize();
	}
}


bool WordSet::contains(std::string s) const
{
	int sPos = hashFunction(s, BASE_TO_USE, size); //Hash the string
	if(hashArray[sPos] == s)
	{
		return true;
	}
	else if(hashArray[sPos] == "") //if hashArray[sPos] is empty, then no collision occured thus not contained
	{
		return false;
	}
	else //if possible collision
	{
		int choice = 1;
		while(true)
		{
			sPos = (hashFunction(s,  BASE_TO_USE, size) + (int)pow(choice, 2)) % size;
			if(hashArray[sPos] == "") //if new position is empty, no quadratic probing occured, thus not contained
			{
				return false;
			}
			else if (hashArray[sPos] == s)
			{
				return true;
			}
		}
	}
}

// return how many distinct strings are in the set
int WordSet::getCount() const
{
	return count;
}

// return how large the underlying array is.
int WordSet::getCapacity() const
{
	return size;
}

std::string WordSet::getString(int index) const
{
	return hashArray[index]; //return string at given index
}