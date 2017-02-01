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
#include "EventDispatch.h"
#include "ui/CocosGUI.h"


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
    EventDispatch::listenCustomEvent(EventDispatch::eventNameSetScore, callbackScore);
    

    // callback for custom event to set timer
    auto callbackTimer = [this](EventCustom* event){ 
        float timerValue = *((float *)event->getUserData());
        this->setTimerText(timerValue); 
    };
    EventDispatch::listenCustomEvent(EventDispatch::eventNameSetTimer, callbackTimer);


     // callback for custom event to set current guess word
    auto callbackWord = [this](EventCustom* event){ 
        std::string word = *((std::string *)event->getUserData());
        this->setCurrentWordText(word);
    };
    EventDispatch::listenCustomEvent(EventDispatch::eventNameSetWord, callbackWord);
    

    // callback for custom event to set which word we are on
    auto callbackSetWordIndex = [this](EventCustom* event){ 
        int* numbers = ((int *)event->getUserData());
        this->setWordIndexText(numbers[0], numbers[1]);
    };
    EventDispatch::listenCustomEvent(EventDispatch::eventNameSetWordIndex, callbackSetWordIndex);
    

    auto callbackShowPlayerFeedback = [this] (EventCustom* event) {
        std::string word = *((std::string *)event->getUserData());
        this->showPlayerFeedback(word);
    };
    EventDispatch::listenCustomEvent(EventDispatch::eventNameShowPlayerFeedback, callbackShowPlayerFeedback);
    
    return true;
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

    // Label for the player score
    _scoreLabel = Label::createWithTTF("Score : 0", "fonts/Marker Felt.ttf", 20);
    _scoreLabel->setPosition( Vec2(origin.x + visibleSize.width/5,
                                  origin.y + visibleSize.height - _scoreLabel->getContentSize().height));
    this->addChild(_scoreLabel, 1);

    // Label for the which word in the round 
    _wordIndexLabel = Label::createWithTTF("Word : ", "fonts/Marker Felt.ttf", 20);
    _wordIndexLabel->setPosition( Vec2(origin.x + visibleSize.width/5,
                                  origin.y + visibleSize.height*0.95 - _wordIndexLabel->getContentSize().height));
    this->addChild(_wordIndexLabel, 1);
    
    // Label for the time left
    _timerLabel = Label::createWithTTF("Time : 0.0", "fonts/Marker Felt.ttf", 20);
    _timerLabel->setPosition( Vec2(origin.x + 4*visibleSize.width/5,
                                 origin.y + visibleSize.height - _timerLabel->getContentSize().height));
    this->addChild(_timerLabel, 1);

    // letters that the player has clicked on so far 
    _currentWordLabel = Label::createWithTTF("ABCDEF", "fonts/Marker Felt.ttf", 24);
    _currentWordLabel->setPosition( Vec2(origin.x + 1*visibleSize.width/2,
                                 origin.y + visibleSize.height - _currentWordLabel->getContentSize().height));
    this->addChild(_currentWordLabel, 1);


    /*auto createButton = [] (std::string title, int posX) -> cocos2d::ui::Button {
        auto newButton = cocos2d::ui::Button::create("CloseNormal.png", "CloseSelected.png", "CloseSelected.png");

        newButton->setTitleText(title);
        newButton->setTitleFontSize(16);
        newButton->setPosition(Vec2(posX,100));
        return newButton;
    };*/
    
    // Button to clean the current guess 
    auto clearButton = cocos2d::ui::Button::create("CloseNormal.png", "CloseSelected.png", "CloseSelected.png");

    clearButton->setTitleText("[Clear     Guess]");
    clearButton->setTitleFontSize(16);
    clearButton->setPosition(Vec2(75,100));

    auto clearButtonTouchCallback = [this] (Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
        switch (type)
        {
            case ui::Widget::TouchEventType::ENDED:
                CCLOG(" Button 1 clicked" );
                break;
        };
    };
    clearButton->addClickEventListener(CC_CALLBACK_1(GameUILayer::clearButtonClickCallback, this));
    //button->addTouchEventListener(CC_CALLBACK_2(GameUILayer::clearButtonClickCallback, this));
    //button->addTouchEventListener(clearButtonTouchCallback);
    this->addChild(clearButton);



    // Button to move to the next word 
    auto nextButton = cocos2d::ui::Button::create("CloseNormal.png", "CloseSelected.png", "CloseSelected.png");

    nextButton->setTitleText("[Next     Word]");
    nextButton->setTitleFontSize(16);
    nextButton->setPosition(Vec2(origin.x + visibleSize.width-100,100));
    nextButton->addClickEventListener(CC_CALLBACK_1(GameUILayer::nextButtonClickCallback, this));
    this->addChild(nextButton);
}    


void GameUILayer::showPlayerFeedback(std::string feedback)
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // Label for the player score
    auto wordOKLabel = Label::createWithTTF(feedback, "fonts/Marker Felt.ttf", 30);
    wordOKLabel->setPosition( Vec2(origin.x + visibleSize.width/2,
                                  origin.y + 3*visibleSize.height/4) );
    this->addChild(wordOKLabel, 1);

    // Scale uniformly up and then down
    auto scaleByUp = ScaleBy::create(0.5f, 3.0f);
    auto scaleByDown = ScaleBy::create(0.25f, 0.33f);
    auto callbackRemove = CallFunc::create([this, wordOKLabel](){
        this->removeChild(wordOKLabel);
        log("Removed!");
    });

    // create a sequence with the actions and callbacks
    auto seq = Sequence::create(scaleByUp, scaleByDown, callbackRemove, nullptr);
    wordOKLabel->runAction(seq);
}
   
 
void GameUILayer::setScoreText(int newScore)
{
    CCLOG(" score is now at %d", newScore );
    std::string scoreString = "Score: ";
    scoreString += std::to_string(newScore);
    _scoreLabel->setString(scoreString);

    auto scaleByUp = ScaleBy::create(0.2f, 2.0f);
    auto scaleByDown = ScaleBy::create(0.1f, 0.5f);
    auto seq = Sequence::create(scaleByUp, scaleByDown, nullptr);
    _scoreLabel->runAction(seq);
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

void GameUILayer::setWordIndexText(int index, int total )
{
    std::string wordIndexString = "Word: ";
    wordIndexString += std::to_string(index) + "/" + std::to_string(total);
    _wordIndexLabel->setString(wordIndexString);
}


// Callback functions live here
/*void GameUILayer::clearButtonTouchCallback(Ref* sender, Widget::TouchEventType type)
{
    switch (type)
    {
        case ui::Widget::TouchEventType::ENDED:
            CCLOG(" Button 1 clicked" );
            break;
    };
}*/

// Callback functions live here
void GameUILayer::clearButtonClickCallback(Ref* sender)
{
    EventDispatch::dispatchCustomEvent(EventDispatch::eventNameClearWord, nullptr );
}

void GameUILayer::nextButtonClickCallback(Ref* sender)
{
    EventDispatch::dispatchCustomEvent(EventDispatch::eventNameNextWord, nullptr );
}

void GameUILayer::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
