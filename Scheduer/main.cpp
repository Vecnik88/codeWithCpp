// Created by Vecnik88
/*
    Попробуйте решить задачу в общем случае. В первой строке вам дается число задач N.
    В следующей строке идет описание задач, для каждой задачи вам дана ее продолжительность - Ti
(где i - это номер задачи, от 0 до N−1 не включительно). На выход вам требуется вывести номера задач
(задачи нумеруются с 0) в порядке, который минимизирует среднее время ожидания завершения задачи,
как это было объяснено ранее.

Гарантируется, что 0<N≤10000 и 0<Ti≤10000 и все числа целые.
*/

#include <set>
#include <iostream>

using id_process = uint16_t;
using time_process = uint16_t;
using Range = std::pair<time_process, id_process>;

int main()
{
    uint16_t amt_task = 0;
    uint16_t time_task = 0;
    std::cin >> amt_task;
    std::set<Range> scheduer;

    for(uint16_t i = 0; i < amt_task; ++i)
    {
        std::cin >> time_task;
        scheduer.insert({time_task, i});
    }

    for(auto iter = scheduer.begin(); iter != scheduer.end(); ++iter)
        std::cout << iter->second << " ";

    return 0;
}
