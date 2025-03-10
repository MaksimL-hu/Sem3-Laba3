#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#include "Sequence.h"

template <class T>
class DynamicArray : public Sequence<T>
{
private:
    T* data;
    int size;

    void Resize(int newSize)
    {
        T* newData = new T[newSize];

        int minSize = (newSize < size) ? newSize : size;

        for (int i = 0; i < minSize; ++i)
        {
            newData[i] = data[i];
        }

        delete[] data;
        data = newData;
        size = newSize;
    }

public:
    class DynamicArrayIterator : public Sequence<T>::Iterator {
    private:
        T* current;

    public:
        DynamicArrayIterator(T* current) : current(current) {}

        bool operator==(const typename Sequence<T>::Iterator& other) const override
        {
            const DynamicArrayIterator* otherIterator = dynamic_cast<const DynamicArrayIterator*>(&other);
            return otherIterator && current == otherIterator->current;
        }

        bool operator!=(const typename Sequence<T>::Iterator& other) const override
        {
            return !(*this == other);
        }

        T& operator*() override
        {
            return *current;
        }

        typename Sequence<T>::Iterator& operator++() override
        {
            current++;

            return *this;
        }
    };

    typename Sequence<T>::Iterator* ToBegin() override
    {
        return new DynamicArrayIterator(data);
    }

    typename Sequence<T>::Iterator* ToEnd() override
    {
        return new DynamicArrayIterator(data + size);
    }

    DynamicArray(T* items, int size)
    {
        this->size = size;
        data = new T[size];

        for (int i = 0; i < size; ++i)
        {
            Set(i, items[i]);
        }
    }

    DynamicArray(T example, int size)
    {
        this->size = size;
        data = new T[size];

        for (int i = 0; i < size; ++i)
        {
            Set(i, example);
        }
    }

    DynamicArray(int size = 0)
    {
        this->size = size;
        data = new T[size];
    }

    DynamicArray(const DynamicArray& other)
    {
        size = other.size;
        data = new T[size];

        for (int i = 0; i < size; ++i)
            data[i] = other.data[i];
    }

    DynamicArray& operator=(const DynamicArray& other)
    {
        if (this == &other)
            return *this;

        delete[] data;

        size = other.size;
        data = new T[size];

        for (int i = 0; i < size; ++i)
            data[i] = other.data[i];

        return *this;
    }

    ~DynamicArray()
    {
        if (data)
            delete[] data;
    }

    T& operator[](int index)
    {
        return data[index];
    }

    T& operator[](int index) const
    {
        return data[index];
    }

    T& GetFirstElement() override
    {
        return GetElement(0);
    }

    T& GetLastElement() override
    {
        return GetElement(size - 1);
    }

    T& GetElement(int index) override
    {
        return data[index];
    }

    void Swap(T& ConstainsIndex, T& GetKeyByIndex) override
    {
        T temp = ConstainsIndex;
        ConstainsIndex = GetKeyByIndex;
        GetKeyByIndex = temp;
    }

    void Set(int index, T value) override
    {
        data[index] = value;
    }

    DynamicArray<T>* GetSubsequence(int startIndex, int endIndex) override
    {
        int length;

        if (endIndex > size)
        {
            length = size - startIndex;
        }
        else
        {
            length = endIndex - startIndex + 1;

            if (startIndex == 0)
            {
                length -= 1;
            }
        }

        T* items = new T[length];

        for (int i = 0; i < length; i++)
        {
            items[i] = GetElement(startIndex + i);
        }

        return new DynamicArray<T>(items, length);
    }

    int GetLength() const override
    {
        return size;
    }

    void Append(T data) override
    {
        InsertAt(data, size);
    }

    void Append(T* data, int dataSize) override
    {
        int oldSize = size;

        Resize(size + dataSize);

        for (int i = oldSize; i < oldSize + dataSize; i++)
        {
            Set(i, data[i - oldSize]);
        }
    }

    void Prepend(T data) override
    {
        InsertAt(data, 0);
    }

    void InsertAt(T data, int index) override
    {
        Resize(size + 1);

        for (int i = size - 1; i > index; i--)
        {
            Set(i, GetElement(i - 1));
        }

        Set(index, data);
    }

    void Union(Sequence<T>* dynamicArray) override
    {
        int oldSize = size;

        for (int i = 0; i < dynamicArray->GetLength(); i++)
        {
            Append(dynamicArray->GetElement(i));
        }
    }
};

#endif