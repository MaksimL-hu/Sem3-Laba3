#ifndef FILE_WORKER_H
#define FILE_WORKER_H

#include <string>
#include <vector>

#include "Item.h"
#include "State.h"
#include "HashTable.h"

void GenerateItemsToFile(const std::string& filename, int itemCount, int maxWeight, int maxVolume, int maxValue);
std::vector<Item> ReadItemsFromFile(const std::string& filename);
std::string ReadTextFromFile(const std::string& filename);
void WriteAlphabetIndexToFile(const std::string& filename, const HashTable<std::string, std::vector<int>>& hashTable);

#endif