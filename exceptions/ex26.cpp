/*
Задача 26. «Многослойное приложение» (Наследование + Вложенные исключения)

Часть 1: Иерархия исключений

Создай базовый класс AppException, унаследованный от std::runtime_error. В нем пока ничего не нужно, кроме конструктора, принимающего строку и передающего ее в std::runtime_error.
Создай производный класс NetworkException, унаследованный от AppException.
Добавь в NetworkException приватное поле int statusCode и метод getStatusCode().
Конструктор NetworkException должен принимать строку сообщения и int statusCode (и передавать строку в базовый класс AppException).
Часть 2: Низкий уровень (База данных)

Напиши функцию fetchFromDatabase(). Внутри нее просто выброси стандартное исключение: throw std::runtime_error("Ошибка подключения к порту 5432");
Часть 3: Средний уровень (Сетевой слой)

Напиши функцию loadUserData().
Внутри нее открой блок try и вызови fetchFromDatabase().
Напиши catch (const std::exception& e).
Внутри catch используй std::throw_with_nested, чтобы выбросить новое исключение NetworkException("Не удалось загрузить данные пользователя", 500). Таким образом, ты "упакуешь" ошибку базы данных внутрь сетевой ошибки.
Часть 4: Высокий уровень (Main)

В main открой try и вызови loadUserData().
Напиши catch (const NetworkException& e) (лови именно производный класс, чтобы проверить наследование!).
Внутри catch выведи:

Сообщение об ошибке: e.what()
Код ошибки: e.getStatusCode()
Самое интересное: Внутри этого же catch напиши вложенный try, внутри которого вызови std::rethrow_if_nested(e).
Напиши catch (const std::exception& nested_e) (внутри вложенного try), который выведет исходную ошибку: "Причина: " << nested_e.what().
Вопрос для размышления (ответь в комментариях):
Почему в main мы ловим NetworkException, хотя изначально (в самом низу) вылетело std::runtime_error? И зачем нам понадобился std::rethrow_if_nested, если мы могли просто вывести e.what()?
*/
#include <iostream>
#include <stdexcept>

class AppException : public std::runtime_error
{
public:
    AppException(const std::string &message) : std::runtime_error(message) {}
};

class NetworkException : public AppException
{
private:
    int statusCode;

public:
    NetworkException(const std::string &message, int code) : AppException(message), statusCode(code) {}

    int GetStatusCode() const
    {
        return statusCode;
    }

    ~NetworkException() {}
};

void fetchFromDatabase()
{
    throw std::runtime_error("fail to connect to port 5432");
}

void loaduserData()
{
    try
    {
        fetchFromDatabase();
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';

        std::throw_with_nested(NetworkException("failed to load user data ", 500));
    }
}

int main(void)
{
    try
    {
        loaduserData();
    }
    catch (const NetworkException &e)
    {
        std::cerr << "fail in main: " << e.what() << e.GetStatusCode() << '\n';

        try
        {
            std::rethrow_if_nested(e);
        }
        catch (const std::exception &nested_e)
        {
            std::cerr << "fail reason: " << nested_e.what() << '\n';
        }
    }

    /*
        вывод:
            fail to connect to port 5432
            fail in main: failed to load user data500
            fail reason: fail to connect to port 5432

        1 вопрос:
            ну так мы ловим производный класс а не базовый, от которого наследуемся
            и поэтому располагаем конкретный обработчик раньше базового чтобы небыло срезки

            Изначально на нижнем уровне возникло исключение std::runtime_error.
            Функция loadUserData перехватила его, но не стала пробрасывать дальше в исходном виде.
            Вместо этого она с помощью std::throw_with_nested создала новое исключение
            NetworkException, которое содержит контекст более высокого уровня (сетевую ошибку),
            а исходное исключение упаковала внутрь как вложенное.
            Поэтому в main прилетает именно NetworkException

        2 вопрос:
            ну чтобы раскрыть обертку исключения и посмотреть то нижний уровень

            Если мы выведем только e.what(), мы увидим лишь сообщение
            верхнего уровня ("Не удалось загрузить данные пользователя").
            Мы потеряем информацию о том, почему это произошло
            (что на самом деле упала база данных).
            std::rethrow_if_nested позволяет "распаковать матрешку" и достать
            исходное исключение (std::runtime_error), чтобы увидеть настоящую причину сбоя в логах
    */

    return 0;
}