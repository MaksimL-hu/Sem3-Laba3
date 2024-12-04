#include <cassert>
#include <string>

#include "AlphabetIndex.h"
#include "Backpack.h"
#include "DynamicArray.h"
#include "HashTable.h"
#include "Item.h"
#include "SparseVector.h"
#include "State.h"

#include "Printer.h"

namespace HashTableTests
{
    const std::string key1 = "one";
    const std::string key2 = "two";
    const std::string key3 = "three";
    const int value1 = 1;
    const int value2 = 2;
    const int value3 = 3;

    void SetUp(HashTable<std::string, int>& table)
    {
        table.Add(key1, value1);
        table.Add(key2, value2);
        table.Add(key3, value3);
    }

    void AddElements()
    {
        HashTable<std::string, int> table;
        SetUp(table);

        assert(table.ContainsKey(key1));
        assert(table.ContainsKey(key2));
        assert(table.ContainsKey(key3));
        assert(table.GetValue(key1).value() == value1);
        assert(table.GetValue(key2).value() == value2);
        assert(table.GetValue(key3).value() == value3);
    }

    void UpdateValue()
    {
        int newValue1 = 10;

        HashTable<std::string, int> table;
        SetUp(table);

        table.Add(key1, newValue1);

        assert(table.GetValue(key1).value() == newValue1);
    }

    void ContainsKey()
    {
        HashTable<std::string, int> table;
        SetUp(table);

        assert(table.ContainsKey(key2));
        assert(!table.ContainsKey("four"));
    }

    void RemoveElement()
    {
        HashTable<std::string, int> table;
        SetUp(table);

        table.Remove(key2);
        assert(!table.ContainsKey(key2));
        assert(table.GetCount() == 2);
    }

    void ResizeUp()
    {
        HashTable<std::string, int> table;
        SetUp(table);

        for (int i = 0; i < 100; ++i)
            table.Add("key" + std::to_string(i), i);

        assert(table.GetCount() == 103);
        assert(table.GetCapacity() > 20);
    }

    void IsEmpty()
    {
        HashTable<std::string, int> emptyTable;

        assert(emptyTable.IsEmpty());
        assert(emptyTable.GetCount() == 0);
    }

    void ResizeDown()
    {
        HashTable<std::string, int> table;
        SetUp(table);

        for (int i = 0; i < 100; ++i)
            table.Add("key" + std::to_string(i), i);

        for (int i = 0; i < 100; ++i)
            table.Remove("key" + std::to_string(i));

        assert(table.GetCount() == 3);
        assert(table.GetCapacity() < 100);
    }

    void Collisions()
    {
        HashTable<int, int> table(5);

        table.Add(1, 100);
        table.Add(6, 200);

        assert(table.GetValue(1).value() == 100);
        assert(table.GetValue(6).value() == 200);
    }
}

namespace SparseVectorTests
{
    const int defaultValue = 0;
    const int value1 = 1;
    const int value2 = 2;
    const int value3 = 3;
    const int index1 = 0;
    const int index2 = 5;
    const int index3 = 10;

    void SetUp(SparseVector<int>& vector)
    {
        vector.Add(index1, value1);
        vector.Add(index2, value2);
        vector.Add(index3, value3);
    }

    void AddElements()
    {
        SparseVector<int> vector(defaultValue);
        SetUp(vector);

        assert(vector.ContainsKey(index1));
        assert(vector.ContainsKey(index2));
        assert(vector.ContainsKey(index3));
        assert(vector.GetValue(index1).value() == value1);
        assert(vector.GetValue(index2).value() == value2);
        assert(vector.GetValue(index3).value() == value3);
    }

    void UpdateValue()
    {
        SparseVector<int> vector(defaultValue);
        SetUp(vector);

        int newValue = 42;
        vector.Set(index1, newValue);

        assert(vector.GetValue(index1).value() == newValue);
        assert(vector.GetValue(index2).value() == value2);
    }

    void RemoveElement()
    {
        SparseVector<int> vector(defaultValue);
        SetUp(vector);

        vector.Remove(index2);

        assert(!vector.ContainsKey(index2));
        assert(vector.GetCount() == 2);
    }

    void AddArray()
    {
        SparseVector<int> vector(defaultValue);

        int array[] = { 0, 1, 0, 2, 0, 3 };
        vector.Add(array, 6);

        assert(vector.ContainsKey(1));
        assert(vector.ContainsKey(3));
        assert(vector.ContainsKey(5));
        assert(vector.GetValue(1).value() == 1);
        assert(vector.GetValue(3).value() == 2);
        assert(vector.GetValue(5).value() == 3);
    }

