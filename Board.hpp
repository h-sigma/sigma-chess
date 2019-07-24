#ifndef GUI_BOARD_HPP
#define GUI_BOARD_HPP

#include <array>    

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
        
    public:     //constructors
        explicit Board();
        explicit Board(const std::array<Piece , 64>&);
        explicit Board( Board&& );
    public:     //publically callable members
        void run();
    private:    //lifetime of board
        void loadResources();
        void resetBoard();

        bool handleEvents(const sf::Event& event);
        bool update(sf::Time time);
        void render();

        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    private:    //operations on board
        Piece get(uint8_t col, uint8_t row) const;
        void set(uint8_t col, uint8_t row, Piece piece);
        void move(uint8_t fromcol, uint8_t fromrow, uint8_t tocol, uint8_t torow);
    private:
        enum row : uint8_t{
            A = 0 , B , C , D , E , F , G , H
        };
        enum colors : uint8_t{
            BlackTile = 0 , WhiteTile, LastFromTile, LastToTile, Selected, Count
        };
    private:
        std::array<bool, 64> board_back = {
            true, false, true, false, true, false, true, false,
            false, true, false, true, false, true, false, true,
            true, false, true, false, true, false, true, false,
            false, true, false, true, false, true, false, true,
            true, false, true, false, true, false, true, false,
            false, true, false, true, false, true, false, true,
            true, false, true, false, true, false, true, false,
            false, true, false, true, false, true, false, true
        };
    private:
        sf::RenderWindow mWindow;
        int8_t mLastFrom, mLastTo, mSelected;
        std::array<sf::Color, colors::Count> mColors;
        std::array<sf::Texture , Piece::totalPieces> mTexture;
        std::array<sf::Sprite , Piece::totalPieces> mPieces;
        std::array<Piece , 64> mBoard;
        const float tile_size; 
        /*
        *   Board to array co-ordinates: (Uses enum row)
        *   a1 = [A][0U]
        *   h1 = [H][0U]
        *   a8 = [A][7U]
        *   h6 = [H][5U]
        */
};

#endif