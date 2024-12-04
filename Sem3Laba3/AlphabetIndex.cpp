#include <sstream>
#include <string>

#include "DynamicArray.h"
#include "HashTable.h"

DynamicArray<std::string> SplitIntoWords(const std::string& text)
{
    std::istringstream stream(text);
    DynamicArray<std::string> words;
    std::string word;

    while (stream >> word)
        words.Append(word);

    return words;
}

void BuildAlphabetIndex(HashTable<std::string, DynamicArray<int>>& wordPageHashTable, const std::string& text,
    int pageSize, bool isByWords)
{
    DynamicArray<std::string> words = SplitIntoWords(text);
    int currentPage = 1;
    int currentPageSize = 0;

    for (int i = 0; i < words.GetLength(); ++i)
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

        if (wordPageHashTable.ContainsKey(word))
        {
            auto pagesOptional = wordPageHashTable.GetValue(word);

            if (pagesOptional.has_value())
            {
                DynamicArray<int>& pages = pagesOptional.value();
                pages.Append(currentPage);
                wordPageHashTable.Add(word, pages);
            }
        }
        else
        {
            DynamicArray<int> newPages;
            newPages.Append(currentPage);
            wordPageHashTable.Add(word, newPages);
        }
    }
}