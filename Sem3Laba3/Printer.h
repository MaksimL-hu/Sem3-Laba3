#ifndef PRINTER_H
#define PRINTER_H

#include <iostream>
#include <vector>

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

#endif