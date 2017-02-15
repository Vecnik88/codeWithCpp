#include "TestWork.h"

    //display_map(cont_map);                            // <---. можно посмотреть на каждом этапе результат выполнения
    //display_vector(cont_vec);                         //       ###

int main()
{
    srand(time(0));
    int size_container = input_size_cont();

    vector<int> cont_vec(size_container);
    map<int, int> cont_map;
    map<int, int> new_cont_map;                         // <---. результирующий массив на выходе

    generate_container(cont_vec, size_container);       // <---. генерируем в каждый контейнер случайное
    generate_container(cont_map, size_container);       //       значение элемента от 0 до 9

    del_random_el_map(cont_map, size_container);        // <---. удаляем случайным образом от 1 до 15 элементов в контейнере
    del_random_el_vec(cont_vec, size_container);

    org_conteiner(cont_map, cont_vec);                  // <---. выравниваем количество элементов в контейнерах

    func_sort_result(cont_vec, cont_map, new_cont_map); // <---. сортируем, удаляем лишние элементы

    display_finish_result (cont_vec, new_cont_map);     // <---. выводим результат

    return 0;
}
