//
//  GameManager.cpp
//  clicky
//
//  Created by Pradyut Panda on 10/25/16.
//
//

#include "GameManager.h"
#include "GameWorldScene.h"
#include "TileManager.h"
#include "WordSet.h"
#include "WordSetManager.h"


USING_NS_CC;


const float     MAX_TIME_PER_ROUND = 2.0f;     // in seconds 
const int       SCORE_MULTIPLIER = 10;
const int       MAX_WORDS_PER_ROUND = 20;
const float     MAX_TIME_TRANSITION_WORD = 0.5f;    // in seconds 

const int       STATE_GUESS_WORD = 0;
const int       STATE_TRANSITION_OUT_WORD = 1;


const std::string GameManager::eventNameSetTimer = "EventNameSetTimer";
const std::string GameManager::eventNameSetScore = "EventNameSetScore";
GameManager* GameManager::_sharedInstance = NULL;




GameManager::GameManager()
{
    resetValues();
    WordSetManager::create();
}

// create a singleton if it does not exist and return
GameManager* GameManager::create()
{
   if (_sharedInstance)
        return _sharedInstance;

    GameManager *pRet = new(std::nothrow) GameManager();
    if (pRet)
    {
        _sharedInstance = pRet;
        //pRet->autorelease();
        return pRet;
    }
    else
    {
        delete pRet;
        pRet = nullptr;
        return nullptr;
    } 
}

// return the shared instance 
GameManager *GameManager::getInstance()
{
    return _sharedInstance;
}

void GameManager::resetValues()
{
    _state = STATE_GUESS_WORD;
    _timer = 0.0f;
    _score = 0;
    _numWords = 0;
    _updateLabelTimer = 0.0f;
}


// start a new round
void GameManager::startRound()
{
    CCLOG( "Starting a new Round ! ");
    _state = STATE_GUESS_WORD;
    _score = 0;
    _numWords = 0;

    _wordSet = WordSetManager::getInstance()->getActive();
    startWordGuessTime();

    std::string word;
    _wordSet->initRound();
    _wordSet->getNewWordFromSet(word);
    TileManager::getInstance()->spawnNewWord(word, true);
}


void GameManager::endRound()
{
    CCLOG( "Ending a Round ! , total score : %d ", _score );
}


// player found the word, kill timer and give points
void GameManager::wordFound()
{
    endWordGuessTimeRound();
}

// start a new timer to guess the new word in 
void GameManager::startWordGuessTime()
{
    CCLOG( "Starting timer for word %d : ", _numWords );
    // kick off the timer
    _state = STATE_GUESS_WORD;
    _timer = MAX_TIME_PER_ROUND;
    _updateLabelTimer = 0.0;
    std::string blank("---");
    GameWorldScene::getGameUILayer()->setCurrentWordText(blank);

    std::string word;
    _wordSet->getNewWordFromSet(word);
    TileManager::getInstance()->spawnNewWord(word, true);
    TileManager::getInstance()->transitionIn(MAX_TIME_TRANSITION_WORD);
}


void GameManager::endWordGuessTimeRound()
{
    CCLOG( "Stop timer for word %d : ", _numWords );

    // computer the score based on time remaining
    int scoreForWord = (int) (_timer * SCORE_MULTIPLIER);
    _score += scoreForWord;

    dispatchCustomEvent(GameManager::eventNameSetScore, &_score);
    TileManager::getInstance()->transitionOut(MAX_TIME_TRANSITION_WORD);

    _numWords++;
    if ( _numWords==MAX_WORDS_PER_ROUND )
    {
        endRound();       
    } 
    else 
    {
        _state = STATE_TRANSITION_OUT_WORD; 
    }
}

void GameManager::update(float dt)
{
    if ( _numWords >= MAX_WORDS_PER_ROUND )
        return;


    _timer -= dt;
     switch (_state)
     {
        case STATE_GUESS_WORD:
            if ( _timer<0 )
            {
                _timer = 0.0f;
                endWordGuessTimeRound();
            }

             // update the visual label ever so often 
             _updateLabelTimer += dt;
            if ( _updateLabelTimer > 0.1f )
            {
                _updateLabelTimer = 0.0f;
                GameWorldScene::getGameUILayer()->setTimerText(_timer);
            }
            break;
            
        case STATE_TRANSITION_OUT_WORD: 
            if (!TileManager::getInstance()->isTransitioning())
            {
                startWordGuessTime();
            }
            break;
        };
}

// contains the boiler plate code to send off a custon event 
void GameManager::dispatchCustomEvent(const std::string &eventName, void *eventData)
{
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    EventCustom event(eventName);
    event.setUserData(eventData);
    dispatcher->dispatchEvent(&event);
}
