// Тестовое задание 1.03.2017

// Исправлено 2.03.2017 - изменен алгоритм поиска
//            4.03.2017 - изменен алгоритм поиска, добавлена возможность сортировки и слияние одинаковых диапазонов
/*
        В одном из наших продуктов реализован DHCP-сервер, который выдаёт конечным пользователям IP-адреса
        из пула. Пул представляет собой набор диапазонов адресов IPv4. При изменении настроек пула
        необходимо получить диапазоны IP-адресов, которые входили в старый пул, но не входят в новый,
        чтобы пометить их в системе как устаревшие. Реализуйте функцию, которая будет вычислять устаревшие
        диапазоны, сравнивая новый и старый пул. Предложите тест-кейсы, позволяющие убедиться в корректности
        работы алгоритма.
        Используйте следующие типы для IP-адресов, диапазонов и пулов:
        using IPAddress = uint32_t; // Адрес IPv4 представлен целочисленным типом uint32_t
        using Range = std::pair<IPAddress, IPAddress>;
        Диапазон IP-адресов, границы включены
        using Pool = ? // предложите оптимальный STL-котейнер для хранения диапазонов IP-адресов (Range)
        Диапазоны IP-адресов в пуле могут пересекаться. Порядок их расположения в пуле - случайный.
        Функция, вычисляющая разницу между старым и новым пулами:
        `old_pool` - старый пул IP-адресов
        `new_pool` - новый пул IP-адресов
        return value - пул диапазонов "устаревших" IP-адресов
        Pool find_diff(const Pool& old_pool, const Pool& new_pool)
        {
            Pool result;
            // TODO: реализуйте алгоритм, описанный в условии задачи
            // ...
            return result;
        }
        Проще говоря
        old_pool {{1,10},{12,15}}, new_pool {{5,9}}, result {{1,4},{12,15}}
        old_pool {{1,10}}, new_pool {{5,15}}, result {{1,4}}
        old_pool {{1, 10}, {11,19}}, new_pool {{1,19}}, result {{}}
        old_pool {{0, 3}, {16, 18} ,{4, 5}}, new_pool {{15, 16} }, result{{0, 3},{4, 5}, {17, 18} }
        *читайте внимательнее задание, функция "find_diff" и прочий синтаксис необходимо соблюсти для автоматических тестов.
        Pool find_diff(const Pool& old_pool, const Pool& new_pool)
        испольхование функции в одном из тестов
        { // Overlapping at higher end only:
            Pool old_pool = {{10, 17}};
            Pool new_pool = {{15, 20}, {24, 30}};
            auto expired = find_diff(old_pool, new_pool);
            assert(eq(expired, {{10, 14}}));
        }
*/

/* Логика решения:

    1: старый пул полностью входит в новый
    2: начало старого входит в новый, а конец нет
    3: конец входит в новый, а начало нет
    4: новый пул - это середина старого
    5: поскольку в задании указано
       "Диапазоны IP-адресов в пуле могут пересекаться. Порядок их расположения в пуле - случайный."
       то сортировка результируещего массива и приведение его к общему вида без пересечений не производится
    6: в задании используется контейнер list, вместо vector и set - поскольку у вектора большие затраты при
       резервировании новой памяти, а сет использовать в данной концепции не стоит.
*/

#include <iostream>
#include <list>
#include <cassert>
#include <limits>

using IPAddress = uint32_t;                                 // <---. объявление прототипов используя С++11
using Range = std::pair<IPAddress, IPAddress>;              // <---. объявление прототипов используя С++11
using Pool = std::list<Range>;                              // <---. объявление прототипов используя С++11

Pool find_diff(const Pool& old_pool, const Pool& new_pool);
bool eq(const Pool& expired, const Pool& expected);
void print_pool(const Pool& pool);
Pool sortAndMerge(Pool& pool);

bool mycomparison (const Range& a, const Range& b)          // <---. предикат
{ return ( a.first < b.first ); }