    void MemoryUsage()
    {
        SparseVector<int> vector(defaultValue);
        SetUp(vector);

        size_t memory = vector.MemoryUsage();
        assert(memory == vector.GetCount() * (sizeof(size_t) + sizeof(int)));
    }

    void DefaultValueBehavior()
    {
        SparseVector<int> vector(defaultValue);

        assert(vector.GetValue(100).value() == defaultValue);
        vector.Set(100, defaultValue);
        assert(!vector.ContainsKey(100));
    }

    void EmptyVector()
    {
        SparseVector<int> vector(defaultValue);

        assert(vector.GetCount() == 0);
    }
}

namespace BackPackTests
{
    void TestMemoKey()
    {
        std::string key = MemoKey(2, 50, 30);
        assert(key == "2_50_30");
    }

    void EmptyBackPack()
    {
        DynamicArray<Item> items;
        int maxWeight = 50;
        int maxVolume = 30;

        State result = Package(items, maxWeight, maxVolume);

        assert(result.totalValue == 0);
        assert(result.totalWeight == 0);
        assert(result.totalVolume == 0);

        for (int i = 0; i < result.GetLength(); ++i)
            assert(!result.selectedItems[i]);
    }

    void SingleItemFits()
    {
        DynamicArray<Item> items(1);
        items[0] = Item(10, 5, 1);

        int maxWeight = 50;
        int maxVolume = 30;

        State result = Package(items, maxWeight, maxVolume);

        assert(result.totalValue == 1);
        assert(result.totalWeight == 10);
        assert(result.totalVolume == 5);
        assert(result.selectedItems[0]);
    }

    void SingleItemDoesNotFit()
    {
        DynamicArray<Item> items(1);
        items[0] = Item{ 10, 60, 40 };

        int maxWeight = 50;
        int maxVolume = 30;

        State result = Package(items, maxWeight, maxVolume);

        assert(result.totalValue == 0);
        assert(result.totalWeight == 0);
        assert(result.totalVolume == 0);
        assert(!result.selectedItems[0]);
    }

    void MultipleItems()
    {
        DynamicArray<Item> items(3);
        items[0] = Item{ 10, 5, 60 };
        items[1] = Item{ 20, 10, 100 };
        items[2] = Item{ 30, 15, 120 };

        int maxWeight = 50;
        int maxVolume = 25;

        State result = Package(items, maxWeight, maxVolume);

        assert(result.totalValue == 220);
        assert(result.totalWeight == 50);
        assert(result.totalVolume == 25);
        assert(result.selectedItems[1]);
        assert(result.selectedItems[2]);
        assert(!result.selectedItems[0]);
    }

    void BackPackFullCapacity()
    {
        DynamicArray<Item> items(4);
        items[0] = Item(5, 5, 15);
        items[1] = Item(4, 3, 10);
        items[2] = Item(3, 2, 9);
        items[3] = Item(1, 1, 5);

        int maxWeight = 10;
        int maxVolume = 8;

        State result = Package(items, maxWeight, maxVolume);

        assert(result.totalValue == 29);
        assert(result.totalWeight == 9);
        assert(result.totalVolume == 8);
        assert(result.selectedItems[0]);
        assert(result.selectedItems[2]);
        assert(result.selectedItems[3]);
        assert(!result.selectedItems[1]);
    }

    void Memoization()
    {
        DynamicArray<Item> items(3);
        items[0] = Item(2, 1, 10);
        items[1] = Item(3, 2, 20);
        items[2] = Item(4, 3, 30);

        int maxWeight = 6;
        int maxVolume = 4;

        HashTable<std::string, int> memo(100);
        State current(items.GetLength());
        State bestSolution(items.GetLength());
        int bestValue = 0;

        Explore(items, maxWeight, maxVolume, current, 0, bestSolution, bestValue, memo);

        assert(memo.GetCount() > 0);

        assert(bestValue == 40);
        assert(bestSolution.totalWeight == 6);
        assert(bestSolution.totalVolume == 4);
    }
}

namespace AlphabetIndexTests
{
    void EmptyText()
    {
        std::string text = "";
        HashTable<std::string, DynamicArray<int>> wordPageHashTable;
        BuildAlphabetIndex(wordPageHashTable, text, 100, true);

        assert(wordPageHashTable.GetCount() == 0);
    }

    void SingleWordText()
    {
        std::string text = "hello";
        HashTable<std::string, DynamicArray<int>> wordPageHashTable;
        BuildAlphabetIndex(wordPageHashTable, text, 100, true);

        auto pagesOptional = wordPageHashTable.GetValue("hello");
        assert(pagesOptional.has_value());
        DynamicArray<int>& pages = pagesOptional.value();
        assert(pages.GetLength() == 1);
        assert(pages[0] == 1);
    }

