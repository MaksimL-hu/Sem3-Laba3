#ifndef FILE_WORKER_H
#define FILE_WORKER_H

#include <string>
#include <vector>

#include "Item.h"
#include "State.h"

void GenerateItemsToFile(const std::string& filename, int itemCount, int maxWeight, int maxVolume, int maxValue);
std::vector<Item> ReadItemsFromFile(const std::string& filename);
void PrintSolutionToFile(const std::string& filename, std::vector<State>& states, State& bestState);

#endif