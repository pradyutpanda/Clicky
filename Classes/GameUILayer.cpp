//
//  GameUILayer.cpp
//  clicky
//
//  Created by Pradyut Panda on 10/24/16.
//
//

#include "GameUILayer.h"
#include "TileManager.h"
#include "GameManager.h"


USING_NS_CC;


// on "init" you need to initialize your instance
bool GameUILayer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    buildGameUI();

    // add evert listeners here
    auto dispatcher = Director::getInstance()->getEventDispatcher();

    // callback for custom event to set score 
    auto callbackScore = [this](EventCustom* event){ 
        float scoreValue = *((int *)event->getUserData());
        this->setScoreText(scoreValue);
    };
    auto listenerScore = EventListenerCustom::create(GameManager::eventNameSetScore, callbackScore);
    dispatcher->addEventListenerWithFixedPriority(listenerScore, 1);    

    // callback for custom event to set timer
    auto callbackTimer = [this](EventCustom* event){ 
        float timerValue = *((float *)event->getUserData());
        this->setTimerText(timerValue); 
    };
    auto listenerTimer = EventListenerCustom::create(GameManager::eventNameSetTimer, callbackTimer);
    dispatcher->addEventListenerWithFixedPriority(listenerTimer, 1);


    
    
    return true;
}


void GameUILayer::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}


void GameUILayer::buildGameUI()
{   
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeButton = MenuItemImage::create(     "CloseNormal.png",
                                                    "CloseSelected.png",
                                                    CC_CALLBACK_1(GameUILayer::menuCloseCallback, this));
    
    closeButton->setPosition(Vec2(origin.x + visibleSize.width - closeButton->getContentSize().width/2 ,
                                  origin.y + closeButton->getContentSize().height/2));
    
    auto menu = Menu::create(closeButton, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    _scoreLabel = Label::createWithTTF("Score : 0.0", "fonts/Marker Felt.ttf", 20);
    _scoreLabel->setPosition( Vec2(origin.x + visibleSize.width/5,
                                  origin.y + visibleSize.height - _scoreLabel->getContentSize().height));
    this->addChild(_scoreLabel, 1);
    
    _timerLabel = Label::createWithTTF("Time : 0.0", "fonts/Marker Felt.ttf", 20);
    _timerLabel->setPosition( Vec2(origin.x + 4*visibleSize.width/5,
                                 origin.y + visibleSize.height - _timerLabel->getContentSize().height));
    this->addChild(_timerLabel, 1);

    // letters that the player has clicked on so far 
    _currentWordLabel = Label::createWithTTF("ABCDEF", "fonts/Marker Felt.ttf", 24);
    _currentWordLabel->setPosition( Vec2(origin.x + 1*visibleSize.width/2,
                                 origin.y + visibleSize.height - _currentWordLabel->getContentSize().height));
    this->addChild(_currentWordLabel, 1);
}    
   
 
void GameUILayer::setScoreText(int newScore)
{
    CCLOG(" score is now at %d", newScore );
    std::string scoreString = "Score: ";
    scoreString += std::to_string(newScore);
    _scoreLabel->setString(scoreString);
}

void GameUILayer::setTimerText(float newTimerValue )
{
    //CCLOG(" timer is now at %f", newTimerValue );
    std::string timerString = "Time: ";
    timerString += std::to_string((int)newTimerValue);
    _timerLabel->setString(timerString);
}

void GameUILayer::setCurrentWordText(std::string& word )
{
    _currentWordLabel->setString(word);
}