int main()
{
    // ### Test ###

    const uint32_t max = std::numeric_limits<uint32_t>::max();
    { // похожие диаппазоны, много пересечений, равные первые и последние элементы
    Pool oldp {{23,45}, {134,156}, {234,256}, {334,356}, {434,456}, {4,6}, {3,5}, {500,563}, {334,536},{134,535}, {34,56}, {900,956},{1001,1002},{5000,5002}};
    oldp = sortAndMerge(oldp);
    Pool oldp1 {{23,45}, {134,156}, {234,256}, {334,356}, {434,456}, {4,6}, {3,5}, {500,563}, {334,536},{134,135}, {34,56}, {900,956},{980,1001},{5000,5001}};
    oldp1 = sortAndMerge(oldp1);
    auto expired = find_diff(oldp, oldp1);
    
    expired.sort(mycomparison); // <---. выводится неотсортированным, можно отсортировать для удобства проверки результатов

    assert(eq(expired, {{157, 233}, {257, 333}, {1002,1002}, {5002, 5002}}));
    print_pool(expired);
    }
    { // Empty pools:
        auto expired = find_diff({}, {});
        assert(eq(expired, {}));
    }
    { // Empty new_pool:
        auto expired = find_diff({{10, 20}}, {});
        assert(eq(expired, {{10, 20}}));
        print_pool(expired);
    }
    { // Empty old_pool
        auto expired = find_diff({},{{12,32}});
        assert(eq(expired, {}));
        print_pool(expired);
    }
    { // No crossing:
        Pool old_pool = {{10, 15}};
        Pool new_pool = {{5, 8}, {20, 21}};
        old_pool = sortAndMerge(old_pool);
        new_pool = sortAndMerge(new_pool);
        auto expired = find_diff(old_pool, new_pool);

        expired.sort(mycomparison); // <---. выводится неотсортированным, можно отсортировать для удобства проверки результатов

        assert(eq(expired, {{10, 15}}));
        print_pool(expired);
    }
    { // crossing
        Pool old_pool {{1, 10}, {11,19}, {19,40}};      // <---. должен получиться 1 диапазон
        Pool new_pool {{12,19}};
        old_pool = sortAndMerge(old_pool);
        new_pool = sortAndMerge(new_pool);
        auto expired = find_diff(old_pool, new_pool);

        expired.sort(mycomparison); // <---. выводится неотсортированным, можно отсортировать для удобства проверки результатов

        assert(eq(expired, {{1,11}, {20,40}}));
        print_pool(expired);
    }
    { // crossing
        Pool old_pool {{55,90}};
        Pool new_pool {{15, 16}, {15,16}, {4,5}, {56,90}};
        old_pool = sortAndMerge(old_pool);
        new_pool = sortAndMerge(new_pool);
        auto expired = find_diff(old_pool, new_pool);

        expired.sort(mycomparison); // <---. выводится неотсортированным, можно отсортировать для удобства проверки результатов

        assert(eq(expired, {{55,55}}));
        print_pool(expired);
    }
    { // Overlapping at higher end only:
        Pool old_pool = {{10, 17}};
        Pool new_pool = {{15, 20}, {24, 30}};
        old_pool = sortAndMerge(old_pool);
        new_pool = sortAndMerge(new_pool);
        auto expired = find_diff(old_pool, new_pool);

        expired.sort(mycomparison); // <---. выводится неотсортированным, можно отсортировать для удобства проверки результатов

        assert(eq(expired, {{10, 14}}));
        print_pool(expired);
    }
    {
        Pool old_pool = {{22,32},{18, 33}};
        Pool new_pool = {{15, 20}, {24, 30}};
        old_pool = sortAndMerge(old_pool);
        new_pool = sortAndMerge(new_pool);
        auto expired = find_diff(old_pool, new_pool);

        expired.sort(mycomparison); // <---. выводится неотсортированным, можно отсортировать для удобства проверки результатов

        assert(eq(expired, {{21, 23}, {31,33}}));
        print_pool(expired);
    }
    {
        Pool old_pool = {{22,32},{18, 33},{18,33}, {23,30}, {12,45}};
        Pool new_pool = {{15, 20}, {4, 120}};
        old_pool = sortAndMerge(old_pool);
        new_pool = sortAndMerge(new_pool);
        auto expired = find_diff(old_pool, new_pool);
        assert(eq(expired, {}));
        print_pool(expired);
    }
    {
        Pool old_pool = {{2,32},{18, 3159},{7565,7888}, {23,30}, {2,2}};
        Pool new_pool = {{15, 20}, {4, 754}};
        old_pool = sortAndMerge(old_pool);
        new_pool = sortAndMerge(new_pool);
        auto expired = find_diff(old_pool, new_pool);

        expired.sort(mycomparison); // <---. выводится неотсортированным, можно отсортировать для удобства проверки результатов

        assert(eq(expired, {{2,3},{755,3159}, {7565,7888}}));
        print_pool(expired);
    }
}

