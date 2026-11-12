/*
Задача 21. «Секретный файл»

Что нужно сделать:

Напиши функцию readSecretFile(). Она не принимает аргументов.
Внутри функции создай поток для чтения: std::ifstream file;
Попробуй открыть файл с названием "secret.txt" (этого файла у тебя на компьютере нет, и это хорошо!).
Если файл не открылся (if (!file.is_open())),
выброси исключение std::runtime_error с текстом "Файл с секретами не найден!".
Если файл открылся (этого не случится, но код написать надо), прочитай из него одну строку и выведи её в консоль.
В main вызови эту функцию внутри try.
Добавь catch (const std::exception& e). Внутри выведи: "Ошибка: " << e.what().
*/
#include <iostream>
#include <fstream>
#include <string>

void readSecretFile()
{
    std::ifstream file; // создал поток

    file.open("secret.txt"); // открыл по потоку

    if (!file.is_open()) // проверил на открытие
    {
        throw std::runtime_error("not found"); // выбросил исключение
    }

    std::string line; // ввел обьект чтения

    std::getline(file, line); // прочитал

    std::cout << line << '\n'; // вывел

    file.close(); // закрыл
}

int main(void)
{
    try
    {
        readSecretFile();
    }
    catch (const std::runtime_error &ex) // производный
    {
        std::cerr << "fail runtime: " << ex.what() << '\n';
    }
    catch (const std::exception &ex) // базовый
    {
        std::cerr << "fail common: " << ex.what() << '\n';
    }
    catch (...) // общий
    {
        std::cout << "fail unknown: " << '\n';
    }

    /*
    ➜  exceptions git:(main) ✗ g++ ex22.cpp && ./a.out
    fail runtime: not found
    ➜  exceptions git:(main) ✗
    */

    return 0;
}