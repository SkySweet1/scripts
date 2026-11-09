#include <iostream>
#include <string>
#include <stdexcept>

int convert(std::string & str){
    return std::stoi(str);
}

int main(void){
    std::string ned;

    std::cout << "entet the num: ";
    std::cin >> ned;
    
    try
    {
        int nedded = convert(ned);
        std::cout << "seccess" << std::endl;
    }
    catch(const std::invalid_argument & ex)
    {
        std::cout << ex.what() << std::endl;
    }
    catch(const std::out_of_range & ex)
    {
        std::cout << ex.what() << std::endl;
    }

    return 0;
}