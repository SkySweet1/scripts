/*
Задача 11. «Геометрия» (Базовые исключения)

Уровень: Легкий.
Что делать:

Напиши функцию calculateArea(int width, int height), которая возвращает площадь прямоугольника.
Если пользователь передал отрицательную ширину или высоту, функция должна выбросить std::invalid_argument с сообщением "Стороны не могут быть отрицательными".
В main вызови эту функцию с отрицательным числом внутри try-catch и обработай исключение.
(Подсказка из курсовой: Раздел 1.3, ошибки логики программы).
*/

#include <iostream>
#include <stdexcept>

int CalculateArea(int width, int height){
    if(width < 0 || height < 0){
        throw std::invalid_argument("smaller than zero");
    }    
    return width * height;
}

int main(void){
    int a = 10;
    int b = -10;

    try
    {
        CalculateArea(a,b);
    }
    catch(const std::invalid_argument & ex)
    {
        std::cerr << "fail: " <<  ex.what() << '\n';
    }
    

    return 0;
}