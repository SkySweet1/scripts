#include <iostream>
#include <stdexcept>

void lowLevelfunction()
{
    throw std::runtime_error("explosion");
}

void highLevelFunctio()
{
    try
    {
        lowLevelfunction();
    }
    catch (const std::exception &ex)
    {
        std::throw_with_nested(std::runtime_error("dataBase error"));
    }
}

void higtHigtLevelfunction()
{
    try
    {
        highLevelFunctio();
    }
    catch (const std::exception &ex)
    {
        std::throw_with_nested(std::runtime_error("application error"));
    }
}

int main(void)
{
    try
    {
        higtHigtLevelfunction();
    }
    catch (const std::exception &e)
    {
        std::cerr << "fail in higt main: " << e.what() << '\n';

        try
        {
            std::rethrow_if_nested(e);
        }
        catch (const std::exception &nested_e)
        {
            std::cerr << "fail in low main: " << nested_e.what() << '\n';

            try
            {
                std::rethrow_if_nested(nested_e);
            }
            catch (const std::exception &twice_nested_e)
            {
                std::cerr << "fail in low low level main: " << twice_nested_e.what() << '\n';
            }
        }
    }

    /*
    fail in higt main: application error
    fail in low main: dataBase error
    fail in low low level main: explosion

    программист получает лог с ошибкой "application error". Он смотрит глубже и видит "dataBase error".
    Смотрит еще глубже и видит "explosion". Теперь он точно знает, что база данных упала из-за того,
    что где-то произошел взрыв (например, кончилось место на диске или сработал триггер).
    Без вложенных исключений он бы видел только "application error" и гадал бы, что случилось
    */

    return 0;
}
