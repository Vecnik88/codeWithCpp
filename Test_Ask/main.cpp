// Тестовое задание 1.03.2017

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
#include <iostream>
#include <list>

using namespace std;

// шаблонная ф-ция, выводящая результирующий вектор на экран
template <typename T>
void display_result(const T& result)
{

    for(auto i = result.begin(); i != result.end(); ++i)
        cout << i->first << " - " << i->second << endl;

    cout << endl;
}

using IPAddress = uint32_t;                                 // <---. объявление прототипов используя С++11
using Range = std::pair<IPAddress, IPAddress>;              // <---. объявление прототипов используя С++11
using Pool = list<Range>;                                   // <---. объявление прототипов используя С++11

/* Логика:

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

Pool find_diff(const Pool& old_pool, const Pool& new_pool)
{
    Pool result;
    for(const auto& old_p : old_pool)
    {
        for(const auto& new_p : new_pool)
        {
            if(old_p.second < new_p.first)
            {
                result.push_back({old_p.first, old_p.second});
                break;
            }

            // ### если диапазон нового пересекает старый
            if(old_p.first >= new_p.first)
            {
                if(old_p.second <= new_p.second)
                    break;

                else
                {
                    result.push_back({(new_p.second + 1),old_p.second});
                    break;
                }
            }

            if(old_p.first < new_p.first)
            {
                if(old_p.second <= new_p.second)
                {
                    result.push_back({old_p.first, (old_p.first+(new_p.first - old_p.first - 1))});
                    break;
                }
                else
                    {
                        result.push_back({old_p.first, (old_p.first+(new_p.first - old_p.first-1))});
                        result.push_back({(old_p.second-new_p.second),old_p.second});
                        break;
                    }
            }
        }
    }
   return result;
}

int main()
{
    Pool old_pool {{1, 10}, {11,19}}, new_pool {{1,19}};                    // result {{}}
    Pool old_pool1 {{0, 3}, {16, 18} ,{4, 5}}, new_pool1 {{15, 16} };       // result{{0, 3},{4, 5}, {17, 18}

    auto expired = find_diff(old_pool, new_pool);
    auto expired1 = find_diff(old_pool1, new_pool1);

    display_result(expired);
    display_result(expired1);
}

