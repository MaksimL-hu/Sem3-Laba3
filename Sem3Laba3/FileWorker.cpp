#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <vector>

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