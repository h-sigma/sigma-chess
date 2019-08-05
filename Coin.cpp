#include "Coin.hpp"
#include "Utility.hpp"
#include "Board.hpp"

#include "UCI.hpp"

#include <iostream>

Coin::Coin(Piece piece, Board* board, sf::Vector2u cords, sfmlContext context) 
: mType(piece)
, mBoard(board)
, mPos(cords)
, mContext(context)
, mSprite( context.mTextureHolder->get( pieceToTexture(piece) ) )
, mIsGrabbed(false)
{
    //centerOrigin(mSprite);
    setSize(context.tilesize);
    setPosition( sf::Vector2f( mPos.x * context.tilesize , (7 - mPos.y) * context.tilesize ) ) ;
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
        vec = static_cast<sf::Vector2f> ( sf::Mouse::getPosition(*mContext.mWindow) ) - vec - sf::Vector2f(mContext.tilesize/2, mContext.tilesize/2);
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
        if(mContext.pieceDropCall != nullptr)
        if(!mContext.pieceDropCall(from, to))
            return;

        mBoard->capture(to);
        sf::Vector2f fromvec = getPosition();
        sf::Vector2f tovec {( static_cast<float>(to.x) - mPos.x) * mContext.tilesize ,  -( static_cast<float>(to.y) - mPos.y) * mContext.tilesize } ;
        setPosition(tovec + fromvec);
        mPos = to;

        mBoard->setLast( from, to );
        mBoard->setSelected( std::nullopt );
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

void Coin::setGrabbed(bool val) 
{
    mIsGrabbed = val;
}

void Coin::handleEvent( const sf::Event& event, sf::Vector2u pos)
{
    if(event.type == sf::Event::MouseButtonReleased )
    {
        //std::cout << "Released: " << std::endl;
        if(mIsGrabbed && pos != mPos)
        {
            mIsGrabbed = false;
            move(mPos, pos);
        }
        else if(mIsGrabbed && pos == mPos)
        {
            mBoard->setSelected(std::nullopt);
            mIsGrabbed = false;
        }
    }
    else if(event.type == sf::Event::MouseButtonPressed)
    {
        if(mIsGrabbed)  //grabbed but another mouse key is clicked
        {
            mIsGrabbed = false;
            mBoard->setSelected( std::nullopt );
        }
        else if(pos == mPos && !mIsGrabbed) //released back
        {
            mIsGrabbed = true;
            mBoard->setSelected( mPos );
        }
    }
}
