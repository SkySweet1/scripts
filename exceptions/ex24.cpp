/*
Задача 24. «Магия failbit» (Автоматическая проверка)

Что делать:

Возьми код из Задачи 23.
Измени настройку маски на: file.exceptions(std::ios::badbit | std::ios::failbit);
Удали строчку if (!file.is_open()) throw ....
Оставь только: file.open("no_file.txt");
Запусти программу.
Цель: Увидеть, что теперь исключение ios_base::failure вылетает прямо на строчке open().
Программа даже не доходит до следующих строк. Это то, о чем написано на стр. 17 твоей курсовой
(почему автор не включил failbit в основном примере).
*/
#include <iostream>
#include <fstream>

void openfile(const std::string &path) // скопированно из 21-1
{
    std::ifstream file;

    file.exceptions(std::ios::badbit | std::ios_base::failbit);

    std::cout << "1" << '\n';

    file.open(path);

    std::cout << "2" << '\n';

    file.close();
}

int main(void)
{
    try
    {
        openfile("data.txt");
    }
    catch (const std::ios_base::failure &ex)
    {
        std::cerr << "fail in main: " << ex.what() << '\n';
    }

    /*
        ➜  exceptions git:(main) ✗ g++ ex24.cpp && ./a.out
        1
        fail in main: ios_base::clear: unspecified iostream_category error
        ➜  exceptions git:(main) ✗ 

        код не доходит то 2 т к включена настройка которая если что выбросит исключение?

ё    */

    return 0;
}