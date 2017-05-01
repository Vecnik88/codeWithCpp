// Created by Vecnik88

/* Сделано с использованием прямой адресации */

/*
                                    Телефонная книга

                        Реализовать структуру данных, эффективно обрабатывающую запросы
                        вида add number name, del number и find number.
                        Вход. Последовательность запросов вида add number
                        name, del number и find number, где number — те-
                        лефонный номер, содержащий не более семи знаков,
                        а name — короткая строка.
                        Выход. Для каждого запроса find name выведите соот-
                        ветствующий телефонный номер или сообщите, что такой
                        записи нет.
                        Цель в данной задаче — реализовать простую те-
                        лефонную книгу, поддерживающую три следующих
                        типа запросов. С указанными ограничениями дан-
                        ная задача может быть решена с использованием
                        таблицы с прямой адресацией.
                        • add number name: добавить запись с именем name и телефон-
                        ным номером number. Если запись с таким телефонным номе-
                        ром уже есть, нужно заменить в ней имя на name.
                        • del number: удалить запись с соответствующим телефонным
                        номером. Если такой записи нет, ничего не делать.
                        • find number: найти имя записи с телефонным номером
                        number. Если запись с таким номером есть, вывести имя. В про-
                        тивном случае вывести «not found» (без кавычек).
                        Формат входа. Первая строка содержит число запросов n. Каждая из
                        следующих n строк задаёт запрос в одном из трёх описанных вы-
                        ше форматов.
                        Формат выхода. Для каждого запроса find выведите в отдельной
                        строке либо имя, либо «not found».
                        28
                        Ограничения. 1 ≤ n ≤ 105
                        . Телефонные номера содержат не более
                        семи цифр и не содержат ведущих нулей. Имена содержат только
                        буквы латинского алфавита, не являются пустыми строками и
                        имеют длину не больше 15. Гарантируется, что среди имён не
                        встречается строка «not found».
                        Пример.
                        Вход:
                        12
                        add 911 police
                        add 76213 Mom
                        add 17239 Bob
                        find 76213
                        find 910
                        find 911
                        del 910
                        del 911
                        find 911
                        find 76213
                        add 76213 daddy
                        find 76213
                        Выход:
                        Mom
                        not found
                        police
                        not found
                        Mom
                        daddy
*/

#include <string>
#include <vector>
#include <sstream>
#include <iostream>

using namespace std;

void add_number(vector<string>& array, string &str);        // <---. добавляет строку в массив
void find_number(vector<string>& array, string& str);       // <---. ищет по номеру в массиве строку и выводит ее на экран
void delete_number(vector<string>& array, string& str);     // <---. удаляет строку из массива по номеру

int main()
{
    int n = 0;                                      // <---. количество запросов
    string str = "";                                // <---. строка для ввода команды с данными
    cin >> n;
    vector<string>array(10000000, "");

    while(n >= 0)
    {
        getline(cin, str);
        switch (str[0])
        {
        case 'a':
            add_number(array, str);
            break;

        case 'f':
            find_number(array, str);
            break;

        case 'd':
            delete_number(array, str);
            break;
        }
        --n;
    }

    return 0;
}

void add_number(vector<string> &array, string& str)
{
    unsigned i = 4;
    unsigned number = 0;
    string str1 = "";

    while(str[i] != ' ')
    {
        str1 += str[i];
        ++i;
    }
    ++i;

    istringstream is(str1);
    is >> number;

    str1 = "";

    while(i != str.length())
    {
        str1 += str[i];
        ++i;
    }
    array[number] = str1;
}

void find_number(vector<string>& array, string& str)
{
    unsigned i = 5, number = 0;
    string str1 = "";

    while(i != str.length())
    {
        str1 += str[i];
        ++i;
    }
    istringstream is(str1);
    is >> number;

    if(array[number] == "")
        cout << "not found" << endl;

    else
        cout << array[number] << endl;
}

void delete_number(vector<string>& array, string& str)
{
    string str1 = "";
    unsigned i = 4, number = 0;

    while(i != str.length())
    {
        str1 += str[i];
        ++i;
    }
    istringstream is(str1);

    is >> number;

    array[number] = "";
}
