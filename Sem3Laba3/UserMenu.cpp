#include <iostream>
#include <string>
#include <vector>

#include "Item.h"
#include "FileWorker.h"
#include "AlphabetIndex.h"
#include "Commands.h"
#include "Backpack.h"
#include "SparseVector.h"
#include "Input.h"
#include "Tests.h"

using namespace std;

void Help()
{
	cout << "'" << GenerateFileOfItems << "' - Generate txt file\n"
		<< "'" << PackItemsInBackpack << "' - Generate txt file\n"
		<< "'" << CreateSparseVector << "' - Create sparse vector\n"
		<< "'" << BuildAlphabet << "' - Create indexes for word\n"
		<< "'" << RunAllTests << "' - run all tests\n";
}

void OpenMenu()
{
	bool isOpen = true;
	string userInput;

	cout << "Write 'help' to show available commands\n";

	while (isOpen)
	{
		cin >> userInput;

		if (userInput == helpCommand)
		{
			Help();
		}
		else if (userInput == GenerateFileOfItems)
		{
			int count;
			int maxWeight;
			int maxVolume;
			int maxValue;
			string fileName;

			ReadVariable(fileName, "Write file name");
			ReadVariable(count, "Write count data in file");
			ReadVariable(maxWeight, "Write max weight of Item");
			ReadVariable(maxVolume, "Write max volume of Item");
			ReadVariable(maxValue, "Write max value of Item");

			cout << "Generating data in progress...\n";

			GenerateItemsToFile(fileName, count, maxWeight, maxVolume, maxValue);

			cout << "Generating data is completed\n";
		}
		else if (userInput == PackItemsInBackpack)
		{
			int maxWeight;
			int maxVolume;
			string fileName;

			ReadVariable(fileName, "Write file name of Items");
			ReadVariable(maxWeight, "Write max weight of Backpack");
			ReadVariable(maxVolume, "Write max volume of Backpack");

			cout << "Reading in progress...\n";
			vector<Item> items = ReadItemsFromFile(fileName);

			cout << "Calculating item placement...\n";
			Package(items, maxWeight, maxVolume);
		}
		else if (userInput == CreateSparseVector)
		{
			int count;
			int percent;

			ReadVariable(count, "Write count of items");
			ReadVariable(percent, "Write percent of null data");

			SparseVector<Item> sparseItems;
			Item* items = (Item*)calloc(count, sizeof(Item));

			for (size_t i = 0; i < count; i++) {
				int chance = 1 + std::rand() % 100;

				if (chance > percent) {
					items[i] = Item(i + 1, i + 1, i + 1);
				}
				else {
					items[i] = Item();
				}
			}

			sparseItems.Add(items, count);

			std::cout << "The memory occupied in the array: " << sizeof(Item) * count << " bytes\n";
			std::cout << "The memory occupied in the sparse vector: " << sparseItems.MemoryUsage() << " bytes\n";

			/*for (size_t i = 0; i < count; i++) 
			{
				auto value = sparseItems.GetValue(i);

				if (value.has_value()) 
				{
					std::cout << "Item " << i << ": "
						<< value->weight << " "
						<< value->volume << " "
						<< value->value << "\n";
				}
			}*/

			free(items);
		}
		else if (userInput == BuildAlphabet)
		{
			std::string inputFileName;
			std::string outputFileName;
			int pageSize;
			bool isByWords;

			ReadVariable(inputFileName, "Enter input file name");
			ReadVariable(outputFileName, "Enter output file name");
			ReadVariable(pageSize, "Enter page size");
			ReadVariable(isByWords, "Use word count for page size (1) or character count (0)");

			std::string text = ReadTextFromFile(inputFileName);

			if (text.empty())
			{
				std::cerr << "No text to process. Exiting.\n";
				continue;
			}

			HashTable<std::string, std::vector<int>> alphabetIndex = BuildAlphabetIndex(text, pageSize, isByWords);
			WriteAlphabetIndexToFile(outputFileName, alphabetIndex);

			std::cout << "Alphabet index has been saved to " << outputFileName << "\n";
		}
		else if (userInput == RunAllTests)
		{
			TestAll();
		}
		else
		{
			cout << "Unknown command\n";
		}
	}
}