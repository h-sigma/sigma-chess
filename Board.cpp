#include "Board.hpp"
#include "Utility.hpp"

#include <iostream>
#include <algorithm>

#include <SFML/Window/Event.hpp>
#include <SFML/System/Time.hpp>

Board::Board( sf::RenderWindow* window, TextureHolder* holder, int tsize) 
: mWindow(window )
, mTextureHolder( holder )
, tile_size(tsize)
, mLastFrom(-1 , -1) 
, mLastTo(-1 , -1)
, mSelected(-1 , -1)
, mColors{ sf::Color::Green , sf::Color::White , sf::Color(100, 100, 150) , sf::Color(100, 100, 250), sf::Color(200, 100 , 50) }
, mBoardBackground(createBoardBack())
{
    loadResources();
    resetBoard();
}


void Board::set(sf::Vector2u pos, Piece piece)
{
    mPieces.push_back( Coin{piece , this, tile_size , pos , mWindow , mTextureHolder} );
}

void Board::move( sf::Vector2u from, sf::Vector2u to)
{
    mLastFrom = static_cast<sf::Vector2i>(from);
    mLastTo = static_cast<sf::Vector2i>(to);
    mSelected = sf::Vector2i{-1 , -1};

    capture(to);

    for( auto& piece : mPieces)
        piece.move(from, to);
    
}

void Board::capture(sf::Vector2u at)
{
    auto ptr = std::remove_if( mPieces.begin() , mPieces.end() , [& at](const Coin& ptr){
        if(at == ptr.getFileRank())
            return true;
        return false;
    });
    mPieces.erase(ptr, mPieces.end());
}

void Board::setLast(sf::Vector2i from, sf::Vector2i to)
{
    mLastFrom = from;
    mLastTo = to;
}

void Board::setSelected(sf::Vector2i at)
{
    mSelected = at;
}

void Board::handleEvent(const sf::Event& event) 
{
    sf::Vector2i vec = getMouseToFileRank(event);
    if(vec.x == -1 && event.type == sf::Event::MouseButtonPressed)
        return;
    for(auto& piece : mPieces)
    {
        piece.handleEvent(event , static_cast<sf::Vector2u>(vec) );
    }
}


void Board::loadResources()
{
    mTextureHolder->load(Textures::blackBishop, "Sprites/blackBishop.png");
    mTextureHolder->load(Textures::blackKing, "Sprites/blackKing.png");
    mTextureHolder->load(Textures::blackKnight, "Sprites/blackKnight.png");
    mTextureHolder->load(Textures::blackPawn, "Sprites/blackPawn.png");
    mTextureHolder->load(Textures::blackQueen, "Sprites/blackQueen.png");
    mTextureHolder->load(Textures::blackRook, "Sprites/blackRook.png");
    
    mTextureHolder->load(Textures::whiteBishop, "Sprites/whiteBishop.png");
    mTextureHolder->load(Textures::whiteKing, "Sprites/whiteKing.png");
    mTextureHolder->load(Textures::whiteKnight, "Sprites/whiteKnight.png");
    mTextureHolder->load(Textures::whitePawn, "Sprites/whitePawn.png");
    mTextureHolder->load(Textures::whiteQueen, "Sprites/whiteQueen.png");
    mTextureHolder->load(Textures::whiteRook, "Sprites/whiteRook.png"); 

    mTextureHolder->get(Textures::blackBishop).setSmooth(true);
    mTextureHolder->get(Textures::blackKing).setSmooth(true);
    mTextureHolder->get(Textures::blackKnight).setSmooth(true);
    mTextureHolder->get(Textures::blackPawn).setSmooth(true);
    mTextureHolder->get(Textures::blackQueen).setSmooth(true);
    mTextureHolder->get(Textures::blackRook).setSmooth(true);
    
    mTextureHolder->get(Textures::whiteBishop).setSmooth(true);
    mTextureHolder->get(Textures::whiteKing).setSmooth(true);
    mTextureHolder->get(Textures::whiteKnight).setSmooth(true);
    mTextureHolder->get(Textures::whitePawn).setSmooth(true);
    mTextureHolder->get(Textures::whiteQueen).setSmooth(true);
    mTextureHolder->get(Textures::whiteRook).setSmooth(true);
    

}

