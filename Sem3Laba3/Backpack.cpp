#include <sstream>
#include <string>

#include "DynamicArray.h"
#include "HashTable.h"
#include "Item.h"
#include "State.h"

std::string MemoKey(int index, int weight, int volume)
{
    std::ostringstream oss;
    oss << index << "_" << weight << "_" << volume;
    return oss.str();
}

void Explore(const DynamicArray<Item>& items, int maxWeight, int maxVolume,
    State current, int index, State& bestSolution, int& bestValue, HashTable<std::string, int>& memo)
{
    if (index == items.GetLength())
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

    if (index < current.GetLength() &&
        current.totalWeight + items[index].weight <= maxWeight &&
        current.totalVolume + items[index].volume <= maxVolume)
    {
        current.totalWeight += items[index].weight;
        current.totalVolume += items[index].volume;
        current.totalValue += items[index].value;
        current.selectedItems[index] = true;

        Explore(items, maxWeight, maxVolume, current, index + 1, bestSolution, bestValue, memo);
    }

}

State Package(const DynamicArray<Item>& items, int maxWeight, int maxVolume)
{
    State bestSolution(items.GetLength());
    int bestValue = 0;
    HashTable<std::string, int> memo(1000);

    Explore(items, maxWeight, maxVolume, State(items.GetLength()), 0, bestSolution, bestValue, memo);

    return bestSolution;
}