/*
Задача 5. «Своё исключение»
Создай свой класс исключения NetworkException,
унаследованный от std::runtime_error.
Добавь в него поле int errorCode.
Напиши функцию connect(), которая бросает это исключение.
В main поймай его, выведи сообщение через e.what() и
отдельно выведи код ошибки через e.errorCode.
(Подсказка из текста: Раздел 1.3. Исключения следует наследовать от
std::exception).
*/
#include <iostream>
#include <stdexcept>
#include <string>

class NetEx : public std::runtime_error
{
private:
    int errorCode;

public:
    NetEx(const std::string &message, int code) : std::runtime_error(message), errorCode(code)
    {
        std::cout << "error_call" << '\n';
    }

    int getError() const
    {
        return errorCode;
    }

    ~NetEx()
    {
        std::cout << "error_destructed" << '\n';
    }
};

void connect()
{
    throw NetEx("error", 404);
}

int main(void)
{
    try
    {
        connect();
    }
    catch (const NetEx &ex)
    {
        std::cerr << ex.what() << " " << ex.getError() << '\n';
    }

    return 0;
}