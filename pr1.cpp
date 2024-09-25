#include <iostream>
#include "class/Hotel.h"
#include "class/JsonParser.h"

int main()
{
    srand((unsigned int)time(0));
    Hotel h;
    Hotel h1(1);
    Hotel hTest;
    JsonParser<Hotel> parser;
    if (parser.addElement(h)) std::cout << "h\n";
    if (parser.addElement(h1)) std::cout << "h1\n";
    if (!parser.addElement(h)) std::cout << "wow, it works\n";

    parser.changeElement(hTest);

    auto temp = parser.find("Случайное имя", 9999);
    if (temp) {
        std::cout << "find";
    }

    std::cout << "Hello World!\n";
}