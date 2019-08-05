#ifndef GUI_BOARD_HPP
#define GUI_BOARD_HPP

#include <array>    
#include <functional>
#include <optional>

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
    public:
        
    //constructors
    public:     
        explicit Board(sfmlContext context);

    //operations on board
    public:     
        void set(sf::Vector2u pos, Piece piece);
        void move( sf::Vector2u from, sf::Vector2u to);
        void capture( sf::Vector2u at);
        void setLast(std::optional<sf::Vector2u>, std::optional<sf::Vector2u>);
        void setSelected(std::optional<sf::Vector2u>);
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
        sfmlContext mContext;
        int tile_size; 
        std::optional<sf::Vector2u> mLastFrom, mLastTo, mSelected;
        std::array<sf::Color, colors::Count> mColors;
        std::vector<Coin> mPieces;
        sf::Texture mBoardBackground;
};


#endif