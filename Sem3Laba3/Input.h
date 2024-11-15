#ifndef INPUT_H
#define INPUT_H

#include <iostream>
#include <string>

template<typename T>
void ReadVariable(T& variable, const std::string& message)
{
	std::cout << message << "\n";
	std::cin >> variable;
}

#endif