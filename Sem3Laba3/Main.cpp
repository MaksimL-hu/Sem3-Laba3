﻿#include "HashTable.h"
#include "UserMenu.h"

int main()
{
    OpenMenu();
    //таблица на 10000, положить 7000 эл. 10 раз: удалить 1000(для каждой итерации для разных ключей) и добавить 1000. Посчитать время доступа для хранящихся эл
    HashTable<int, int> a(10000);
}