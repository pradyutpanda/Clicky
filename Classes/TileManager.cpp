//
//  TileManager.cpp
//  - Manages the rendering and animation for a list of tiles
//
//  Created by Pradyut Panda on 8/3/16.
//
//

#include "TileManager.h"
#include "WordTile.h"
#include "GameWorldScene.h"
#include "EventDispatch.h"



USING_NS_CC;

TileManager* TileManager::_sharedInstance = NULL;
//const int TileManager::GRID_NUM_COLS = 10;


bool TileManager::init(cocos2d::Layer *drawLayer)
{
    this->_drawLayer = drawLayer;

    // create the letter tiles 
    int numTiles = GRID_NUM_ROWS * GRID_NUM_COLS;
     _letterTiles.resize(numTiles);
    for ( int i=0; i<numTiles; i++ )
    {
        WordTile *tile = WordTile::create("letters_tiles.png");
        _letterTiles[i] = tile;
        tile->setLetter('a');
        this->_drawLayer->addChild( tile, 0);
    }

    _gridNumCols = 0;

    _angle = 0;
    _transitioning = 0;
    _transitionSpeed = 0.0f;
    //addMouseEventListener();
    addTouchEventListener();
    return true;
}

bool TileManager::release()
{
    return true;
}

// create a singleton if it does not exist and return
TileManager* TileManager::create(cocos2d::Layer *layer)
{
   if (_sharedInstance)
        return _sharedInstance;

    TileManager *pRet = new(std::nothrow) TileManager();
    if (pRet && pRet->init(layer))
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
TileManager *TileManager::getInstance()
{
    return _sharedInstance;
}

void TileManager::spawnNewWord(std::string& newWord, bool setTilePos = false)
{
    Vec2 visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // get a new word 
    int wordLength = (int)newWord.size();
    _gridNumCols = wordLength;
    std::string currentWordLong = newWord;
    getAdditionLetters(currentWordLong);

    // loop through and set the letters of the word 
    for ( int i=0; i<currentWordLong.length(); i++ )
    {
        _letterTiles[i]->setLetter(currentWordLong[i]);
    }
    //placeLetters(_currentWord, wordLength);
    placeLettersLeftToRight(currentWordLong, wordLength, setTilePos);
}

 void TileManager::update( float delta )
 {
    for ( int i=0; i<_letterTiles.size(); i++ )
    {
        _letterTiles[i]->update(delta);
    }

    updateTransition(delta);
}


void TileManager::updateTransition( float delta )
{
    if (_transitioning==1) 
    {
        _angle += _transitionSpeed * delta;
        if ( _angle>90 )
        {
            _angle = 90;
            _transitioning = 0;
        }
        float scale = cos(_angle * 3.14f / 180.0f);
    }
    if (_transitioning==2)
    {
        _angle += _transitionSpeed * delta;
        if ( _angle<0 )
        {
            _angle = 0;
            _transitioning = 0;
        }    
    }

    float scale = cos(_angle * 3.14f / 180.0f);
    for ( int i=0; i<_letterTiles.size(); i++ )
    {
        _letterTiles[i]->setScale(scale);
    }
 }


// triggers the effect that happens between two words
// scale all the tiles down from angle 0 => 90 
void TileManager::transitionOut(float transitionTime)
{
  _transitioning = 1;  
  _transitionSpeed = 90 / transitionTime;
  _angle = 0;
}

// triggers the effect that happens between two words
// scale all the tiles up from angle 90 => 0 
void TileManager::transitionIn(float transitionTime)
{
    _transitioning = 2;
    _transitionSpeed = -90 / transitionTime;
    _angle = 95; 
}

bool TileManager::isTransitioning()
{
    return (_transitioning > 0);
}


// get some random letters to mix things up 
void TileManager::getAdditionLetters(std::string& newWord)
{

    // add a bunch more letters and return 
    unsigned long wordLength = newWord.length();
    const int numLetters = GRID_NUM_ROWS * GRID_NUM_COLS;
    newWord.resize( numLetters, 'a');

    for ( unsigned long i=wordLength; i<numLetters; i++)
    {
        char newChar = 'a' + rand() % 26;
        newWord[i] = newChar;
    }
}


// place letters in different places 
void TileManager::placeLetters(std::string &newWord, int wordLength)
{
    const int c_randOffset = 10;

    Vec2 visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    origin.x += visibleSize.x/5;
    origin.y += visibleSize.y/3;

    // place in a simple grid format 
    int drawGrid[3][6] = {0};
    int currentLetter = 0;
    while ( currentLetter < _letterTiles.size() )
    {
        int randRow = rand() % 3;
        int randCol = rand() % 6;

        if ( drawGrid[randRow][randCol] == 0 )
        {
            drawGrid[randRow][randCol] = 1;

            Vec2 offset;
            offset.x = randCol * 80 + (rand() % (c_randOffset*2) - c_randOffset);
            offset.y = randRow * 100  + (rand() % (c_randOffset*2) - c_randOffset);
            this->_letterTiles[currentLetter]->setPosition( origin+offset );
            currentLetter++;
        }
    }
}

void TileManager::placeLettersLeftToRight(std::string &newWord, int wordLength, bool setTilePos)
{
    setTilePos = true;
    int i=0;
    int drawGrid[GRID_NUM_ROWS][GRID_NUM_COLS] = {0};

    // hide al the tiles 
    // hide all the other letters 
    for ( i=0; i<GRID_NUM_ROWS*GRID_NUM_COLS; i++ )
    {
        this->_letterTiles[i]->setVisible(false);
    }

    // place the letters of the word left to right 
    int letterSpace = GRID_NUM_COLS - wordLength;
    int startCol = 0;
    if ( letterSpace > 0 )
        startCol = rand() % (letterSpace+1);
    startCol = 0;
    // set the letter tiles for letters of the word to guess
    for ( i=0; i<wordLength; i++ )
    {
        int randRow = rand() % GRID_NUM_ROWS;
        drawGrid[randRow][startCol+i] = 1;
        if (setTilePos)
            setTilePosition(this->_letterTiles[i], wordLength, randRow, startCol+i);
        this->_letterTiles[i]->setVisible(true);
    }

    // set the tiles for the other random letters
    int some = GRID_NUM_COLS;
    int numCols = std::min(wordLength, some );
    int maxNumTiles = std::min( wordLength*3, GRID_NUM_ROWS*GRID_NUM_COLS);
    while ( i < maxNumTiles )
    {
        int randRow = rand() % GRID_NUM_ROWS;
        int randCol = rand() % numCols;

        if ( drawGrid[randRow][randCol] == 0 )
        {
            drawGrid[randRow][randCol] = 1;
            if (setTilePos)
                setTilePosition(this->_letterTiles[i], wordLength, randRow, randCol);
            this->_letterTiles[i]->setVisible(true);
            i++;
        }
    }
}

// set the tile position based on a loose grid 
void TileManager::setTilePosition(WordTile *tile, int wordLength, int row, int col )
{
    const int c_randOffset = 10;
    const int c_widthOffset = 70;
    const int c_heightOffset = 90;

    Vec2 visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    int numTotalCols = wordLength;
    int totalWidth = (c_widthOffset-WordTile::TILE_SIZE)*(numTotalCols-1) + WordTile::TILE_SIZE*numTotalCols;
    origin.x = (visibleSize.x-totalWidth)/2;
    origin.y += visibleSize.y/3;


    // place in a simple grid format 
    Vec2 offset;
    offset.x = col * c_widthOffset + (rand() % (c_randOffset*2) - c_randOffset);
    offset.y = row * c_heightOffset  + (rand() % (c_randOffset*2) - c_randOffset);

    tile->setPosition( origin+offset );
}



// check to see which tiles were clicked 
void TileManager::addMouseEventListener()
{
    // add evert listeners here
    auto dispatcher = Director::getInstance()->getEventDispatcher();

    auto callbackMouseDown = [this](EventMouse* event){ 

        Vec2 mousePosition( event->getCursorX(), event->getCursorY() );
        this->getClickedTile(mousePosition);
    };

    auto listener = EventListenerMouse::create();
    listener->onMouseDown = callbackMouseDown;
    dispatcher->addEventListenerWithFixedPriority(listener, 10);
    
}

// check to see which tiles were touched
void TileManager::addTouchEventListener()
{
    auto listener1 = EventListenerTouchOneByOne::create();

    listener1->onTouchBegan = [this](Touch* touch, Event* event){

        this->getClickedTile(touch->getLocation());
        return true;
    };

    listener1->onTouchMoved = [](Touch* touch, Event* event){
        return true;
    };

    listener1->onTouchEnded = [](Touch* touch, Event* event){
        return true;
    };

    auto dispatcher = Director::getInstance()->getEventDispatcher();
    dispatcher->addEventListenerWithFixedPriority(listener1, 10);
}


// check to see if the player clicked / touched on any of the tiles
// if so add to the current guess and reset clear timer
void TileManager::getClickedTile(Vec2 eventPosition)
{
    // run through all the tile and check if clicked inside 
    for ( int i=0; i<_letterTiles.size(); i++ )
    {
        Rect bbox = _letterTiles[i]->getBoundingBox();
        if (bbox.containsPoint(eventPosition))
        {
            char letter = _letterTiles[i]->getLetter();
            EventDispatch::dispatchCustomEvent( EventDispatch::eventNameAddLetter, &letter );
            break;
        }
    }
}

