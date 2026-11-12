/*
Задача 16. «Объектная срезка (Object Slicing) в действии»

Тема: Ловля по значению vs по ссылке. Переброс.
Что делать:

Создай базовый класс BaseException (наследник std::runtime_error).
Создай производный класс DerivedException (наследник BaseException), у которого есть дополнительное поле int code.
Напиши функцию, которая бросает DerivedException с кодом 404.
В main напиши catch (BaseException e) — обрати внимание, ловим по значению, без амперсанда! Внутри выведи сообщение и сделай throw; (переброс).
В том же main сделай второй catch (const DerivedException& e) (он будет ниже). Выведи e.code.
Вопрос: Сработает ли второй catch (который ждет DerivedException)? Что произойдет с полем code при первом перехвате по значению?
(Подсказка: вспомни, как работает копирование объектов при передаче по значению).
*/

#include <iostream>
#include <stdexcept>

class BaseExeption : public std::runtime_error
{
public:
    BaseExeption(const std::string &message) : std::runtime_error(message) {}

    ~BaseExeption() {}
};

class DerivedException : public BaseExeption
{
private:
    int code;

public:
    DerivedException(const std::string &message, int error) : BaseExeption(message), code(error) {}

    /*
    я назнал что можно писать вот так: BaseExeption(message) - круто
    */

    int getErrorCode() const
    {
        return code;
    }

    ~DerivedException() {}
};

int main(void)
{
    try
    {
        throw DerivedException("error", 404);
    }
    catch (BaseExeption ex)
    {
        std::cerr << "fail in main: " << ex.what() << '\n';

        throw;

        /*
        программа уже перебрасывает обьезаный обьект BaseExeption
        значит следующий const DerivedException & ex ей не подойдет и исключение пойдет дальше а дальше ничего нет и программа завершиться

        тут throw без аргумента и поэтому он будет перебрасыват динамический тип обьекта
        ОДНАКО срезка произошла не на моменте когда здесь написано throw а на моменте когда исключение
        поставила в соответствие подходящий БАЗОВЫЙ класс BaseException
        а уже потом мы перебрасываем динамический УЖЕ СРЕЗАНЫЙ тип обьекта (явахуе)
        */
    }
    catch (const DerivedException &ex)
    {
        std::cout << " -> fail in main: " << ex.what() << " " << ex.getErrorCode() << '\n';
    }

    return 0;
}