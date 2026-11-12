/*
Задача 20. «Вложенные исключения» (Nested Exceptions)

Тема: Сохранение контекста ошибки на разных уровнях. (Это фишка C++11).
Что делать:

Напиши функцию lowLevelFunction(), которая бросает std::runtime_error("Ошибка базы данных").
Напиши функцию highLevelFunction(), которая вызывает lowLevelFunction() внутри try-catch.
В catch (const std::exception& e) внутри highLevelFunction используй функцию std::throw_with_nested, чтобы выбросить новое исключение std::runtime_error("Ошибка приложения"), прикрепив к нему старое (пойманное) как вложенное.
В main вызови highLevelFunction() и поймай std::runtime_error.
В catch используй блок try { throw; } catch (const std::exception& e) { ... } и внутри него вызови std::rethrow_if_nested(e), чтобы достать исходную ошибку.
Вопрос: Зачем вообще нужно вкладывать исключения друг в друга? Что мы увидим, если достанем вложенное исключение?
(Это реальный паттерн: не терять исходную причину ошибки, когда она проходит через разные слои приложения).
*/
#include <iostream>
#include <stdexcept>

void lowLevelfunction() {
    throw std::runtime_error("dataBase error");
}

void highLevelFunctio(){
    try
    {
        lowLevelfunction();
    }
    catch(const std::exception & ex)
    {
        std::throw_with_nested(std::runtime_error("application error"));
    }
    
}

int main(void){
    try
    {
        highLevelFunctio();
    }
    catch(const std::exception& e)
    {
        std::cerr << "fail in higt main: " << e.what() << '\n';

        try
        {
            std::rethrow_if_nested(e);
        }
        catch(const std::exception& nested_e)
        {
            std::cerr << "fail in low main: " << nested_e.what() << '\n';
        }
    }

    /*
    Вложенные исключения нужны для сохранения контекста ошибки при прохождении через разные слои приложения. 
    Функция std::throw_with_nested упаковывает новое исключение вместе с исходным, а std::rethrow_if_nested 
    озволяет извлечь исходную причину. Это помогает не терять информацию о первоначальном сбое при перехвате 
    на более высоких уровнях
    */
    
    return 0;
}