void Board::resetBoard()
{
    mPieces.clear(); 

    set( {0u , 7u} , Piece::blackRook);     //note that 1..8 indexing is used
    set( {1u , 7u} , Piece::blackKnight);
    set( {2u , 7u} , Piece::blackBishop);
    set( {3u , 7u} , Piece::blackQueen);
    set( {4u , 7u} , Piece::blackKing);
    set( {5u , 7u} , Piece::blackBishop);
    set( {6u , 7u} , Piece::blackKnight);
    set( {7u , 7u} , Piece::blackRook);

    for(uint8_t i = 0u ; i <= 7u ; i++)   //stronger coupling here as it's not dependent on enum row
        set( {i , 6u} , Piece::blackPawn);
    
    set( {0u , 0u} , Piece::whiteRook);
    set( {1u , 0u} , Piece::whiteKnight);
    set( {2u , 0u} , Piece::whiteBishop);
    set( {3u , 0u} , Piece::whiteQueen);
    set( {4u , 0u} , Piece::whiteKing);
    set( {5u , 0u} , Piece::whiteBishop);
    set( {6u , 0u} , Piece::whiteKnight);
    set( {7u , 0u} , Piece::whiteRook);

    for(uint8_t i = 0u ; i <= 7u ; i++)   //stronger coupling here as it's not dependent on enum row
        set( {i , 1u} , Piece::whitePawn);

    for(auto& piece : mPieces)
    {
        piece.setSize(tile_size);
        //centerOrigin(piece);
    }
}

sf::Vector2i Board::getMouseToFileRank(const sf::Event& event) const
{
    sf::Vector2i vec {event.mouseButton.x, event.mouseButton.y};

    vec -= static_cast<sf::Vector2i>( this->getPosition() );

    vec.x = vec.x / tile_size;
    vec.y = vec.y / tile_size;

    vec.y = 7 - vec.y;

    if(vec.x < 0 || vec.x >= 8 || vec.y < 0 || vec.y >= 8 )
    return {-1 , -1};

    return vec;
}

sf::Texture Board::createBoardBack() const
{

    sf::RenderTexture target; 
    target.create(tile_size * 8 , tile_size * 8);

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

    static std::array<sf::RectangleShape, 2> tile;
    tile.fill( sf::RectangleShape{sf::Vector2f(tile_size, tile_size)} );

    tile[0].setFillColor(mColors[colors::BlackTile]);
    tile[1].setFillColor(mColors[colors::WhiteTile]); 

    float x = 0.f , y = 0.f;

    for(int8_t arg = 0 ; arg < 64 ; arg++)
    {
        x = tile_size * (arg%8);
        y = tile_size * (arg/8);

        if(board_back[arg] == false)
        {
            tile[0].setPosition( x ,y);
            target.draw(tile[0]);
        }
        else
        {
            tile[1].setPosition( x ,y);
            target.draw(tile[1]);
        }
    }

    target.setSmooth(true);

    target.display();

    return std::move(target.getTexture());
}   


void Board::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    //draw board
    target.draw(sf::Sprite{mBoardBackground}, states);

    //highlight tiles
    static std::array<sf::RectangleShape, 3> tile;
    tile.fill( sf::RectangleShape{sf::Vector2f(tile_size, tile_size)} );

    tile[0].setFillColor(mColors[colors::LastFromTile]);
    tile[1].setFillColor(mColors[colors::LastToTile]);
    tile[2].setFillColor(mColors[colors::Selected]);

    states.blendMode = sf::BlendAlpha;
    if(mLastFrom.x > -1)
    {
        tile[0].setPosition( sf::Vector2f(mLastFrom.x * tile_size, (7 - mLastFrom.y ) * tile_size)) ;
        target.draw(tile[0] , states);
    }
    
    if(mLastTo.x > -1)
    {
        tile[1].setPosition( sf::Vector2f(mLastTo.x * tile_size, (7 - mLastTo.y ) * tile_size));
        target.draw(tile[1] , states);
    }
    
    if(mSelected.x > -1)
    {
        tile[2].setPosition( sf::Vector2f(mSelected.x * tile_size, (7 - mSelected.y ) * tile_size));
        target.draw(tile[2] , states);
    }

    const Coin* ptr = nullptr;
    for(const auto& piece : mPieces)
    {
        if( piece.isGrabbed() )
            ptr = &piece;
        else
            target.draw(piece, states);
    }

    if(ptr != nullptr)
        target.draw( *ptr, states);

}
