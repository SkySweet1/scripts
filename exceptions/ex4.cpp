#include <iostream>
#include <stdexcept>

int main(void)
{
    try
    {
        throw std::out_of_range("err");
    }
    catch (const std::exception &ex)
    {
        std::cerr << "1 " << ex.what() << std::endl;
    }
    catch (const std::out_of_range &ex)
    {
        std::cerr << "2 " << ex.what() << std::endl;
    }

    /*
        вообщем - если мы поставим catch(const std::exception & ex) первым
        то именно этот блок catch поймает это исключение т к
        базовый класс принимает все обьекты младших классов (незнаю как сказать классы которые унаследовали класс exeption (производные))
        и для этого исключения catch(const std::exception & ex) и catch(const std::out_of_range & ex) весят одинаково (оба обработчика совместимы по типу)
        и по этому что первое поймаяет это исключение (сверху вниз) то и будет

        теперь посмотрю в курсовую

        catch принимающий сылку на базовый класс может обработать и производный тип
        обработчики внитри одного try проверяються по порядку обьявления поэтому конкретный тип следует размещать раньше базового


        ➜  exeptions g++ ex3.cpp && ./a.out
        ex3.cpp:13:17: warning: exception of type 'const std::out_of_range &' will be caught by earlier handler [-Wexceptions]
        13 |     catch(const std::out_of_range & ex)
            |                 ^
        ex3.cpp:9:17: note: for type 'const std::exception &'
            9 |     catch(const std::exception & ex)
            |                 ^
        1 warning generated.
        1 err
        ➜  exeptions

        Компилятор clang++ (который ты используешь на Mac) — очень умный.
        Он сам провел статический анализ кода и выдал предупреждение
        (warning: exception of type 'const std::out_of_range &' will be caught by earlier handler),
        что второй catch — это мертвый код (unreachable code), потому что первый обработчик всё перехватит
    */

    return 0;
}