#ifndef COIN_HPP
#define COIN_HPP

#include <vector>

#include <SFML/Graphics.hpp>

#include "Types.hpp"
#include "ResourceHolder.hpp"
#include "ResourceIdentifier.hpp"

class Board;

class Coin : public sf::Transformable, public sf::Drawable
{
    public:
        explicit Coin(Piece , Board*, sf::Vector2u , sfmlContext);
    public:
        void setSize(float size);
        void setGrabbed(bool val);
    // public:
    //     virtual std::vector<sf::Vector2i> genLegalMoves() = 0;
    //     virtual uint64_t genAttacks() = 0;
    public:
        void move( sf::Vector2u from, sf::Vector2u to);
        sf::Vector2u getFileRank() const;
        bool isGrabbed() const;
    public:
        void handleEvent( const sf::Event& event, sf::Vector2u pos);
    private:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    protected:
        Piece mType;
        Board* mBoard;
        sf::Vector2u mPos;
        sfmlContext mContext;
    private:
        sf::Sprite mSprite;
        bool mIsGrabbed;

};

#endif