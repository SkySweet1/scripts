/*
Задача 23. «Копия из курсовой» (Ручная проверка)

Что делать:

Скопируй логику твоей функции print_first_line из курсовой, но назови её openFile.
Внутри создай std::ifstream file;
Включи настройку: file.exceptions(std::ios::badbit); (пока только badbit!)
Попробуй открыть файл "no_file.txt" (которого не существует).
Напиши проверку: if (!file.is_open()) throw std::ios_base::failure("Не открылось!");
В main вызови функцию в try и поймай catch (const std::ios_base::failure& e). Выведи e.what().
Цель: Понять, почему с включенным только badbit программа не падает на строчке open(),
а спокойно идет дальше до ручной проверки is_open().
*/
#include <iostream>
#include <fstream>

void openfile(const std::string &path) // скопированно из 21-1
{
    std::ifstream file;

    file.exceptions(std::ios::badbit);

    file.open("no_file.txt");

    if (!file.is_open())
    {
        throw std::ios_base::failure("Cannot open this file");
    }

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
        std::cerr << ex.what() << '\n';
    }

    /*
        exceptions git:(main) ✗ g++ ex23.cpp && ./a.out

        Cannot open this file: unspecified iostream_category error

        ➜  exceptions git:(main) ✗
    */

    return 0;
}