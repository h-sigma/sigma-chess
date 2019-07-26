#include "BoardAPI.hpp"

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

BoardAPI::BoardAPI(sf::RenderWindow* window, TextureHolder* holder, int tsize)
: mBoard(window, holder, tsize)
{

}

void BoardAPI::set(sf::Vector2u pos, Piece piece)
{
    mBoard.set(pos,piece);
}

void BoardAPI::move( sf::Vector2u from, sf::Vector2u to)
{
    mBoard.move(from,to);
}

void BoardAPI::capture( sf::Vector2u at)
{
    mBoard.capture(at);
}   

void BoardAPI::handleEvent(const sf::Event& event)
{
    mBoard.handleEvent(event);
}

void BoardAPI::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(mBoard, states);
}   


