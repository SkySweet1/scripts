#include <iostream>
#include <stdexcept>
#include <string>

class A : public std::runtime_error
{
private:
    int errorCode;

public:
    A(const std::string &message, int code) : std::runtime_error(message), errorCode(code) {}

    int GetErrorCode() const
    {
        return errorCode;
    }
};

class B : public A
{
private:
    std::string science_explain;

public:
    B(const std::string &message, int code, const std::string &science_message) : A(message, code), science_explain(science_message) {}

    std::string GetScienceExplain() const
    {
        return science_explain;
    }
};

int main(void)
{
    try
    {
        throw B("error", 404, "error");
    }
    catch (B ex)
    {
        std::cout << ex.what() << " " << ex.GetErrorCode() << " " << ex.GetScienceExplain() << '\n';
    }
    catch (...)
    {
        std::cout << "unknown" << '\n';
    }

    return 0;
}