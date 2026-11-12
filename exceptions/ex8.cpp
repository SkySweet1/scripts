/*
Задача 8. «Переброс ошибки (Re-throwing)»
Напиши три функции: main() вызывает functionA(), functionA() вызывает functionB().
В functionB() сгенерируй исключение std::runtime_error("Ошибка в B").
В functionA() сделай try-catch. В блоке catch выведи сообщение "Логирую ошибку в A",
а затем перебрось это же исключение дальше наверх (в main).
В main поймай его и выведи "Поймано в main".
Вопрос: Почему для переброса нужно писать именно throw; (без аргумента), а не throw e;?
(Подсказка из текста: Раздел 1.3. throw; сохраняет исходный динамический тип объекта).
*/
#include <iostream>
#include <stdexcept>

void function_B()
{
    std::cout << "throw error in B" << std::endl;

    throw std::runtime_error("error in B");
}

void function_A()
{
    try
    {
        std::cout << "in A, call B" << std::endl;
        function_B();
    }
    catch (const std::runtime_error &ex)
    {
        std::cerr << "catch in A: " << ex.what() << '\n';

        throw;
        // ошибку можно перебросить дальше
        // если throw написать с аргументом то производный тип срежеться и останеться только базовый
        // а вот если без обьекта то динамический тип обьекта передатся дальше и его методы сохраняться
    }
}

int main(void)
{
    try
    {
        std::cout << "call A" << '\n';
        function_A();
    }
    catch (const std::runtime_error &ex)
    {
        std::cerr << "catch in main: " << ex.what() << '\n';
    }

    return 0;
}