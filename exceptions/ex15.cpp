/*
Задача 15. «Железобетонный конструктор» (RAII + noexcept)

Уровень: Сложный.
Что делать:

Создай класс DatabaseConnection. У него внутри поле std::unique_ptr<int> data.
В конструкторе выдели память через std::make_unique<int>(42), выведи "Память выделена", а затем выброси std::runtime_error.
В деструкторе просто выведи "Деструктор класса".
В main создай этот объект в try-catch.
Задание со звездочкой: Пометь конструктор перемещения этого класса (если бы он был) как noexcept.
Вопрос: Выведется ли "Деструктор класса"? Останется ли в памяти утечка от std::make_unique?
(Подсказка из курсовой: Раздел 1.3 и идиома RAII. Если конструктор упал, деструктор самого класса не вызывается, но локальные поля-объекты разрушаются).
*/
#include <iostream>
#include <stdexcept>
#include <memory>
#include <utility>

class DatabaseConnection
{
private:
    std::unique_ptr<int> data;

public:
    DatabaseConnection()
    {
        data = std::make_unique<int>(42);

        std::cout << "memmory allocated" << '\n';

        throw std::runtime_error("fail in DatabaseConnection");
    }

    DatabaseConnection(DatabaseConnection &&other) noexcept
    {
        data = std::move(other.data); // почемуто помечает как ошибку ("=")

        /*
        data = other.data

        компилятор будет рукаться потому что std::unique_ptr
        это эксклюзивный владелец. его нелзя просто скопировать через "="
        потому что тогде у двух обьектов был бы один и тот же указатель и они бы попытались его удалить (двойное удаление справоцирует краш)

        чтобы украсть указатель нужно явно разрешить перемещение

        data = std::move(other.data);
        */

        // other.data = nullptr;                                  не обязательно

        std::cout << "obj moved" << '\n';
    }

    ~DatabaseConnection()
    {
        std::cout << "dc destr" << '\n';
    }
};

int main(void)
{
    try
    {
        DatabaseConnection obj;
    }
    catch (const std::exception &ex)
    {
        std::cerr << "fail in main" << '\n';
    }

    /*
    memmory allocated
    fail in main

    дектруктор не выведеться так как исключение выбросилось во время действия
    конструктора значит обьект не собрался до конца - и поэтому не сработал деструктор
    */

    return 0;
}