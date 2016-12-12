//
//  WordTile.cpp
//  clicky
//
//  Created by Pradyut Panda on 10/23/16.
//
//

#include <math.h>
#include "WordTile.h"

USING_NS_CC;


// Creates a word tile with an image filename
WordTile* WordTile::create(const std::string& filename)
{
	WordTile *pRet = new(std::nothrow) WordTile();
    if (pRet && pRet->init())
    {
    	pRet->setTexture(filename);
        pRet->autorelease();
        return pRet;
    }
    else
    {
        delete pRet;
        pRet = nullptr;
        return nullptr;
    }
}

bool WordTile::init()
{
	if ( !Sprite::init() )
    {
        return false;
    }
    
    reset();
    addEventListener();
    return true;
}


void WordTile::reset()
{
	_position = Vec2::ZERO;
    _velocity = Vec2::ZERO;
    _angle = rand() % 180;

    // position the sprite on the center of the screen
    Sprite::setPosition(_position);
}

void WordTile::addEventListener()
{
	// add evert listeners here
    auto dispatcher = Director::getInstance()->getEventDispatcher();

    /*auto callbackMouseDown = [](EventMouse* event){
        //this->setTimerText(*(float *)event->getUserData()); 
        // need to find the GameUILayer
        float x = event->getCursorX();
        CCLOG( " hello world - in a mouse callback ! (%f) " , x );
    };

    auto listener = EventListenerMouse::create();
    listener->onMouseDown = callbackMouseDown;
    dispatcher->addEventListenerWithFixedPriority(listener, 10);*/
    
    auto listener1 = EventListenerTouchOneByOne::create();
    
    listener1->onTouchBegan = [this](Touch* touch, Event* event){
        //char a = getClickedTileTouch(event);
        CCLOG(" on touch began .... %c", this->_letter );
        return true;
    };
    //_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, this);
}

// set the letter to draw , figure out the rect and set that too
void WordTile::setLetter(char letter)
{
	 // set the sprite frame rect based on the letter 
    _letter = letter;
    int letterOffset = letter - 'a';

    // find texture row 
    int textureRow = floor(letterOffset / 10);
    int textureCol = letterOffset % 10;


    // set the rectangle for the sprite frame to match the letter
    this->setTextureRect(Rect(TILE_SIZE*textureCol, TILE_SIZE*textureRow, TILE_SIZE, TILE_SIZE));
}


// update the tile and move as needed 
void WordTile::update( float delta )
{
	_angle += HOVER_SPEED * delta;
    if ( _angle > 360.0f )
    {
        _angle = 360.0f - _angle;
    }
	float cosAngle = cos(_angle * 3.14f / 180.0f);
    Vec2 newPos = _position;
	newPos.y += HOVER_AMP * cosAngle;
	Sprite::setPosition(newPos);
    //_position.y += HOVER_AMP * cosAngle;
    //setPosition(_position);
}


void WordTile::setPosition(const Vec2& pos)
{
	this->_position = pos;
	Sprite::setPosition(pos);
}
