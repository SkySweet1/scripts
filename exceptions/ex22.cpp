/*
Задача 22. «Чтение существующего файла» (База)

Что делать:

Создай в папке с кодом текстовый файл test.txt и напиши в нем три любые строчки.
Напиши программу, которая открывает test.txt через std::ifstream.
Используя цикл while (std::getline(file, line)), выведи все строчки файла на экран.
В конце просто закрой файл file.close(); (пока без исключений).
Цель: Понять, как работает getline и как он останавливается, когда файл заканчивается (выставляя eofbit).
*/
#include <iostream>
#include <fstream>

int main(void)
{
    std::ifstream file;

    file.open("text.txt");

    std::string line;

    /*  text.txt
        123
        123
        123
    */

    while (std::getline(file, line))
    {
        std::cout << line << '\n';
    }
    
    file.close();

    return 0;
}
