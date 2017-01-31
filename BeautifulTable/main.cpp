// ### multiplication table ### Created by Vecnik88
/*
    Красивое оформление таблицы на языке С++

    Beautiful design table in the language С++
*/

#include <iostream>
#include <iomanip>
#include <cctype>

using namespace std;

int main()
{
  int table = 0;                                //<---. размер таблицы
  const int table_min = 2;                      //<---. минимальный размер
  const int table_max = 12;                     //<---. максимальный размер
  char ch = 0;                                  //<---. ответ

  do {
    cout << endl
         << "What size table would you like ("
         << table_min << " to " << table_max << ")? ";
    cin >> table;                               // ####### размерность таблицы
    cout << endl;

    // ограничение количества элементов
    if(table < table_min || table > table_max) {
      cout << "Invalid table size entered. Program terminated."
           << endl;
      exit(1);
    }

    // создаем верхнюю строку таблицы

    cout << "     |";
    for(int i = 1 ; i <= table ; i++)
      cout << " " << setw(3) << i << " |";
    cout << endl;

    for(int i = 0 ; i <= table ; i++)           //<---. создаем разделитель строк
      cout << "------";
    cout << endl;

    for(int i = 1 ; i <= table ; i++) {         //<---. итерация по строкам
      cout << " " << setw(3) << i << " |";

      // ### значения строки

      for(int j = 1 ; j <= table ; j++)
        cout << " " << setw(3) << i*j << " |";
      cout << endl;
    }

    // ### Вы хотите еще одну таблицу? Если n, то выход из цикла

    cout << endl << "Do you want another table (y or n)? ";
    cin >> ch;
    cout << endl;
  } while(tolower(ch) == 'y');

  return 0;
}

