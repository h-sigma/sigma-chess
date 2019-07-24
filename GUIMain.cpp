#include <SFML/Graphics.hpp>
#include <exception>
#include <iostream>
#include "Board.hpp"

int main()
{
    try
    {
        Board board;
        board.run();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
}   