#ifndef COIN_HPP
#define COIN_HPP

#include <vector>

class Board;

#include <SFML/Graphics.hpp>
#include "Types.hpp"
#include "ResourceHolder.hpp"
#include "ResourceIdentifier.hpp"

class Coin : public sf::Transformable, public sf::Drawable
{
    public:
        explicit Coin(Piece , Board*, int , sf::Vector2u , sf::RenderWindow* , TextureHolder*);
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
        int tile_size;
    private:
        sf::RenderWindow* mWindow;
        sf::Sprite mSprite;
        bool mIsGrabbed;

};

#endif