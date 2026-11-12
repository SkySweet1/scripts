/*
Задача 7. «Безопасная работа с файлом»
Напиши функцию readFile(), которая открывает файл "data.txt" через std::ifstream. 
Включи маску исключений input.exceptions(std::ios::badbit);. 
Если файл не открылся (метод is_open() вернул false), 
выбрось исключение std::ios_base::failure с текстом "Файл не найден". 
В main поймай это исключение.
(Подсказка из текста: Раздел 2.3, третий пример из практики).
*/
#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>

void readFile(const std::string & path){
    std::ifstream inputFile;
    // создать обьект inputFile - поток
    inputFile.exceptions(std::ios::badbit | std::ios::failbit);
    // эта настройка при ошибке не просто поставит флажок а сразу бросит исключение
    inputFile.open(path);
    // подключить к потоку сам файл
    if(!inputFile.is_open()){
        throw std::ios_base::failure("not exist");
    }
    // проверить есть ли вообще такой файл (или права илии еще чтото)
}

int main(void){
    try
    {
        readFile("data.txt");
    }
    catch(const std::ios_base::failure & ex)
    {
        std::cerr << "fail: " << ex.what() << '\n';
    }
    
    return 0;
}