// algorithm search old pool
Pool find_diff(const Pool& old_pool, const Pool& new_pool)
{
    Pool result;

    for(const auto& old_p : old_pool)                               // <---. C++11, семантика питона, обращаемся к каждому эл-ту в контейнере
    {
        result.push_front({old_p.first, old_p.second});             // <---. заносим элемент вначало
        auto first_element_result = result.begin();                 // <---. создаем итератор на первый элемент

        for(auto new_p = new_pool.begin(); new_p != new_pool.end(); ++new_p) // <---. пока не достигнем конца нового пула
        {
            if(first_element_result->first >= new_p->first)
            {
                if(first_element_result->second <= new_p->second)
                {
                    result.pop_front();
                    break;
                }

                else if(first_element_result->first > new_p->second)         // <---. если превышает диапазон
                {
                    continue;
                }
                else    // <---. if first > first.old, but first < second.old and second > second.old
                {
                    first_element_result->first = (new_p->second +1);
                }
            }

            if(first_element_result->first < new_p->first)
            {
                if(first_element_result->second < new_p->first)
                {
                    //continue;
                    break;
                }
                else if(first_element_result->second <= new_p->second)
                    {
                        first_element_result->second = (new_p->first - 1);
                    }
                else    // <---. if first < first.old and second > second.old
                {
                    result.insert(next(first_element_result), {first_element_result->first, (new_p->first-1)});
                    first_element_result->first = (new_p->second + 1);

                    // используем рекурсию, если новый пул разбивает наш старый диапазон на 2
                    result = find_diff(result, new_pool);
                }
            }
        }
    }
   return result;
}

// ### sorting and merge pool ###
Pool sortAndMerge(Pool& pool)               // <---. может изменить передаваемый контейнер
{
    if(pool.size() > 1)                     // <---. если в пуле больше 1 элемента, иначе нет смысла
    {
        pool.sort(mycomparison);            // <---. можно использовать также stable_sort ###

        Pool mergeContainer;

        auto it1 = pool.begin();            // <---. начало списка
        auto it2 = next(pool.begin());      // <---. следующий элемент

        while(it2!=pool.end())
        {
            //{1,20}, {1,43}, {1,43}, {2,43}, {5,43}, {9,56}, {12,43}, {12,43}, {12,463}, {20,456}, {22,43}
            if(it1->second > it2->first)
            {
                if(it1->second >= it2->second)
                {
                    ++it2;
                }
                else
                {
                    it1->second = it2->second;
                    ++it2;                          // <---. так работает быстрее
                }
            }
            else
            {
                if(it1->second+1 == it2->first || it1->second == it2->first)
                {
                    it1->second = it2->second;
                    ++it2;
                }
                else
                {
                    mergeContainer.push_back({it1->first, it1->second});
                    it1 = it2;
                    ++it2;
                }
            }

        }
        mergeContainer.push_back({it1->first, it1->second});
        return mergeContainer;
    }
    else
        return pool;
}
// ### function for test ###

// enter pair for display
void print_range(const Range& range)
{
    std::cout << "[" << range.first << "; " << range.second << "] ";
}

// enter container pool for display
void print_pool(const Pool& pool)
{
    for (const auto& range: pool) {
        print_range(range);
    }
    std::cout << std::endl;
}

// return true if expired = expected, else false
bool eq(const Pool& expired, const Pool& expected)
{
    if (expired == expected) {
        return true;
    } else {
        std::cout << "Got:" << std::endl;
        print_pool(expired);
        std::cout << "Expected:" << std::endl;
        print_pool(expected);
        std::cout << std::endl;
        return false;
    }
}
