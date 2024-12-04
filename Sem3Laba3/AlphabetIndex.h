#pragma once
#ifndef ALPHABET_INDEX_H
#define ALPHABET_INDEX_H

#include <string>

#include "DynamicArray.h"
#include "HashTable.h"

DynamicArray<std::string> SplitIntoWords(const std::string& text);
void BuildAlphabetIndex(HashTable<std::string, DynamicArray<int>>& wordPageHashTable, const std::string& text,
    int pageSize, bool isByWords);

#endif