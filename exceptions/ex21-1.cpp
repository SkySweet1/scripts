#include <fstream>
#include <iostream>
#include <string>

void print_first_line(const std::string &path)
{
    std::ifstream input;                // обьект потока
    input.exceptions(std::ios::badbit); // настройка - batbit -> runtime ошибка - failbit -> логическая - eofbit -> конец файла
    input.open(path);                   // 

    if (!input.is_open())
        throw std::ios_base::failure("Не удалось открыть файл: " + path);

    std::string line;

    if (std::getline(input, line))

        std::cout << line << '\n';
}

int main(void)
{
    try
    {
        print_first_line("data.txt");
    }
    catch (const std::ios_base::failure &e)
    {
        std::cerr << "Ошибка файла: " << e.what() << '\n';
    }
}