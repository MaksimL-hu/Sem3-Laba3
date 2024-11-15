#include <iostream>
#include <vector>
#include <string>
#include <sstream>

#include "State.h"
#include "Item.h"
#include "HashTable.h"

void PrintSolution(const State& state)
{
    std::cout << "Solution - Total Value: " << state.totalValue
        << ", Total Weight: " << state.totalWeight
        << ", Total Volume: " << state.totalVolume
        << ", Items: ";

    for (size_t i = 0; i < state.selectedItems.size(); ++i)
        if (state.selectedItems[i])
            std::cout << i + 1 << " ";

    std::cout << "\n";
}

std::string MemoKey(int index, int weight, int volume)
{
    std::ostringstream oss;
    oss << index << "_" << weight << "_" << volume;
    return oss.str();
}

void Explore(const std::vector<Item>& items, int maxWeight, int maxVolume, State current, int index, State& bestSolution, int& bestValue, HashTable<std::string, int>& memo)
{
    if (index == items.size())
    {
        if (current.totalWeight <= maxWeight && current.totalVolume <= maxVolume)
        {
            if (current.totalValue > bestValue)
            {
                bestValue = current.totalValue;
                bestSolution = current;
            }
        }

        return;
    }

    std::string key = MemoKey(index, current.totalWeight, current.totalVolume);
    auto memoValue = memo.GetValue(key);

    if (memoValue.has_value() && memoValue.value() >= current.totalValue)
        return;

    memo.Add(key, current.totalValue);

    Explore(items, maxWeight, maxVolume, current, index + 1, bestSolution, bestValue, memo);

    if (current.totalWeight + items[index].weight <= maxWeight &&
        current.totalVolume + items[index].volume <= maxVolume)
    {

        current.totalWeight += items[index].weight;
        current.totalVolume += items[index].volume;
        current.totalValue += items[index].value;
        current.selectedItems[index] = true;

        Explore(items, maxWeight, maxVolume, current, index + 1, bestSolution, bestValue, memo);
    }
}

//void Explore(const std::vector<Item>& items, int maxWeight, int maxVolume, State current, int index, State& bestSolution, int& bestValue)
//{
//    if (index == items.size())
//    {
//        if (current.totalWeight <= maxWeight && current.totalVolume <= maxVolume)
//        {
//            if (current.totalValue > bestValue)
//            {
//                bestValue = current.totalValue;
//                bestSolution = current;
//            }
//        }
//
//        return;
//    }
//
//    Explore(items, maxWeight, maxVolume, current, index + 1, bestSolution, bestValue);
//
//    if (current.totalWeight + items[index].weight <= maxWeight &&
//        current.totalVolume + items[index].volume <= maxVolume)
//    {
//        current.totalWeight += items[index].weight;
//        current.totalVolume += items[index].volume;
//        current.totalValue += items[index].value;
//        current.selectedItems[index] = true;
//
//        Explore(items, maxWeight, maxVolume, current, index + 1, bestSolution, bestValue);
//    }
//}

void Package(const std::vector<Item>& items, int maxWeight, int maxVolume)
{
    State bestSolution(items.size());
    int bestValue = 0;
    HashTable<std::string, int> memo(1000);

    Explore(items, maxWeight, maxVolume, State(items.size()), 0, bestSolution, bestValue, memo);

    std::cout << "Best ";
    PrintSolution(bestSolution);
}