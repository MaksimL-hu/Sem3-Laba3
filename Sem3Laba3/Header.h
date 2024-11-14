#ifndef A_H
#define A_H

#include <iostream>
#include <string>
#include <vector>

#include "HashTable.h"
#include "SparseVector.h"
#include "AlphabetIndex.h"
#include "Backpack.h"

void test2()
{
    HashTable<int, int> hashTable(2);

    std::cout << hashTable.GetCapacity() << std::endl;
    hashTable.Add(1, 1);
    hashTable.Add(2, 2);
    hashTable.Add(3, 3);
    hashTable.Add(4, 4);
    hashTable.Add(5, 5);
    hashTable.Add(6, 6);
    hashTable.Add(7, 7);
    std::cout << hashTable.GetCapacity() << std::endl;

    auto value = hashTable.GetValue(2);
    if (value)
        std::cout << "Value for key 2: " << *value << std::endl;
    else
        std::cout << "Key 2 not found" << std::endl;

    std::cout << hashTable.GetCount() << std::endl;
    hashTable.Remove(2);
    hashTable.Remove(2);

    value = hashTable.GetValue(2);
    if (value)
    {
        std::cout << "Value for key 2: " << *value << std::endl;
    }
    else
    {
        std::cout << "Key 2 not found" << std::endl;
    }

    hashTable.Display();
}

void test3()
{
    SparseVector<int> vec(0);

    int arr[] = { 0, 5, 0, 10, 0, 15, 0, 0, 20 };
    int size = sizeof(arr) / sizeof(arr[0]);

    vec.Add(arr, size);

    vec.Display();
    std::cout << *vec.GetValue(8) << std::endl;
}

void test4()
{
    std::string text = "Here is your text. This is an example text for an alphabetical index.";
    int pageSize = 5;
    bool isByWords = true; 

    auto alphabetIndex = BuildAlphabetIndex(text, pageSize, isByWords);

    DisplayAlphabetIndex(alphabetIndex);
}

void test5()
{
    std::vector<Item> items = { {2, 3, 40}, {3, 4, 50}, {5, 6, 70}, {4, 2, 30} };
    int maxWeight = 10;
    int maxVolume = 12;
}

#endif