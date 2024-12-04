#include <iostream>
#include <string>

#include "AlphabetIndex.h"
#include "Backpack.h"
#include "Commands.h"
#include "DynamicArray.h"
#include "FileWorker.h"
#include "Input.h"
#include "Item.h"
#include "Printer.h"
#include "SparseVector.h"
#include "Tests.h"

using namespace std;

void Help()
{
	cout << "'" << GenerateFileOfItems << "' - Generate txt file\n"
		<< "'" << PackItemsInBackpack << "' - Calculate the most valuable position of Items in the Backpack\n"
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
			DynamicArray<Item> items = ReadItemsFromFile(fileName);

			if (items.GetLength() == 0)
			{
				std::cerr << "Memory allocation failed" << "\n";
				continue;
			}

			cout << "Calculating item placement...\n";

			PrintSolution<void>(Package(items, maxWeight, maxVolume), std::cout);
		}
		else if (userInput == CreateSparseVector)
		{
			int count;
			int percent;

			ReadVariable(count, "Write count of items");
			ReadVariable(percent, "Write percent of null data");

			SparseVector<Item> sparseItems;
			DynamicArray<Item> items(count);

			std::cout << "Creating usual array...\n";

			for (int i = 0; i < count; i++) {
				int chance = 1 + std::rand() % 100;

				if (chance > percent)
					items[i] = Item(i + 1, i + 1, i + 1);
				else
					items[i] = Item();
			}

			std::cout << "Creating sparse vector...\n";

			sparseItems.Add(items);

			std::cout << "The memory occupied in the array: " << sizeof(Item) * count << " bytes\n";
			std::cout << "The memory occupied in the sparse vector: " << sparseItems.MemoryUsage() << " bytes\n";
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

			HashTable<std::string, DynamicArray<int>> alphabetIndex;
			BuildAlphabetIndex(alphabetIndex, text, pageSize, isByWords);
			WriteAlphabetIndexToFile(outputFileName, alphabetIndex);

			std::cout << "Alphabet index has been saved to " << outputFileName << "\n";
		}
		else if (userInput == RunAllTests)
		{
			TestHashTable();
			std::cout << "Hash Table tests passed" << std::endl;
			TestSparseVector();
			std::cout << "Sparse Vector tests passed" << std::endl;
			TestBackPack();
			std::cout << "Back Pack tests passed" << std::endl;
			TestAlphabetIndex();
			std::cout << "Alphabet Index tests passed" << std::endl;
		}
		else
		{
			cout << "Unknown command\n";
		}
	}
}