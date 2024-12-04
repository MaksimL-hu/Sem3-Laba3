#ifndef FILE_WORKER_H
#define FILE_WORKER_H

#include <string>

#include "DynamicArray.h"
#include "HashTable.h"
#include "Item.h"

void GenerateItemsToFile(const std::string& filename, int itemCount, int maxWeight, int maxVolume, int maxValue);
DynamicArray<Item> ReadItemsFromFile(const std::string& filename);
std::string ReadTextFromFile(const std::string& filename);
void WriteAlphabetIndexToFile(const std::string& filename, const HashTable<std::string, DynamicArray<int>>& hashTable);

#endif