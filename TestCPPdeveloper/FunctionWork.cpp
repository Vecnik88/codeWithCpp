#include "TestWork.h"

int rand_value(int n)                           // <---. ф-ция генерирующая случайное число в диапазоне от 1 до n
{
    if(n==0)
        return 0;

    return (rand()%n+1);
}

int input_size_cont()                           // <---. пользователь сам устанавливаем размерность контейнеров
{                                               //       но не меньше 16
    int n = 0;

    cout << "Enter the size of the container (more than 15)" << endl;
    cin >> n;                                   // <---. подразумевается что будут введены только целые числа
    while(n < 16)                               //       поэтому обработка опущена
    {
        system ("cls");
        cout << "You value small, retry again" << endl;
        cout << "Enter the size of the container (more than 15)" << endl;
        cin >> n;
    }

    return n;
}
