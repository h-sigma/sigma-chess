#include "Board.hpp"
#include "Utility.hpp"

#include <iostream>

#include <SFML/Window/Event.hpp>
#include <SFML/System/Time.hpp>

Board::Board() 
: mWindow(sf::VideoMode(600,600) , "Chess GUI", sf::Style::Close )
, mLastFrom(-1) 
, mLastTo(-1)
, mSelected(-1)
, mColors{ sf::Color::Green , sf::Color::White , sf::Color(0, 0, 50, 150) , sf::Color(0, 0, 100, 200), sf::Color(200, 100 , 0) }
, tile_size(60.f)
{
    mBoard.fill(Piece::EMPTY);  //invariant initialization shouldn't depend on another member's definition
    loadResources();
    resetBoard();
}

void Board::loadResources()
{
    mTexture[Piece::blackBishop].loadFromFile("Sprites/blackBishop.png");
    mTexture[Piece::blackKing].loadFromFile("Sprites/blackKing.png");
    mTexture[Piece::blackKnight].loadFromFile("Sprites/blackKnight.png");
    mTexture[Piece::blackPawn].loadFromFile("Sprites/blackPawn.png");
    mTexture[Piece::blackQueen].loadFromFile("Sprites/blackQueen.png");
    mTexture[Piece::blackRook].loadFromFile("Sprites/blackRook.png");
    mTexture[Piece::whiteBishop].loadFromFile("Sprites/whiteBishop.png");
    mTexture[Piece::whiteKing].loadFromFile("Sprites/whiteKing.png");
    mTexture[Piece::whiteKnight].loadFromFile("Sprites/whiteKnight.png");
    mTexture[Piece::whitePawn].loadFromFile("Sprites/whitePawn.png");
    mTexture[Piece::whiteQueen].loadFromFile("Sprites/whiteQueen.png");
    mTexture[Piece::whiteRook].loadFromFile("Sprites/whiteRook.png");https://github.com/h-sigma/sigma-chess

    mPieces[Piece::blackBishop].setTexture(mTexture[Piece::blackBishop]);
    mPieces[Piece::blackKing].setTexture(mTexture[Piece::blackKing]);
    mPieces[Piece::blackKnight].setTexture(mTexture[Piece::blackKnight]);
    mPieces[Piece::blackPawn].setTexture(mTexture[Piece::blackPawn]);
    mPieces[Piece::blackQueen].setTexture(mTexture[Piece::blackQueen]);
    mPieces[Piece::blackRook].setTexture(mTexture[Piece::blackRook]);
    mPieces[Piece::whiteBishop].setTexture(mTexture[Piece::whiteBishop]);
    mPieces[Piece::whiteKing].setTexture(mTexture[Piece::whiteKing]);
    mPieces[Piece::whiteKnight].setTexture(mTexture[Piece::whiteKnight]);
    mPieces[Piece::whitePawn].setTexture(mTexture[Piece::whitePawn]);
    mPieces[Piece::whiteQueen].setTexture(mTexture[Piece::whiteQueen]);
    mPieces[Piece::whiteRook].setTexture(mTexture[Piece::whiteRook]);

    for(auto& piece : mPieces)
    {
        fixScale(piece , tile_size , tile_size);
        //centerOrigin(piece);
    }

}

void Board::resetBoard()
{
    mBoard.fill(Piece::EMPTY); //clear board

    set(A , 8u , Piece::blackRook);     //note that 1..8 indexing is used
    set(B , 8u , Piece::blackKnight);
    set(C , 8u , Piece::blackBishop);
    set(D , 8u , Piece::blackQueen);
    set(E , 8u , Piece::blackKing);
    set(F , 8u , Piece::blackBishop);
    set(G , 8u , Piece::blackKnight);
    set(H , 8u , Piece::blackRook);

    for(uint8_t i = 0 ; i <= 7 ; i++)   //stronger coupling here as it's not dependent on enum row
        set(i , 2u , Piece::whitePawn);
    
    set(A , 1u , Piece::whiteRook);
    set(B , 1u , Piece::whiteKnight);
    set(C , 1u , Piece::whiteBishop);
    set(D , 1u , Piece::whiteQueen);
    set(E , 1u , Piece::whiteKing);
    set(F , 1u , Piece::whiteBishop);
    set(G , 1u , Piece::whiteKnight);
    set(H , 1u , Piece::whiteRook);

    for(uint8_t i = 0 ; i <= 7 ; i++)   //stronger coupling here as it's not dependent on enum row
        set(i , 7u , Piece::blackPawn);
}

