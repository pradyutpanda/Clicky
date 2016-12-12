//
//  GameWorldScene.cpp
//  
//
//  Created by Pradyut Panda on 7/25/16.
//
//

#include "GameWorldScene.h"



USING_NS_CC;

// static member definitions
GameUILayer* GameWorldScene::_gameUILayer = NULL;
cocos2d::Layer* GameWorldScene::_gameLayer = NULL;


Scene* GameWorldScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // create and add the UI layer
    _gameUILayer = GameUILayer::create();
    scene->addChild(_gameUILayer);

    // create and add the game layer
    _gameLayer = GameLayer::create();
    scene->addChild(_gameLayer);
    
    // return the scene
    return scene;
}
