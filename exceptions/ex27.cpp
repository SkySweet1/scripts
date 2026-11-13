/*
Задача 27. «Матрёшка 4 уровня» (Тройное наследование + Тройная вложенность)

Часть 1: Тройное наследование

Создай базовый класс AppError (наследник std::runtime_error). Конструктор принимает строку.
Создай класс ServiceError (наследник AppError). Конструктор принимает строку.
Создай класс DatabaseError (наследник ServiceError). Конструктор принимает строку.
Часть 2: Вложенные исключения (4 уровня)

Напиши функцию level0_database(). Внутри просто выбрось std::runtime_error("Core: Disk I/O Error");
Напиши функцию level1_service().
Внутри try вызови level0_database().
В catch (const std::exception& e) используй std::throw_with_nested, чтобы выбросить DatabaseError("Database: Query failed") (упаковываешь ошибку диска внутрь ошибки БД).
Напиши функцию level2_api().
Внутри try вызови level1_service().
В catch используй std::throw_with_nested, чтобы выбросить ServiceError("Service: API Timeout") (упаковываешь ошибку БД внутрь ошибки Сервиса).
Напиши функцию level3_app().
Внутри try вызови level2_api().
В catch используй std::throw_with_nested, чтобы выбросить AppError("App: UI Crashed") (упаковываешь ошибку Сервиса внутрь ошибки Приложения).
Часть 3: Распаковка (Main)

В main вызови level3_app() внутри try.
Напиши catch (const AppError& e).
Внутри catch сделай цепочку из трех вложенных try-catch, чтобы достать все уровни:
Выведи "Уровень 3: " << e.what()
В первом try вызываешь rethrow_if_nested(e). Ловишь const ServiceError& e2. Выводишь "Уровень 2: " << e2.what().
Во втором try (внутри первого catch) вызываешь rethrow_if_nested(e2). Ловишь const DatabaseError& e3. Выводишь "Уровень 1: " << e3.what().
В третьем try (внутри второго catch) вызываешь rethrow_if_nested(e3). Ловишь const std::exception& e4. Выводишь "Уровень 0 (корень): " << e4.what().
Вопрос для размышления:
Как ты думаешь, почему в main мы ловим сначала AppError, потом ServiceError, потом DatabaseError, а в самом конце std::exception? Что было бы, если бы мы попытались поймать их в обратном порядке?
*/
#include <iostream>
#include <stdexcept>
#include <string>

class AppError : public std::runtime_error
{
public:
    AppError(const std::string &message) : std::runtime_error(message) {}

    ~AppError() {}
};

class ServiceError : public AppError
{
public:
    ServiceError(const std::string &message) : AppError(message) {}

    ~ServiceError() {}
};

class DataBaseError : public ServiceError
{
public:
    DataBaseError(const std::string &message) : ServiceError(message) {}

    ~DataBaseError() {}
};

void level0_database()
{
    throw std::runtime_error("Core: Disk I/O Error");
}

void level1_service()
{
    try
    {
        level0_database();
    }
    catch (const std::exception &e)
    {
        std::throw_with_nested(DataBaseError("Database: Query failed"));
    }
}

void level2_api()
{
    try
    {
        level1_service();
    }
    catch (const std::exception &e)
    {
        std::throw_with_nested(ServiceError("Service: API Timeout"));
    }
}

void level3_app()
{
    try
    {
        level2_api();
    }
    catch (const std::exception &e)
    {
        std::throw_with_nested(AppError("App: UI Crashed"));
    }
}

int main(void)
{
    try
    {
        level3_app();
    }
    catch (const AppError &e)
    {
        std::cerr << e.what() << '\n';

        try
        {
            std::rethrow_if_nested(e);
        }
        catch (const ServiceError &nested_e)
        {
            std::cerr << nested_e.what() << '\n';

            try
            {
                std::rethrow_if_nested(nested_e);
            }
            catch (const DataBaseError &twice_nested_e)
            {
                std::cerr << twice_nested_e.what() << '\n';

                try
                {
                    std::rethrow_if_nested(twice_nested_e);
                }
                catch (const std::exception &triple_nested_e)
                {
                    std::cerr << triple_nested_e.what() << '\n';
                }
            }
        }
    }

    /*
    ➜  exceptions git:(main) ✗ g++ ex27.cpp && ./a.out

        App: UI Crashed
        Service: API Timeout
        Database: Query failed
        Core: Disk I/O Error

    ➜  exceptions git:(main) ✗
    */

    return 0;
}