void Board::run()
{
    sf::Clock clock;
    sf::Time dt = sf::Time::Zero;
    sf::Event event;
    const sf::Time perframe = sf::seconds(1/60.f);
    bool quit = false;
    while(mWindow.isOpen())
    {
        dt += clock.restart();
        while(dt >= perframe)
        {
            dt -= perframe;
            quit = handleEvents(event);
            update(perframe);
        }
        render();
        if(quit)
            mWindow.close();
    }
}

bool Board::handleEvents(const sf::Event&)
{
    sf::Event evt;
    while(mWindow.pollEvent(evt))
    {
        if(evt.type == sf::Event::KeyReleased && evt.key.code == sf::Keyboard::Escape )
            return true;
        if(evt.type == sf::Event::Closed)
            return true;
        if(evt.type == sf::Event::MouseButtonPressed)
        {
            sf::Vector2i vec = sf::Mouse::getPosition(mWindow);
            vec -= static_cast<sf::Vector2i> (this->getPosition() );
            if(vec.x < 0 || vec.y < 0)
                continue;

            uint8_t row = vec.y / tile_size;
            uint8_t col = vec.x / tile_size;

            if( row >= 8 || col >= 8)
                continue;

            if(mSelected == -1)
            {   //select the piece
                mSelected = row*8 + col;
            }
            else
            {
                if(mSelected == row*8 + col)    //clicked the same piece again
                    mSelected = -1;
                else
                {
                    move(7 - mSelected%8 , 8 - mSelected/8, 7 - col, 8 - row);
                }
                
            }
            
        }
    }
    return false;
}

bool Board::update(sf::Time)
{
    return false;
}

void Board::render()
{
    mWindow.clear();
    mWindow.draw(*this);
    mWindow.display();
}

void Board::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    //draw board
    static std::array<sf::RectangleShape, colors::Count> tile;
    tile.fill( sf::RectangleShape{sf::Vector2f(tile_size, tile_size)} );

    tile[colors::BlackTile].setFillColor(mColors[colors::BlackTile]);
    tile[colors::WhiteTile].setFillColor(mColors[colors::WhiteTile]);
    tile[colors::LastFromTile].setFillColor(mColors[colors::LastFromTile]);
    tile[colors::LastToTile].setFillColor(mColors[colors::LastToTile]);
    tile[colors::Selected].setFillColor(mColors[colors::Selected]);
    

    float x = 0.f , y = 0.f;

    for(int8_t arg = 0 ; arg < 64 ; arg++)
    {
        x = tile_size * (arg%8);
        y = tile_size * (arg/8);

        states.blendMode = sf::BlendAlpha;

        if(board_back[arg] == false)
        {
            tile[colors::BlackTile].setPosition( x ,y);
            target.draw(tile[colors::BlackTile] , states);
        }
        else
        {
            tile[colors::WhiteTile].setPosition( x ,y);
            target.draw(tile[colors::WhiteTile] , states);
        }

        int8_t normalarg = 63 - arg; //the indexing the normal board uses

        if(normalarg == mLastFrom)
        {
            tile[colors::LastFromTile].setPosition( x ,y);
            target.draw(tile[colors::LastFromTile] , states);
        }
        if(normalarg == mLastTo)
        {
            tile[colors::LastToTile].setPosition( x ,y);
            target.draw(tile[colors::LastToTile] , states);
        }
        if(arg == mSelected)
        {
            tile[colors::Selected].setPosition( x ,y);
            target.draw(tile[colors::Selected] , states);
        }
        
        if(mBoard[normalarg] == Piece::EMPTY)
        { /*do nothing*/ }
        else
        {
            states.blendMode = sf::BlendAlpha;
            sf::Sprite piece = mPieces[ mBoard[normalarg] ];
            piece.setPosition(x, y );
            target.draw(piece, states);
        }
        
    }

}

Piece Board::get(uint8_t col, uint8_t row) const
{
    return mBoard[col + ((row-1) * 8)]; //please note that the "-1" converts 1..8 indexing to 0..7
}

void Board::set(uint8_t col, uint8_t row, Piece piece)
{
    mBoard[col + ((row - 1) * 8)] = piece;//please note that the "-1" converts 1..8 indexing to 0..7
}

void Board::move(uint8_t fromcol, uint8_t fromrow, uint8_t tocol, uint8_t torow)
{
    Piece temp = get(fromcol , fromrow);
    set(fromcol , fromrow , Piece::EMPTY);
    set(tocol, torow, temp );
    mLastFrom = fromcol + (fromrow-1)*8;
    mLastTo = tocol + (torow-1)*8;
    mSelected = -1;
}