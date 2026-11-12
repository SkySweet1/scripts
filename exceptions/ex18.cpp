/*
Задача 18. «Инициализация с подвохом» (RAII и порядок полей)

Тема: Инициализация полей в конструкторе и гарантии исключений.
Что делать:

Создай класс Engine (двигатель). В его конструкторе выведи "Двигатель создан". В деструкторе выведи "Двигатель уничтожен".
Создай класс Wheels (колеса). В его конструкторе выведи "Колеса созданы". В деструкторе выведи "Колеса уничтожены".
Создай класс Car. У него два поля: std::unique_ptr<Engine> engine; и std::unique_ptr<Wheels> wheels; (порядок именно такой).
Напиши конструктор Car(), который инициализирует оба поля в списке инициализации (через make_unique).
Важно: в теле конструктора Car (внутри фигурных скобок) выброси исключение std::runtime_error("Авария на заводе").
В main оберни создание Car в try-catch.
Вопрос: В каком порядке будут выводиться сообщения в консоль?
(Сначала создание, потом уничтожение). Уничтожатся ли оба умных указателя, если тело конструктора Car упало с ошибкой?
*/
#include <iostream>
#include <stdexcept>
#include <memory>

class Engine
{
public:
    Engine()
    {
        std::cout << "engine created" << '\n';
    }

    ~Engine()
    {
        std::cout << "engine desructed" << '\n';
    }
};

class Wheels
{
public:
    Wheels()
    {
        std::cout << "wheels created" << '\n';
    }

    ~Wheels()
    {
        std::cout << "wheels destrected" << '\n';
    }
};

class Car
{
private:
    std::unique_ptr<Engine> engine;
    std::unique_ptr<Wheels> wheels;

public:
    Car() : engine(std::make_unique<Engine>()), wheels(std::make_unique<Wheels>())
    {
        std::cout << "memory allocated" << '\n';

        throw std::runtime_error("explosion on factory");
    }

    ~Car()
    {
        std::cout << "не вызоветься" << '\n';
    }
};

int main(void)
{
    try
    {
        Car myCar;
    }
    catch (const std::exception &e)
    {
        std::cerr << "fail in main: " << e.what() << '\n';
    }

    /*
    engine created
    wheels created
    memory allocated
    wheels destrected
    engine desructed
    fail in main: explosion on factory

    деструктор класс Car никогда не вызоветься поскольку иключение выброситься в конктрукторе при этом не создав обьект до конца

    раскрутка стека - это разрушение локальных автоматических обьектов между точкой выброса исключения
    и найденным обработчиком в обратном порядке их создания
    */

    return 0;
}