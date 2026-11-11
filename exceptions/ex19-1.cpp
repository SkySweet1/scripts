/*
Задача 19. «Копирование вместо перемещения» (Логика std::vector)

Тема: noexcept и строгая гарантия безопасности.
Что делать:

Создай класс HeavyObject.
Напиши для него конструктор копирования, который выводит "Копирование".
Напиши конструктор перемещения, который выводит "Перемещение", но НЕ помечай его как noexcept (сделай его потенциально опасным).
В main создай std::vector<HeavyObject> vec;.
Используй vec.reserve(1); чтобы выделить память на 1 элемент.
Добавь первый элемент vec.push_back(HeavyObject());.
Добавь второй элемент vec.push_back(HeavyObject()); (тут вектору придется перевыделять память).
Вопрос: При добавлении второго элемента (когда вектору нужно расширяться), что выведет программа: 
"Копирование" или "Перемещение"? И почему вектор принял такое решение?
(Подсказка: если move-конструктор не помечен noexcept, 
std::vector не может дать строгую гарантию безопасности при перемещении, поэтому использует более безопасное копирование).
*/
#include <iostream>
#include <vector>

class HeavyObject
{
// private:
//     int data[100];

public:
    HeavyObject() {
        std::cout << "simple constr" << '\n';
    }

    HeavyObject(const HeavyObject & other) {
        std::cout << "copy constr" << '\n';
    }

    HeavyObject(HeavyObject&& other) {
        std::cout << "move constr" << '\n';
    }

    ~HeavyObject() {
        std::cout << "destr" << '\n';
    }
};

int main(void){
    std::vector<HeavyObject> vector_X;
    
    vector_X.reserve(1);

    vector_X.push_back(HeavyObject());

    vector_X.push_back(HeavyObject());

    /*
    ➜  exceptions git:(main) ✗ g++ ex19.cpp && ./a.out
    simple constr
    move constr
    destr
    destr

    сначала умирает временный объект (из скобок), 
    а в самом конце программы — элемент внутри вектора.

    ➜  exceptions git:(main) ✗ g++ ex19.cpp && ./a.out
    simple constr
    move constr
    destr
    simple constr
    move constr
    copy constr
    destr
    destr
    destr
    destr
    */

    return 0;
}