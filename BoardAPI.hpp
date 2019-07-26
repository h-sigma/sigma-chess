#ifndef BOARDAPI_HPP
#define BOARDAPI_HPP

#include "Board.hpp"

namespace sf{
    class RenderWindow;
    class TextureHolder;
    class RenderTarget;
    class RenderStates;
    class Event;
};

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>

#include <SFML/System/Vector2.hpp>

class BoardAPI : public sf::Transformable, public sf::Drawable
{
    public:
        BoardAPI(sf::RenderWindow* window, TextureHolder* holder, int tsize);
    public:
        void set(sf::Vector2u pos, Piece piece);
        void move( sf::Vector2u from, sf::Vector2u to);
        void capture( sf::Vector2u at);    public:
    public:
        void handleEvent(const sf::Event& event);
    private:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    private:
        Board mBoard;
};

#endif