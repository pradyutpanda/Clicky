//
//  GameLayer.hpp
//  clicky
//
//  Created by Pradyut Panda on 10/24/16.
//
//

#ifndef ____GameLayer_h__
#define ____GameLayer_h__

#include "cocos2d.h"
#include "TileManager.h"
#include "GameManager.h"



class GameLayer : public cocos2d::Layer
{
public:
    
    static const int NUM_SPRITES = -1;
    
    virtual bool init();
    virtual void update( float delta );
    
    // implement the "static create()" method manually
    CREATE_FUNC(GameLayer);

private:
	TileManager * 		_tileManager; 
	GameManager	* 		_gameManager;

};

#endif /* ____GameLayer_h__ */
