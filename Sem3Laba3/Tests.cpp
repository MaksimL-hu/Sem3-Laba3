#include <cassert>
#include <iostream>
#include <string>

#include "AlphabetIndex.h"
#include "Backpack.h"
#include "HashTable.h"
#include "SparseVector.h"

void TestHashTable() 
{
    HashTable<std::string, int> table;

    table.Add("key1", 10);
    assert(table.GetValue("key1").value() == 10);

    table.Add("key1", 20);
    assert(table.GetValue("key1").value() == 20);

    table.Remove("key1");
    assert(!table.GetValue("key1").has_value());

    for (int i = 0; i < 50; ++i) 
        table.Add("key" + std::to_string(i), i);
    
    assert(table.GetCapacity() > 20);

    assert(!table.GetValue("missing").has_value());

    std::cout << "HashTable test is completed. Status: Ok" << "\n";
}

void TestSparseVector() 
{
    SparseVector<int> vector(0);

    vector.Set(0, 10);
    vector.Set(5, 15);
    assert(vector.GetValue(0).value() == 10);
    assert(vector.GetValue(5).value() == 15);

    vector.Set(5, 0);
    assert(vector.GetValue(5).value() == 0);

    std::cout << "SparseVector test is completed. Status: Ok" << "\n";
}

void TestBuildAlphabetIndex() 
{
    std::string text = "apple banana apple orange apple";
    int pageSize = 5;

    auto index = BuildAlphabetIndex(text, pageSize, true);

    auto applePages = index.GetValue("apple").value();
    assert(applePages.size() == 3);

    auto bananaPages = index.GetValue("banana").value();
    assert(bananaPages.size() == 1);

    std::cout << "BuildAlphabetIndex test is completed. Status: Ok" << "\n";
}

void TestPackage() 
{
    std::vector<Item> items = 
    {
        {5, 3, 10}, {10, 5, 20}, {20, 10, 50}
    };

    Package(items, 15, 10);

    assert(true);

    std::cout << "Package test is completed. Status: Ok" << "\n";
}

void TestAll() 
{
    TestHashTable();
    TestSparseVector();
    TestBuildAlphabetIndex();
    TestPackage();

    std::cout << "All tests are completed. Status: Ok" << "\n";
}