/*
Задача 14. «Ловля после переброса» (Сложная ловушка)

Уровень: Сложный.
Что делать:

В functionInner() сгенерируй исключение std::out_of_range("Ошибка диапазона").
В functionOuter() сделай try-catch. Поймай базовый класс catch (const std::exception& e), выведи "Логирую в Outer" и сделай переброс throw;.
В main() сделай try-catch. А здесь поймай производный класс catch (const std::out_of_range& e).
Вопрос: Сработает ли catch в main, который ловит именно out_of_range, или программа упадет? Почему?
(Подсказка из курсовой: Раздел 1.3. Вспомни, почему для переброса нужен throw; без аргумента).
*/
#include <iostream>
#include <stdexcept>

void functionInner()
{
    throw std::out_of_range("diapazon fail");
}

void functionOuter()
{
    try
    {
        functionInner();
    }
    catch (const std::exception &ex)
    {
        std::cerr << "logging in Outer" << '\n';
        throw;
    }
}

int main(void)
{
    try
    {
        functionOuter();
    }
    catch (const std::out_of_range &ex)
    {
        std::cerr << "fail in main: " << ex.what() << '\n';
    }

    /*
    базовый класс ловит (и может обрабатывать) сылку на производный класс но не наоборот!

    throw (без аргумента) сохранит свой динамический тип
    */

    return 0;
}