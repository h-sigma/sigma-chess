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