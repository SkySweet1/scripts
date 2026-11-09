/*
Задача 12. «Банковский счет» (Свои исключения)

Уровень: Средний.
Что делать:

Создай свой класс исключения InsufficientFundsException, унаследованный от std::runtime_error.
Создай класс BankAccount. У него должно быть поле double balance.
Напиши метод withdraw(double amount). Если сумма снятия больше, чем баланс, выброси InsufficientFundsException (передай туда текст "Недостаточно средств").
В main создай счет с балансом 100.0. Попробуй снять 150.0 внутри try-catch. Поймай свое исключение и выведи e.what().
(Подсказка: не забудь, что геттеры и конструкторы для своих исключений мы уже умеем писать).

*/

#include <iostream>
#include <stdexcept>
#include <string>

class InsufficientFundsExeption : public std::runtime_error
{
public:
    InsufficientFundsExeption(const std::string & message) : std::runtime_error(message) {}
};

class BankAccount
{
private:
    double balance;
    std::string owner;
public:
    BankAccount(const std::string & name, double amount) : owner(name), balance(amount) {}

    void withdraw(double amount){
        if(amount > balance){
            throw InsufficientFundsExeption("nedostatochno sredstv " + owner);
        }

        balance -= amount;

        std::cout << "seccess" << std::endl;
    }

    void deposit(double amount){
        balance += amount;

        std::cout << "success" << std::endl;
    }

    double getBalance() const {
        return balance;
    }

};

int main(void){
    BankAccount anonimus("acc", 100);

    try
    {
        anonimus.withdraw(200);
    }
    catch(const InsufficientFundsExeption & ex)
    {
        std::cerr << "fail: " << ex.what() << '\n';
    }
    
    anonimus.getBalance();

    return 0;
}