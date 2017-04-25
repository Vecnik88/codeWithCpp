// Created by Vecnik88

/*
            Системы непересекающихся множеств
                 Объединение таблиц.
    Ваша цель в данной задаче — реализовать симуляцию объединениятаблиц в базе данных.
    В базе данных естьnтаблиц, пронумерованных от 1 доn, над од-ним и тем же множеством столбцов (атрибутов).
    Каждая таблица со-держит либо реальные записи в таблице, либо символьную ссылку надругую таблицу.
    Изначально все таблицы содержат реальные записи,иi-я таблица содержитriзаписей.

    Ваша цель — обработатьmзапро-сов типа(destinationi;sourcei):

    1. Рассмотрим таблицу с номеромdestinationi. Пройдясь по цепоч-ке символьных ссылок,
найдём номер реальной таблицы, на ко-торую ссылается эта таблица:пока таблица destinationi содержит
символическую ссылку:destinationisymlink(destinationi)
    2. Сделаем то же самое с таблицейsourcei.
    3. Теперь таблицыdestinationiиsourceiсодержат реальные запи-си. Если destinationi6=sourcei,
скопируем все записи из таблицыsourceiв таблицуdestinationi, очистим таблицуsourceiи пропи-шем в неё
символическую ссылку на таблицуdestinationi.4. Выведем максимальный размер среди всехnтаблиц.
Размеромтаблицы называется число строк в ней.
Если таблица содержитсимволическую ссылку, считаем её размер равным нулю.

Формат входа.
    Первая строка содержит числаn иm— число таблици число запросов, соответственно.
    Вторая строка содержитnце-лых чиселr1; : : : ; rn— размеры таблиц.
    Каждая из последующихmстрок содержит два номера таблицdestinationiиsourcei, кото-рые необходимо объединить.
Формат выхода.
    Для каждого изmзапросов выведите максималь-ный размер таблицы после соответствующего объединения.
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct table
{
    unsigned int ref_table;                     // <---. ссылка на родительскую таблицу
    unsigned int height_table;                  // <---. глубина таблицы
} table;

unsigned int search_ref_for_table(table* tabl, unsigned int number);

int main()
{
    unsigned int n = 0;                               // <---. число таблиц
    unsigned int m = 0;                               // <---. число запросов

    unsigned int table1 = 0;              // <---. номер таблицы 1 для слияния
    unsigned int table2 = 0;              // <---. номер таблицы 2 для слияния

    unsigned int i = 0;                         // <---. счетчик
    unsigned int maxHeightTable = 0;            // <---. высота самой высокой таблицы

    scanf("%d%d", &n, &m);

    table* arrayTable = (table*)calloc(n, sizeof(table));       // <---. создаем массив для таблиц

    for(i = 0; i < n; ++i)
    {
        scanf("%d", &arrayTable[i].height_table);
        arrayTable[i].ref_table = i;

        if(arrayTable[i].height_table > maxHeightTable)
            maxHeightTable = arrayTable[i].height_table;
    }

    for(i = 0; i < m; ++i)
    {
        scanf("%d%d", &table1, &table2);
        --table1;
        --table2;

        table1 = search_ref_for_table(arrayTable, table1);
        table2 = search_ref_for_table(arrayTable, table2);

        if(table1 != table2)                    // <---. не одна и та же таблица
        {
            arrayTable[table1].height_table += arrayTable[table2].height_table;
            arrayTable[table2].height_table = 0;
            arrayTable[table2].ref_table = table1;

            if(arrayTable[table1].height_table > maxHeightTable)
                maxHeightTable = arrayTable[table1].height_table;
        }
        printf("%u\n", maxHeightTable);
    }

    free(arrayTable);
    return 0;
}

unsigned int search_ref_for_table(table* tabl, unsigned int number)
{
    if( tabl[number].ref_table != number)
        tabl[number].ref_table = search_ref_for_table(tabl, tabl[number].ref_table);

    return tabl[number].ref_table;
}
