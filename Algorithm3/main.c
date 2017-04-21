/*
            ### *** Стек с поддержкой максимума *** ###

    Реализовать стек с поддержкой операций push,pop и max.

    Вход. Последовательность запросов push,pop и max.

    Выход. Для каждого запросаmaxвывести максимальное число, находящее на стеке. push pop

    Стек — абстрактная структура данных,поддерживающая операции push и pop.

    Несложно реализовать стек так, чтобы обеэти операции работали за константное время.

    В данной задача ваша цель — рас-шить интерфейс стека так, чтобы он до-полнительно поддерживал операцию
max и при этом чтобы время работы всех опе-раций по-прежнему было константным.

    Формат входа.
    Первая строка содержит число запросов q. Каждая из последующихqстрок задаёт запрос в одном из следующих форматов:
push v,pop, or max.

    Формат выхода.
    Для каждого запроса ma xвыведите (в отдельнойстроке) текущий максимум на стеке.
*/

#include <stdio.h>
#include <string.h>

#define MIN_POROG 1
#define MAX_POROG 400000
#define MAX_INT_NUMBER 100000

int main()
{
    int n = 0;
    int j = -1;
    int m = 0;
    scanf("%d", &n);

    char buffer[10];
    int arrayStack[n];

    if(n >= MIN_POROG && n <= MAX_POROG)
    {
        for(int i = 0; i < n; ++i)
        {
            scanf("%s", buffer);
            if(strncmp(buffer, "push", 4) == 0)
            {
                scanf("%d", &m);
                if(m >= 0 && m <= MAX_INT_NUMBER)
                {
                    if(j == -1)
                        arrayStack[++j] = m;
                    else
                        (m > arrayStack[j]) ? (arrayStack[++j] = m) : (arrayStack[++j] = arrayStack[j-1]);
                }
                else
                    return 0;
            }
            if(strncmp(buffer, "pop", 3) == 0)
                arrayStack[j--] = 0;

            if(strncmp(buffer, "max", 3) == 0)
                printf("%d\n", arrayStack[j]);
        }
    }

    return 0;
}
