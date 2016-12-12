//
//  GameLayer.cpp
//  clicky
//
//  Created by Pradyut Panda on 10/24/16.
//
//

#include "GameLayer.h"


// on "init" you need to initialize your instance
bool GameLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    _tileManager = TileManager::create(this);
    _gameManager = GameManager::create();
    _gameManager->startRound();

    this->scheduleUpdate();
    return true;
}

void GameLayer::update(float delta)
{
	_tileManager->update(delta);
	_gameManager->update(delta);
}
