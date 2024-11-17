#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "HashTable.h"

std::vector<std::string> SplitIntoWords(const std::string& text)
{
    std::istringstream stream(text);
    std::vector<std::string> words;
    std::string word;

    while (stream >> word)
        words.push_back(word);

    return words;
}

HashTable<std::string, std::vector<int>> BuildAlphabetIndex(const std::string& text, int pageSize, bool isByWords)
{
    HashTable<std::string, std::vector<int>> wordPageHashTable;
    std::vector<std::string> words = SplitIntoWords(text);
    int currentPage = 1;
    int currentPageSize = 0;

    for (size_t i = 0; i < words.size(); ++i)
    {
        std::string word = words[i];
        int wordLength = isByWords ? 1 : word.size();
        bool canFit;

        if (currentPage == 1)
            canFit = currentPageSize + wordLength <= pageSize / 2;
        else if (currentPage % 10 == 0)
            canFit = currentPageSize + wordLength <= pageSize * 3 / 4;
        else
            canFit = currentPageSize + wordLength <= pageSize;

        if (canFit)
        {
            currentPageSize += isByWords ? 1 : word.size() + 1;
        }
        else
        {
            currentPage++;
            currentPageSize = isByWords ? 1 : word.size();
        }

        auto pages = wordPageHashTable.GetValue(word);

        if (pages.has_value())
        {
            pages->push_back(currentPage);
            wordPageHashTable.Add(word, *pages);
        }
        else
        {
            wordPageHashTable.Add(word, { currentPage });
        }
    }

    return wordPageHashTable;
}

void DisplayAlphabetIndex(const HashTable<std::string, std::vector<int>>& hashTable)
{
    hashTable.Display();
}