/*
Задача 25. «RAII и файлы» (Секретное свойство)

Что делать:

Напиши функцию, которая открывает test.txt (файл из Задачи 22) и выводит первую строчку.
Сразу после открытия и чтения добавь строчку: throw std::runtime_error("Внезапная ошибка!");
В main оберни вызов в try-catch.
Задай себе вопрос: если функция вылетела с исключением, файл на диске остался открытым (заблокированным) или закрылся?
(Подсказка: закрой глаза и вспомни, что происходит с std::ifstream, когда он выходит из области видимости).
Цель: Понять, что тебе не нужно писать file.close() в конце функции, если вылетело исключение. Деструктор умного потока сделает всё сам.
*/
#include <iostream>
#include <fstream>
#include <stdexcept>

void closeFile();

void openfile()
{
    std::ifstream file;

    file.open("text.txt");

    /*  text.txt
    txt
    txt
    txt
    */

    std::string line;

    while (std::getline(file, line))
    {
        std::cout << line << '\n';

        throw std::runtime_error("suddenly error");
    }

    closeFile(file);

    /*
    про то что во время раскрутки стека идет разрушение локальных автоматических обьектов я помню
    получаеться в декструкторе этого обьекта идет закрытие файла?

    ну вообщем если исключение выброситься то файл сам закроеться без моей помощи
    */
}

void closeFile(std::ifstream &file) noexcept
{
    file.close();
}
/*
я вспомнил что можно так писать с noexept вроде как но я не знаю как мне передать именно файл вот этот
*/

int main(void)
{
    try
    {
        closeFile();
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    return 0;
}