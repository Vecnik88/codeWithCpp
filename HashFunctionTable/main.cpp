// Created by Vecnik88
/*
                    Хеширование цепочками

    Хеширование цепочками — один из наиболее популярных методов реализации
хеш-таблиц на практике. Ваша цель в данной задаче — реализовать такую схему,
используя таблицу с m ячейками и полиномиальной хеш-функцией на строках.

Ваша программа должна поддерживать следующие типы запросов:

    • add string: добавить строку string в таблицу. Если такая
    строка уже есть, проигнорировать запрос;
    • del string: удалить строку string из таблицы. Если такой
    строки нет, проигнорировать запрос;
    • find string: вывести «yes» или «no» в зависимости от того,
    есть в таблице строка string или нет;
    • check i: вывести i-й список (используя пробел в качестве раз-
    делителя); если i-й список пуст, вывести пустую строку.

При добавлении строки в цепочку, строка должна добавляться в начало цепочки.

    Формат входа. Первая строка размер хеш-таблицы m. Следующая
строка содержит количество запросов n. Каждая из последую-
щих n строк содержит запрос одного из перечисленных выше
четырёх типов.

    Формат выхода. Для каждого из запросов типа find и check выве-
дите результат в отдельной строке.

Ограничения. 1 ≤ n ≤ 105; 5 ≤ m ≤ n. Все строки имеют длину
от одного до пятнадцати и содержат только буквы латинского
алфавита.

Пример.
Вход:
5
12
add world
add HellO
check 4
find World
find world
del world
check 4
del HellO
add luck
add GooD
check 2
del good
Выход:
HellO world
no
yes
HellO
GooD luck
*/

#include <cmath>
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <forward_list>

using namespace std;

uint64_t hashFunction(const string& str, const unsigned &m);     // <---. хэш-функция

void check_str(vector<forward_list<string>>&, const string&);                   // <---. проверяет i-тый список таблицы
void del_str(vector<forward_list<string>>&, const string&, const unsigned&);    // <---. удаляет строку
void add_str(vector<forward_list<string>>&, const string&, const unsigned&);    // <---. добавляет строку
void find_str(vector<forward_list<string>>&, const string&, const unsigned&);   // <---. поиск строки

int main()
{
    uint32_t n = 0;                         // <---. количество запросов
    uint32_t sizeHashTable = 0;             // <---. размер хэш-таблицы
    string str = "";                        // <---. рабочая строка

    cin >> sizeHashTable >> n;
    cin.ignore();

    vector<forward_list<string>>table(sizeHashTable);

    while(n > 0)
    {
        getline(cin, str);

        switch(str[0])
        {
        case 'a':
            add_str(table, str, sizeHashTable);
            break;

        case 'f':
            find_str(table, str, sizeHashTable);
            break;

        case 'c':
            check_str(table, str);
            break;

        case 'd':
            del_str(table, str, sizeHashTable);
            break;
        }

        --n;
    }

    return 0;
}

void find_str(vector<forward_list<string>>&table, const string& str, const unsigned& sizeHashTable)
{
    uint64_t number = 0;
    uint32_t i = 5;
    string str_work = "";

    while(i < str.length())
        str_work += str[i++];

    number = hashFunction(str_work, sizeHashTable);

    for(auto iter = table[number].begin(); iter != table[number].end(); ++iter)
    {
        if(str_work == *iter)
        {
            cout << "yes" << endl;
            return;
        }
    }

    cout << "no" << endl;
}

void add_str(vector<forward_list<string>>&table, const string& str, const unsigned& sizeHashTable)
{
    uint64_t number = 0;
    uint32_t i = 4;
    string str_work = "";

    while(i < str.length())
        str_work += str[i++];

    number = hashFunction(str_work, sizeHashTable);

    for(auto iter = table[number].begin(); iter != table[number].end(); ++iter)
    {
        if(str_work == *iter)
            return;
    }

    table[number].push_front(str_work);
}

void check_str(vector<forward_list<string>>&table, const string& str)
{
    string str_work = "";
    uint32_t i = 6;
    uint64_t number = 0;

    while(i < str.length())
        str_work += str[i++];

    istringstream is(str_work);
    is >> number;

    if(table[number].empty())
        cout << "\n";

    else
    {
        for(auto iter = table[number].begin(); iter != table[number].end(); ++iter)
            cout << *iter << " ";

        cout << endl;
    }
}

void del_str(vector<forward_list<string>>&table, const string& str, const unsigned& sizeHashTable)
{
    uint64_t number = 0;
    uint32_t i = 4;
    string str_work = "";

    while(i < str.length())
        str_work += str[i++];

    number = hashFunction(str_work, sizeHashTable);

    table[number].remove(str_work);
}

uint64_t hashFunction(const string& str, const unsigned &sizeHashTable)
{ 
    const uint64_t mod_index = 1000000007;
    const uint64_t pow_index = 263;

    uint64_t result = 0;
    uint64_t pow = 1;

    for (size_t i = 0; i < str.length(); ++i)
    {
        uint64_t result_v1 = (uint64_t(str[i]) * pow) % mod_index;
        result = (result + result_v1) % mod_index;
        pow = (pow * pow_index) % mod_index;
     }

    result %= mod_index;
    result %= sizeHashTable;

    return result;
}
