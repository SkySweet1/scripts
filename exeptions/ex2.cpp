#include <iostream>
#include <stdexcept>
#include <vector>

int main(void){
    std::vector<int> x = {1,2,3};

    try
    {
        std::cout << x.at(10) << std::endl;
    }
    catch(const std::out_of_range & ex)
    {
        std::cerr << ex.what() << std::endl;
    }
    
    /*
    метод at() проверяет границы и выбрасывает std::out_of_range 
    оператор [] не выполняет такой проверки
        программа не получает гарантированный обьект исключения
    */

    return 0;
}