    void MultipleWords()
    {
        std::string text = "hello world";
        HashTable<std::string, DynamicArray<int>> wordPageHashTable;
        BuildAlphabetIndex(wordPageHashTable, text, 100, true);

        auto helloPages = wordPageHashTable.GetValue("hello");
        auto worldPages = wordPageHashTable.GetValue("world");

        assert(helloPages.has_value());
        assert(worldPages.has_value());

        DynamicArray<int>& helloPageArray = helloPages.value();
        DynamicArray<int>& worldPageArray = worldPages.value();

        assert(helloPageArray[0] == 1);
        assert(worldPageArray[0] == 1);
    }

    void LongText()
    {
        std::string text = "hello hello hello hello";
        HashTable<std::string, DynamicArray<int>> wordPageHashTable;
        BuildAlphabetIndex(wordPageHashTable, text, 10, true);

        auto helloPages = wordPageHashTable.GetValue("hello");
        assert(helloPages.has_value());

        DynamicArray<int>& pages = helloPages.value();
        assert(pages.GetLength() == 4); 
        assert(pages[0] == 1);
        assert(pages[1] == 1);
        assert(pages[2] == 1);
        assert(pages[3] == 1);
    }

    void ByWordsAndByCharacters()
    {
        std::string text = "abc def ghi";
        HashTable<std::string, DynamicArray<int>> wordPageHashTableByWords;
        HashTable<std::string, DynamicArray<int>> wordPageHashTableByChars;

        BuildAlphabetIndex(wordPageHashTableByWords, text, 100, true);
        auto abcPagesByWords = wordPageHashTableByWords.GetValue("abc");
        assert(abcPagesByWords.has_value());
        DynamicArray<int>& abcPagesByWordsArray = abcPagesByWords.value();
        assert(abcPagesByWordsArray[0] == 1);

        BuildAlphabetIndex(wordPageHashTableByChars, text, 100, false);
        auto aPagesByChars = wordPageHashTableByChars.GetValue("a");
        assert(!aPagesByChars.has_value());

        auto dPagesByChars = wordPageHashTableByChars.GetValue("d");
        assert(!dPagesByChars.has_value());

        auto fPagesByWords = wordPageHashTableByWords.GetValue("def");
        assert(fPagesByWords.has_value());
        DynamicArray<int>& fPagesByWordsArray = fPagesByWords.value();
        assert(fPagesByWordsArray[0] == 1);
    }

    void Test()
    {
        std::string text = "word word word word word word word word";
        HashTable<std::string, DynamicArray<int>> wordPageHashTable;

        BuildAlphabetIndex(wordPageHashTable, text, 20, false);

        auto wordPages = wordPageHashTable.GetValue("word");
        assert(wordPages.has_value());
        DynamicArray<int>& pages = wordPages.value();

        assert(pages[0] == 1);
        assert(pages[1] == 1);
        assert(pages[2] == 2);
        assert(pages[3] == 2);
        assert(pages[4] == 2);
        assert(pages[5] == 2);
        assert(pages[6] == 3);
        assert(pages[7] == 3);
    }
}

void TestHashTable()
{
    HashTableTests::AddElements();
    HashTableTests::UpdateValue();
    HashTableTests::ContainsKey();
    HashTableTests::RemoveElement();
    HashTableTests::ResizeUp();
    HashTableTests::IsEmpty();
    HashTableTests::ResizeDown();
    HashTableTests::Collisions();
}

void TestSparseVector()
{
    SparseVectorTests::AddElements();
    SparseVectorTests::UpdateValue();
    SparseVectorTests::RemoveElement();
    SparseVectorTests::AddArray();
    SparseVectorTests::MemoryUsage();
    SparseVectorTests::DefaultValueBehavior();
    SparseVectorTests::EmptyVector();
}

void TestBackPack()
{
    BackPackTests::TestMemoKey();
    BackPackTests::EmptyBackPack();
    BackPackTests::SingleItemFits();
    BackPackTests::SingleItemDoesNotFit();
    BackPackTests::MultipleItems();
    BackPackTests::BackPackFullCapacity();
    BackPackTests::Memoization();
}

void TestAlphabetIndex()
{
    AlphabetIndexTests::EmptyText();
    AlphabetIndexTests::SingleWordText();
    AlphabetIndexTests::MultipleWords();
    AlphabetIndexTests::LongText();
    AlphabetIndexTests::ByWordsAndByCharacters();
    AlphabetIndexTests::Test();
}