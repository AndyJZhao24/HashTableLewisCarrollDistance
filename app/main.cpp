#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <set>

#include "hash.hpp"
#include "Wordset.hpp"


int main()
{
	WordSet words;
	std::ifstream in("words.txt");
	loadWordsIntoTable(words, in);

	std::string start, end;
	while(true)
	{
		std::cout << "Enter the words in which you want to find the Lewis Carroll distance for." << std::endl;
		std::cout << "Enter the word to start with: ";
		std::cin >> start;
		std::cout << "Enter the destination word: ";
		std::cin >> end;
		if(start.length() != end.length())
		{
			std::cout << "The words must be of equal length.\n\n";
			continue;
		}
		std::cout << convert(start, end, words) << std::endl << std::endl;
	}
    return 0;
}

