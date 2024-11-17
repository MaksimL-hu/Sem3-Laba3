#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>
#include <optional>
#include <vector>

#include "IDictionary.h"
#include "Item.h"

template <typename T>
void PrintValue(const T& value, std::ostream& os) 
{
    os << value;
}

template <typename T>
void PrintValue(const std::vector<T>& value, std::ostream& os) 
{
    os << "[";

    for (size_t i = 0; i < value.size(); ++i) 
    {
        os << value[i];

        if (i < value.size() - 1)
            os << ", ";
    }

    os << "]";
}

template <typename TKey, typename TValue>
class HashNode 
{
public:
    TKey key;
    TValue value;

    HashNode(TKey key, TValue value) : key(key), value(value) {}
};

template <typename TKey, typename TValue>
class HashTable : public IDictionary<TKey, TValue>
{
private:
    //контейнеры и smrtPtr
    HashNode<TKey, TValue>** array;
    int capacity;
    int size;
    HashNode<TKey, TValue>* dummy;

    //таблица должна уметь сжиматься
    void Resize() 
    {
        int oldCapacity = capacity;
        capacity *= 2;
        HashNode<TKey, TValue>** newArray = new HashNode<TKey, TValue>* [capacity];

        for (int i = 0; i < capacity; i++) 
            newArray[i] = nullptr;

        for (int i = 0; i < oldCapacity; i++) 
        {
            if (array[i] != nullptr && array[i] != dummy) 
            {
                int hashIndex = HashCode(array[i]->key);

                while (newArray[hashIndex] != nullptr) 
                    hashIndex = (hashIndex + 1) % capacity;

                newArray[hashIndex] = array[i];
            }
        }

        delete[] array;
        array = newArray;
    }

public:
    HashTable(int capacity = 20) : capacity(capacity), size(0) 
    {
        array = new HashNode<TKey, TValue>* [capacity];

        for (int i = 0; i < capacity; i++)
            array[i] = nullptr;

        dummy = new HashNode<TKey, TValue>(TKey(), TValue());
    }

    ~HashTable() 
    {
        for (int i = 0; i < capacity; ++i) 
            if (array[i] && array[i] != dummy) 
                delete array[i];

        delete[] array;
        delete dummy;
    }

    int HashCode(const TKey& key) const
    {
        //параметр шаблона для хеша
        return std::hash<TKey>{}(key) % capacity;
    }

    void Add(const TKey& key, const TValue& value) override
    {
        if (size >= capacity * 0.7) 
            Resize();

        HashNode<TKey, TValue>* temp = new HashNode<TKey, TValue>(key, value);
        int hashIndex = HashCode(key);

        while (array[hashIndex] != nullptr && array[hashIndex] != dummy && array[hashIndex]->key != key)
            hashIndex = (hashIndex + 1) % capacity;

        if (array[hashIndex] == nullptr || array[hashIndex] == dummy)
            size++;
        else
            delete array[hashIndex];

        array[hashIndex] = temp;
    }

    void Remove(const TKey& key) override
    {
        int hashIndex = HashCode(key);

        while (array[hashIndex] != nullptr) 
        {
            if (array[hashIndex]->key == key) 
            {
                array[hashIndex] = dummy;
                size--;
            }

            hashIndex = (hashIndex + 1) % capacity;
        }
    }

    std::optional<TValue> GetValue(const TKey& key) const override
    {
        int hashIndex = HashCode(key);
        int counter = 0;

        while (array[hashIndex] != nullptr) 
        {
            if (counter++ > capacity)
                return std::nullopt;

            if (array[hashIndex]->key == key)
                return array[hashIndex]->value;

            hashIndex = (hashIndex + 1) % capacity;
        }

        return std::nullopt;
    }

    const HashNode<TKey, TValue>* GetNodeAt(int index) const
    {
        if (index >= 0 && index < capacity)
            return array[index];

        return nullptr;
    }

    bool ContainsKey(const TKey& key) const override
    {
        if (GetValue(key))
            return true;
       
        return false;
    }

    int GetCount() const override
    {
        return size;
    }

    int GetCapacity() const override
    {
        return capacity;
    }

    bool IsEmpty() const 
    {
        return size == 0;
    }

    void Display() const 
    {
        for (int i = 0; i < capacity; i++) 
        {
            if (array[i] != nullptr && array[i] != dummy) 
            {
                std::cout << "key = " << array[i]->key << "  value = ";
                PrintValue(array[i]->value, std::cout);
                std::cout << std::endl;
            }
        }
    }
};

#endif