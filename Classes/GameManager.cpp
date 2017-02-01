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
#include "EventDispatch.h"



USING_NS_CC;


const float     MAX_TIME_PER_ROUND = 60.0f;     // in seconds
const int       SCORE_MULTIPLIER = 10;
const int       MAX_WORDS_PER_ROUND = 20;
const float     MAX_TIME_TRANSITION_WORD = 0.5f;    // in seconds 

const int       STATE_GUESS_WORD = 0;
const int       STATE_TRANSITION_OUT_WORD = 1;


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
    if (pRet && pRet->init())
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

bool GameManager::init()
{
    auto dispatcher = Director::getInstance()->getEventDispatcher();

     // callback for custom event for when a letter is added to the current guess word
    auto callbackAddLetter = [this](EventCustom* event){ 
        char letter = *((char *)event->getUserData());
         _guessWord += letter;
        EventDispatch::dispatchCustomEvent(EventDispatch::eventNameSetWord, &_guessWord);
        if ( _currentWord.compare(_guessWord) == 0 )
        {
            this->wordFound();
        }
    };
    auto listenerAddLetter = EventListenerCustom::create(EventDispatch::eventNameAddLetter, callbackAddLetter);
    dispatcher->addEventListenerWithFixedPriority(listenerAddLetter, 1);  

    // callback to clear the current guess
    auto callbackClearWord = [this](EventCustom* event){ 
        _guessWord = "";
        EventDispatch::dispatchCustomEvent(EventDispatch::eventNameSetWord, &_guessWord);
    };
    auto listenerClearWord = EventListenerCustom::create(EventDispatch::eventNameClearWord, callbackClearWord);
    dispatcher->addEventListenerWithFixedPriority(listenerClearWord, 1); 

    // callback to go to the next word 
    auto callbackNextWord = [this](EventCustom* event){
        _timer = 0.0f;
        this->endWordGuessTimeRound();
    };
    //EventDispatch::listenCustomEvent(EventDispatch::eventNameNextWord, callbackNextWord);
    auto listenerNextWord = EventListenerCustom::create(EventDispatch::eventNameNextWord, callbackNextWord);
    dispatcher->addEventListenerWithFixedPriority(listenerNextWord, 1); 


    return true;
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

    _wordSet->initRound();
}


void GameManager::endRound()
{
    CCLOG( "Ending a Round ! , total score : %d ", _score );
}


// player found the word, kill timer and give points
void GameManager::wordFound()
{
    std::string feedbackStr = "Great Work!";
    EventDispatch::dispatchCustomEvent(EventDispatch::eventNameShowPlayerFeedback, &feedbackStr);
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

    // clear the guess word 
    _guessWord = "";
    EventDispatch::dispatchCustomEvent(EventDispatch::eventNameSetWord, &_guessWord);

    _wordSet->getNewWordFromSet(_currentWord);
    TileManager::getInstance()->spawnNewWord(_currentWord, true);
    TileManager::getInstance()->transitionIn(MAX_TIME_TRANSITION_WORD);

    // set the word index 
    int numbers[]= { _numWords+1, MAX_WORDS_PER_ROUND};
    EventDispatch::dispatchCustomEvent(EventDispatch::eventNameSetWordIndex, &numbers);
}


void GameManager::endWordGuessTimeRound()
{
    CCLOG( "Stop timer for word %d : ", _numWords );

    // compute the score based on time remaining
    int scoreForWord = (int) (_timer * SCORE_MULTIPLIER);
    _score += scoreForWord;

    EventDispatch::dispatchCustomEvent(EventDispatch::eventNameSetScore, &_score);
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
                EventDispatch::dispatchCustomEvent(EventDispatch::eventNameSetTimer, &_timer);
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

