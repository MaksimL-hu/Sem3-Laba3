#ifndef BACKPACK_H
#define BACKPACK_H

#include <vector>

#include "State.h"
#include "Item.h"
#include "HashTable.h"

void PrintSolution(const State& state);
void Explore(const std::vector<Item>& items, int maxWeight, int maxVolume, State current, int index, State& bestSolution, int& bestValue, HashTable<std::string, int>& memo);
void Package(const std::vector<Item>& items, int maxWeight, int maxVolume, std::string& fileName);

#endif