//Created by Vecnik88
/*
                    Поиск образца в тексте

    Найти все вхождения строки Pattern в строку Text.
    Вход. Строки Pattern и Text.
    Выход. Все индексы i строки Text, начиная с которых строка Pattern входит в Text:

    Text[i..i + |Pattern| − 1] = Pattern.
    Реализуйте алгоритм Карпа–Рабина.
    Формат входа. Образец Pattern и текст Text.
    Формат выхода. Индексы вхождений строки
    Pattern в строку Text в возрастающем порядке, используя индексацию с нуля.
    Ограничения. 1 ≤ |Pattern| ≤ |Text| ≤ 5 · 105

    Суммарная длина всех вхождений образца в текста не превосходит 108.
    Обе строки содержат буквы латинского алфавита.

Пример.
    Вход:
    aba
    abacaba
    Выход:
    0 4
    Образец aba входит в позициях 0 (abacaba) и 4 (abacaba) в текст abacaba.

Пример.
    Вход:
    Test
    testTesttesT
    Выход:
    4
    36
    Пример.
    Вход:
    aaaaa
    baaaaaaa
    Выход:
    1 2 3
*/

#include <list>
#include <string>
#include <iostream>

using namespace std;

int main()
{
    bool alignment = true;

    string pattern = "";
    string text = "";

    uint32_t pattern_size = 0;
    uint32_t text_size = 0;

    getline(cin, pattern);
    getline(cin, text);

    uint32_t pattern_str_size = pattern.length();
    uint32_t i = 0;

    while(i < pattern_str_size)
    {
        pattern_size += pattern[i];
        text_size += text[i];
        ++i;
    }

    list<uint32_t>hashTable;

    hashTable.push_back(text_size);

    for(; i < text.length(); ++i)
    {
        text_size = text_size - text[i-pattern_str_size] + text[i];
        hashTable.push_back(text_size);
    }
    uint32_t value = 0;

    for(auto iter = hashTable.begin(); iter != hashTable.end(); ++iter)
    {
        if(*iter == pattern_size)
        {
              uint32_t k = value;
              uint32_t j = 0;

              alignment = true;

              while(j < pattern_str_size)
              {
                  if(pattern[j] != text[k++])
                  {
                      alignment = false;
                      break;
                  }
                  ++j;
              }
              if(alignment)
              {
                  cout << value << " ";
              }
        }
        ++value;
    }

    return 0;
}
