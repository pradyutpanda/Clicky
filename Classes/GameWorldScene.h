//
//  GameWorldScene.h
//  
//
//  Created by Pradyut Panda on 7/25/16.
//
//

#ifndef ____GameWorldScene__
#define ____GameWorldScene__

#include "cocos2d.h"
#include "GameLayer.h"
#include "GameUILayer.h"


class GameWorldScene
{
public:
    
    static const int NUM_SPRITES = -1;
    
    static cocos2d::Scene* createScene();

    static GameUILayer* getGameUILayer() 
    {
    	return _gameUILayer;
    }

private:
	static GameUILayer*			_gameUILayer;
	static cocos2d::Layer*		_gameLayer;

};


#endif /* defined(____GameWorldScene__) */
