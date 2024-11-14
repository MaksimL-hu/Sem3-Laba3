#ifndef SPARSEVECTOR_H
#define SPARSEVECTOR_H

#include <iostream>
#include <optional>
#include <vector>

#include "IDictionary.h"
#include "HashTable.h"

template <typename TValue>
class SparseVector : public IDictionary<int, TValue> {
private:
    HashTable<int, TValue> data;
    TValue defaultValue;

public:
    SparseVector(TValue defaultValue = TValue()) : defaultValue(defaultValue) {}

    void Add(const int& index, const TValue& value) override
    {
        if (value != defaultValue)
            data.Add(index, value);
        else
            data.Remove(index);
    }

    void Add(const TValue* array, int size)
    {
        for (int i = 0; i < size; ++i)
        {
            if (array[i] != defaultValue)
            {
                Set(i, array[i]);
            }
        }
    }

    void Set(int index, TValue value)
    {
        if (value != defaultValue) 
            data.Add(index, value);
        else
            data.Remove(index);
    }

    std::optional<TValue> GetValue(const int& index) const override 
    {
        auto result = data.GetValue(index);

        if (result)
            return *result;

        return defaultValue; 
    }

    bool ContainsKey(const int& index) const override 
    {
        return data.ContainsKey(index);
    }

    void Remove(const int& index) override
    {
        data.Remove(index);
    }

    int GetCount() const override 
    {
        return data.GetCount();
    }

    int GetCapacity() const override 
    {
        return data.GetCapacity();
    }

    void Display() 
    {
        std::cout << "Sparse Vector:" << std::endl;
        data.Display();
    }
};

#endif