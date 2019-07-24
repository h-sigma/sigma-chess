#ifndef UTILITY_HPP
#define UTILITY_HPP

#include "Types.hpp"
#include "ResourceIdentifier.hpp"

namespace sf{
    class Sprite;
}

void centerOrigin( sf::Sprite& sprite);

void fixScale( sf::Sprite& sprite , float x , float y);

Textures::ID pieceToTexture( Piece piece );

#endif