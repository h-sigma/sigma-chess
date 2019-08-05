#include "Board.hpp"
#include "Utility.hpp"

#include <iostream>
#include <algorithm>
#include <optional>

#include <SFML/Window/Event.hpp>
#include <SFML/System/Time.hpp>

Board::Board(sfmlContext context) 
: mContext(context)
, tile_size(context.tilesize)
, mLastFrom(std::nullopt) 
, mLastTo(std::nullopt)
, mSelected(std::nullopt)
, mColors{ sf::Color::Green , sf::Color::White , sf::Color(100, 100, 150) , sf::Color(100, 100, 250), sf::Color(200, 100 , 50) }
, mBoardBackground(createBoardBack())
{
    loadResources();
    resetBoard();
}


void Board::set(sf::Vector2u pos, Piece piece)
{
    mPieces.push_back( Coin{piece , this, pos , mContext} );
}

void Board::move(sf::Vector2u from, sf::Vector2u to)
{
    if(mContext.pieceDropCall == nullptr)
    if(!mContext.pieceDropCall(from, to))
        return;
    mLastFrom = from;
    mLastTo = to;
    mSelected = std::nullopt;

    capture(to);

    for( auto& piece : mPieces)
        piece.move(from, to);
}

void Board::capture(sf::Vector2u at)
{
    auto newend = std::remove_if( mPieces.begin() , mPieces.end() , [& at](const Coin& ptr){
        if(at == ptr.getFileRank())
            return true;
        return false;
    });
    mPieces.erase(newend, mPieces.end());
}

void Board::setLast(std::optional<sf::Vector2u> from, std::optional<sf::Vector2u> to)
{
    mLastFrom = from;
    mLastTo = to;
}

void Board::setSelected(std::optional<sf::Vector2u> at)
{
    mSelected = at;
}

void Board::handleEvent(const sf::Event& event) 
{
    if(event.type == sf::Event::MouseLeft)  
        for(auto& piece : mPieces)
            piece.setGrabbed(false);
    else
    {
        sf::Vector2i vec = getMouseToFileRank(event);
        if(vec.x == -1)
            return;
        for(auto& piece : mPieces)
        {
            piece.handleEvent(event , static_cast<sf::Vector2u>(vec) );
        }
            
    }  
}


void Board::loadResources()
{
    TextureHolder& th = *mContext.mTextureHolder;
    th.load(Textures::blackBishop, "Sprites/blackBishop.png");
    th.load(Textures::blackKing, "Sprites/blackKing.png");
    th.load(Textures::blackKnight, "Sprites/blackKnight.png");
    th.load(Textures::blackPawn, "Sprites/blackPawn.png");
    th.load(Textures::blackQueen, "Sprites/blackQueen.png");
    th.load(Textures::blackRook, "Sprites/blackRook.png");
    
    th.load(Textures::whiteBishop, "Sprites/whiteBishop.png");
    th.load(Textures::whiteKing, "Sprites/whiteKing.png");
    th.load(Textures::whiteKnight, "Sprites/whiteKnight.png");
    th.load(Textures::whitePawn, "Sprites/whitePawn.png");
    th.load(Textures::whiteQueen, "Sprites/whiteQueen.png");
    th.load(Textures::whiteRook, "Sprites/whiteRook.png"); 

    th.get(Textures::blackBishop).setSmooth(true);
    th.get(Textures::blackKing).setSmooth(true);
    th.get(Textures::blackKnight).setSmooth(true);
    th.get(Textures::blackPawn).setSmooth(true);
    th.get(Textures::blackQueen).setSmooth(true);
    th.get(Textures::blackRook).setSmooth(true);
    
    th.get(Textures::whiteBishop).setSmooth(true);
    th.get(Textures::whiteKing).setSmooth(true);
    th.get(Textures::whiteKnight).setSmooth(true);
    th.get(Textures::whitePawn).setSmooth(true);
    th.get(Textures::whiteQueen).setSmooth(true);
    th.get(Textures::whiteRook).setSmooth(true);
    

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
    setLast({},{});
    setSelected({});
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
    if(mLastFrom.has_value())
    {
        tile[0].setPosition( sf::Vector2f(mLastFrom->x * tile_size, (7 - mLastFrom->y ) * tile_size)) ;
        target.draw(tile[0] , states);
    }
    
    if(mLastTo.has_value())
    {
        tile[1].setPosition( sf::Vector2f(mLastTo->x * tile_size, (7 - mLastTo->y ) * tile_size));
        target.draw(tile[1] , states);
    }
    
    if(mSelected.has_value())
    {
        tile[2].setPosition( sf::Vector2f(mSelected->x * tile_size, (7 - mSelected->y ) * tile_size));
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
