#include "proj4.hpp"
#include "Wordset.hpp"
#include <iostream>
#include "proj4.hpp"
#include "Wordset.hpp"
#include <iostream>
#include <set>
#include <sstream>
#include <map>
#include <stack>
#include <queue>

// You should not need to change this function.
void loadWordsIntoTable(WordSet & words, std::istream & in)
{
	std::string line, word;
	std::stringstream ss;

	while(	getline(in, line) )
	{
		ss.clear();
		ss << line;
		while( ss >> word )
		{
			words.insert( word );
		}
	}
}


// You probably want to change this function.
std::string convert(std::string s1, std::string s2, const WordSet & words)
{
	std::queue<std::string> wordQueue; //Queue of possible words
	std::map<std::string, std::string> wordMap; //Map where key is possible word and value is the word we are currently on

	wordQueue.push(s1); //Enqueue s1 to start the queue.
	wordMap[s1] = "";

	while(!wordQueue.empty())
	{
		std::string currWord = wordQueue.front(); //get the front of queue
		wordQueue.pop(); // dequeue
		if(currWord == s2) //if end of path is reached
		{
			std::string prevWord = wordMap[currWord]; //wordMap[currWord] returns the word that "points" to currWord
			std::string path = currWord; //path contains s2

			//Loop Backwards through adding each previous word to the path w/ proper format
			while(prevWord != "")
			{
				path = prevWord + " --> " + path;
				currWord = prevWord;
				prevWord = wordMap[currWord];
			}
			return path;
		}
		else
		{
			std::string possibleWord = currWord;
			//Loop through all of the wordset and find words one-letter away from the current word
			for(int i = 0; i < words.getCapacity(); i++)
			{
				possibleWord = words.getString(i);
				if(wordMap.count(possibleWord) == 0 && isSubWord(possibleWord, currWord)) //if the word is one-letter away and it hasn't been seen yet
				{
					wordMap[possibleWord] = currWord; //Add to map
					wordQueue.push(possibleWord); //Add to queue
				}
			}
		}
	}
	return "Not Found";  // return if no path is reached 
}

//Helper function to find words one-letter away from the current word
bool isSubWord(std::string s1, std::string s2)
{
	if(s1.length() == s2.length() && s2 != s1) //strings are same length and not equal
	{
		int diffCount = 0; //keeps track of number of differences between s1 and s2
		for(int i = 0; i < s1.length(); i++)
		{
			if(s1[i] != s2[i]) //If characters are not the same
				diffCount++;
			if(diffCount > 1) //More than one character is different.
			{
				return false;
			}
		}
		return true;
	}
	else
	{
		return false;
	}
}
