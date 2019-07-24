#include "Coin.hpp"
#include "Utility.hpp"
#include "Board.hpp"

Coin::Coin(Piece piece, Board* board, int size, sf::Vector2u cords, sf::RenderWindow* window, TextureHolder* tholder) 
: mType(piece)
, mBoard(board)
, mPos(cords)
, tile_size(size)
, mWindow(window)
, mSprite( tholder->get( pieceToTexture(piece) ) )
, mIsGrabbed(false)
{
    //centerOrigin(mSprite);
    setSize(size);
    setPosition( sf::Vector2f( mPos.x * tile_size , (7 - mPos.y) * tile_size ) ) ;
}

void Coin::setSize(float size)
{
    fixScale(mSprite , size, size);
}

void Coin::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    if(mIsGrabbed)
    {
        sf::Transform transform = sf::Transform::Identity;
        transform *= states.transform;
        sf::Vector2f vec = transform * sf::Vector2f();
        vec = static_cast<sf::Vector2f> ( sf::Mouse::getPosition(*mWindow) ) - vec - sf::Vector2f(tile_size/2, tile_size/2);
        states.transform = states.transform.translate(vec).scale(1.25f, 1.25f);   
        target.draw(mSprite, states);
    }
    else
    {
        target.draw(mSprite , states);
    }
}

void Coin::move( sf::Vector2u from, sf::Vector2u to) 
{
    if(mPos == from)
    {
        sf::Vector2f fromvec = getPosition();
        sf::Vector2f tovec {( static_cast<float>(to.x) - mPos.x) * tile_size ,  -( static_cast<float>(to.y) - mPos.y) * tile_size } ;
        setPosition(tovec + fromvec);
        mPos = to;
    }
}

sf::Vector2u Coin::getFileRank() const
{
    return mPos;
}

bool Coin::isGrabbed() const 
{
    return mIsGrabbed;
}

void Coin::handleEvent( const sf::Event& event, sf::Vector2u pos)
{
    if(event.type == sf::Event::MouseButtonReleased)
    {
        if(mIsGrabbed && pos != mPos)
        {
            mIsGrabbed = false;
            mBoard->capture(pos);
            mBoard->setLast( static_cast<sf::Vector2i>(mPos), static_cast<sf::Vector2i>(pos) );
            mBoard->setSelected( {-1, -1} );
            move(mPos, pos);
        }
        else if(mIsGrabbed && pos == mPos)
        {
            mBoard->setSelected( {-1, -1} );
        }
        mIsGrabbed = false;
    }
    else if(event.type == sf::Event::MouseButtonPressed)
    {
        if(mIsGrabbed)
        {
            mIsGrabbed = false;
            mBoard->setSelected( {-1,-1} );
        }
        else if(pos == mPos && !mIsGrabbed)
        {
            mIsGrabbed = true;
            mBoard->setSelected( static_cast<sf::Vector2i>(mPos) );
        }
        else
        {
            mIsGrabbed = false;
        }
    }
}
