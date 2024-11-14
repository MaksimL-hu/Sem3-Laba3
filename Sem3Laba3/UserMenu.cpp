#include <iostream>
#include <string>

#include "Item.h"
#include "FileWorker.h"
#include "Commands.h"
#include "Backpack.h"

using namespace std;

void Help()
{
	cout << "'" << GenerateFileOfItems << "' - Generate txt file\n"
		<< "'" << PackItemsInBackpack << "' - Generate txt file\n";
}

template<typename T>
void ReadVariable(T& variable, const string& message)
{
	cout << message << "\n";
	cin >> variable;
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
			Package(items, maxWeight, maxVolume, fileName);
		}
		else
		{
			cout << "Unknown command\n";
		}
	}
}