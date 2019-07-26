#ifndef GUI_BOARD_HPP
#define GUI_BOARD_HPP

#include <array>    

#include "Coin.hpp"
#include "ResourceHolder.hpp"
#include "ResourceIdentifier.hpp"
#include "Types.hpp"

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics.hpp>

namespace sf{
    class Event;
    class Time;
}

class Board : public sf::Transformable , public sf::Drawable , private sf::NonCopyable
{
    //constructors
    public:     
        explicit Board(sf::RenderWindow* window, TextureHolder* holder, int tsize);

    //operations on board
    public:     
        void set(sf::Vector2u pos, Piece piece);
        void move( sf::Vector2u from, sf::Vector2u to);
        void capture( sf::Vector2u at);
        void setLast(sf::Vector2i from, sf::Vector2i to);
        void setSelected(sf::Vector2i at);
    //sfml handlers
    public:
        void handleEvent(const sf::Event& event);
    //utility for internal use
    private:    
        void loadResources();
        void resetBoard();
        sf::Vector2i getMouseToFileRank(const sf::Event& event) const;
        sf::Texture createBoardBack() const;
    
    //overriden members
    private:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    
    //enums
    private:
        enum colors : uint8_t{
            BlackTile = 0 , WhiteTile, LastFromTile, LastToTile, Selected, Count
        };
    //data members
    private:
        sf::RenderWindow* mWindow;
        TextureHolder* mTextureHolder;
        int tile_size; 
        sf::Vector2i mLastFrom, mLastTo, mSelected;
        std::array<sf::Color, colors::Count> mColors;
        std::vector<Coin> mPieces;
        sf::Texture mBoardBackground;
};


#endif