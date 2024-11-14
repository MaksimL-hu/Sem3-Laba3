#ifndef ALPHABET_INDEX_H
#define ALPHABET_INDEX_H

#include <string>
#include <vector>

#include "HashTable.h"

std::vector<std::string> SplitIntoWords(const std::string& text);
HashTable<std::string, std::vector<int>> BuildAlphabetIndex(const std::string& text, int pageSize, bool isByWords);
void DisplayAlphabetIndex(const HashTable<std::string, std::vector<int>>& hashTable);

#endif