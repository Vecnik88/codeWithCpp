// ### Created by Vecnik88 15.02.2017

/*                          ТЕСТОВОЕ ЗАДАНИЕ С++

    Результат должен быть в виде проекта, компилироваться и работать под Visual Studio 2013
(в других IDE - по согласованию).

Необходимо:

        1.заполнить случайными числами от 1 до 9 значения контейнеров
        vector[i] и map[i];

        2.удалить случайное число элементов (не более 15) в каждом
        контейнере;

        3.после этого провести синхронизацию, чтобы в vector и map
        остались только имеющиеся в обоих контейнерах элементы
        (дубликаты не удалять).

*/

#pragma once

#include <iostream>
#include <algorithm>
#include <map>
#include <vector>
#include <random>
#include <ctime>

using namespace std;

int rand_value(int n);                              // <---. генерирует случайные числа в диапазоне от 1 до n
int input_size_cont();                              // <---. запрашивает размер контейнеров, проверяет чтобы размер был >15

template <typename T>
void display_vector(const T& cont)                  // <---. выводит на экран элементы в контейнере вектор
{
    for(auto i = cont.begin(); i != cont.end(); ++i)
    {
        cout << *i << ' ';
    }
    cout << '\n';
}

template <typename T>
void display_map(const T& cont)                     // <---. выводит на экран элементы в контейнере map
{
    for(auto i = cont.begin(); i != cont.end(); ++i)
    {
        cout << i->first << " -> " << i->second << endl;
    }
}

template<typename T>                                        // <---. создает контейнер с указанным количеством элементов
void generate_container(T& c, int n)                        //       с случайными числами
{
    for(size_t i = 0; i < n; ++i)
        c[i] = rand_value(9);
}
template<typename T>
void del_random_el_vec(T& cont, int size_container)         // <---. удаляет элементы случайным образом
{                                                           //       но не более 15
    for(int i = 0; i < rand_value(15); ++i)
    {
        // генерируем элемент который нужно удалить случайным образом

        cont.erase(cont.begin()+(rand_value(size_container--) - 1));
    }
}

template<typename T>
void del_random_el_map(T& cont, int size_container)         // <---. удаляем элемент в контейнере map случайным образом
{
auto iter = cont.begin();
    for(int i = 0; i < rand_value(15); ++i)
    {
         advance(iter, (rand_value(size_container--) - 1));
         cont.erase(iter);
         iter = cont.begin();
    }
}

template <typename T1, typename T2>
void org_conteiner(T1& cont_map, T2& cont_vec)              // <---. уравниваем количество элементов в двух контейнерах
{                                                           // <---. удаляем лишние последние элементы
    int k = 0;
    k = (cont_map.size() > cont_vec.size())?(cont_map.size() > cont_vec.size()):(cont_vec.size()-cont_map.size());

    if(cont_map.size() > cont_vec.size())
    {
        auto iter = cont_map.end();
        advance(iter,(-k));
        cont_map.erase(iter, cont_map.end());
    }
    else
    {
        auto iter = cont_vec.end();
        advance(iter,(-k));
        cont_vec.erase(iter, cont_vec.end());
    }
}

template<typename T1, typename T2>
void func_sort_result(T1& cont_vec, T2& cont_map, T2& new_cont_map) // <<< сортируем, удаляем, получаем конечные результаты
{
auto itr = cont_map.begin();

for(size_t i = 0; i < cont_map.size(); ++i)             // <---. если элементы не равны, то заменяем их значения на 0
{
    if(cont_vec[i]!=itr->second)
    {
        cont_vec[i] = 0;
        cont_map[itr->first] = 0;
    }
    ++itr;
}

cont_vec.erase(remove(cont_vec.begin(), cont_vec.end(), 0), cont_vec.end());

itr = cont_map.begin();

for(size_t i = 0; i < cont_map.size(); ++i)
{
    if(cont_map[itr->first]!=0)
    {
        new_cont_map[itr->first] = itr->second;
    }
    ++itr;
}
}

template<typename T1, typename T2>
void display_finish_result (const T1& cont_vec, const T2& new_cont_map) // если контейнеры, не пусты - выводим результат
{
if(new_cont_map.empty())
    cout << "Conteiner map is empty" << endl;
else
    display_map(new_cont_map);

if(cont_vec.empty())
    cout << "Conteiner map is empty" << endl;
else
    display_vector(cont_vec);
}

