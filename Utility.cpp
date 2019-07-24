#include "Utility.hpp"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Rect.hpp>

void centerOrigin(sf::Sprite& sprite)
{
    sf::FloatRect rect = sprite.getLocalBounds();
    sprite.setOrigin( rect.width/2.f , rect.height/2.f);
}

void fixScale( sf::Sprite& sprite, float x , float y)
{
    sf::FloatRect rect = sprite.getLocalBounds();
    sprite.setScale( x / rect.width , y / rect.height );
}

Textures::ID pieceToTexture( Piece piece )
{
    switch(piece)
    {
        case Piece::blackBishop:
            return Textures::blackBishop ;
        case Piece::blackKing:
            return Textures::blackKing ;
        case Piece::blackKnight:
            return Textures::blackKnight ; 
        case Piece::blackPawn:
            return Textures::blackPawn ;
        case Piece::blackQueen:
            return Textures::blackQueen ; 
        case Piece::blackRook:
            return Textures::blackRook ;
        case Piece::whiteBishop:
            return Textures::whiteBishop ; 
        case Piece::whiteKing:
            return Textures::whiteKing ;
        case Piece::whiteKnight:
            return Textures::whiteKnight ;
        case Piece::whitePawn:
            return Textures::whitePawn ; 
        case Piece::whiteQueen:
            return Textures::whiteQueen ;
        case Piece::whiteRook:
            return Textures::whiteRook ;
        case Piece::totalPieces:
            return Textures::totalPieces ;
        case Piece::EMPTY:
            return Textures::totalPieces ;
    }
  
}
