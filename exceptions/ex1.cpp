#include <iostream>
#include <stdexcept>

double safeDivide(int a, int b)
{
    if (b == 0)
    {
        throw std::domain_error("делитель равен нулю");
    }

    return static_cast<double>(a) / b;
}

int main(void)
{
    int a = 10;
    int b = 0;

    try
    {
        double result = safeDivide(a, b);
        std::cout << "result: " << result << std::endl;
    }
    catch (const std::domain_error &ex)
    {
        std::cout << "exeption: " << ex.what() << std::endl;
    }
    catch (...)
    {
        std::cout << "unnown incorrect" << std::endl;
    }

    return 0;
}
