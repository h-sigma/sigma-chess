#include <exception>
#include <iostream>
#include "Application.hpp"

int main()
{
    try
    {
        Application app;
        app.run();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
}   