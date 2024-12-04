#ifndef BACKPACK_H
#define BACKPACK_H

#include <string>

#include "DynamicArray.h"
#include "HashTable.h"
#include "Item.h"
#include "State.h"

std::string MemoKey(int index, int weight, int volume);
void Explore(const DynamicArray<Item>& items, int maxWeight, int maxVolume,
    State current, int index, State& bestSolution, int& bestValue, HashTable<std::string, int>& memo);
State Package(const DynamicArray<Item>& items, int maxWeight, int maxVolume);

#endif