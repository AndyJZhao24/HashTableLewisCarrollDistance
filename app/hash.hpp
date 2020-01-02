#ifndef ___HASH__HPP
#define ___HASH__HPP

#include <string>
#include "Wordset.hpp"

void loadWordsIntoTable(WordSet & words, std::istream & in);


std::string convert(std::string s1, std::string s2, const WordSet & words);

bool isSubWord(std::string s1, std::string s2);

#endif