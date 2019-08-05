#ifndef GUI_TYPES_HPP
#define GUI_TYPES_HPP

#include <cstdint>
#include <utility>
#include <functional>

#include "SFML/Window/Event.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "ResourceHolder.hpp"
#include "ResourceIdentifier.hpp"


enum Piece : uint8_t{
            blackBishop = static_cast<uint8_t>(0), blackKing, blackKnight, blackPawn, blackQueen, blackRook, whiteBishop, whiteKing, whiteKnight,
            whitePawn, whiteQueen, whiteRook , totalPieces, EMPTY = (0b11111111)
};

struct sfmlContext{
        sf::RenderWindow* mWindow;
        TextureHolder* mTextureHolder;
        std::function<bool(sf::Vector2u from , sf::Vector2u to)> pieceDropCall = nullptr;
        int tilesize = 0;
};

/*  
* The enum for board rows that class Board uses.
enum row : uint8_t{
                a = 0 , b , c , d , e , f , g , h
        };
*/

#endif