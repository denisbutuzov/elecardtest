#pragma once

#include <thread>
#include <iostream>

class Foo
{
public:
    void func1()
    {
        std::thread th([&]() { this->func2(); });
    }
private:
    static void func2()
    {
        std::cout << "Hello, I am here" << std::endl;
    }
};
