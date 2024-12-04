#ifndef PRINTER_H
#define PRINTER_H

#include <iostream>
#include <string>

#include "State.h"
#include "DynamicArray.h"
#include "HashTable.h"

using namespace std;

template <typename T>
void PrintValue(const T& value, ostream& os)
{
    os << value;
}

template <typename T>
void PrintValue(const DynamicArray<T>& value, ostream& os)
{
    os << "[";

    for (int i = 0; i < value.GetLength(); ++i)
    {
        PrintValue(value[i], os);

        if (i < value.GetLength() - 1)
            os << ", ";
    }

    os << "]";
}

template <typename TKey, typename TValue, typename Hash = hash<TKey>>
void PrintValue(const HashTable<TKey, TValue, Hash>& value, ostream& os)
{
    for (int i = 0; i < value.GetCapacity(); ++i)
    {
        if (value.ConstainsIndex(i))
        {
            PrintValue(value.GetKeyByIndex(i), os);
            os << " : ";
            PrintValue(value.GetValueByIndex(i), os);
            os << "\n";
        }
    }
}

template <typename>
void PrintSolution(const State& state, ostream& os)
{
    os << "Solution - Total Value: " << state.totalValue
        << ", Total Weight: " << state.totalWeight
        << ", Total Volume: " << state.totalVolume
        << ", Items: ";

    int size = state.GetLength();

    for (int i = 0; i < size; ++i)
        if (state.selectedItems[i] == true)
            os << i + 1 << " ";

    os << "\n";
}

#endif