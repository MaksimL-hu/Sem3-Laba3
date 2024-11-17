#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "HashTable.h"
#include "Item.h"
#include "State.h"

void GenerateItemsToFile(const std::string& filename, int itemCount, int maxWeight, int maxVolume, int maxValue)
{
    std::ofstream file(filename);

    if (!file) 
    {
        std::cerr << "Error opening file for writing\n";
        return;
    }

    std::srand(static_cast<unsigned>(std::time(nullptr)));

    for (int i = 0; i < itemCount; ++i) 
    {
        int weight = 1 + std::rand() % maxWeight;
        int volume = 1 + std::rand() % maxVolume;
        int value = 1 + std::rand() % maxValue;
        file << weight << " " << volume << " " << value << "\n";
    }

    file.close();
}

std::vector<Item> ReadItemsFromFile(const std::string& filename)
{
    std::ifstream file(filename);
    std::vector<Item> items;

    if (!file) 
    {
        std::cerr << "Error opening file for reading\n";
        return items;
    }

    int weight, volume, value;

    while (file >> weight >> volume >> value)
        items.push_back({ weight, volume, value });

    file.close();

    return items;
}

std::string ReadTextFromFile(const std::string& filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cerr << "Error: Unable to open file " << filename << "\n";
        return "";
    }

    std::string line, text;
    while (std::getline(file, line))
    {
        text += line + "\n";
    }

    file.close();
    
    return text;
}

void WriteAlphabetIndexToFile(const std::string& filename, const HashTable<std::string, std::vector<int>>& hashTable)
{
    std::ofstream file(filename);
    if (!file.is_open())
    {
        std::cerr << "Error: Unable to open file " << filename << "\n";
        return;
    }

    for (int i = 0; i < hashTable.GetCapacity(); i++)
    {
        //итератор для нодов
        auto node = hashTable.GetNodeAt(i);

        if (node)
        {
            file << "Word: " << node->key << "  Pages: ";
            PrintValue(node->value, file);
            file << "\n";
        }
    }

    file.close();
}