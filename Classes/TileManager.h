//
//  TileManager.h
//  
//
//  Created by Pradyut Panda on 8/3/16.
//
//

#ifndef ____TileManager__
#define ____TileManager__

#include <stdio.h>
#include "cocos2d.h"
#include "WordTile.h"


// manages all the word tiles and handles input
class TileManager
{
public:
    
    static const int GRID_NUM_ROWS = 3;
	static const int GRID_NUM_COLS = 10;
	constexpr static const float CLEAR_WORD_TIMER = 5.0f;

    
    virtual bool init(cocos2d::Layer *layer );
    virtual bool release();

	static TileManager* create(cocos2d::Layer *layer);
    static TileManager* getInstance();

    void spawnNewWord(std::string& newWord, bool spawnNewWord);

    virtual void update( float delta );

    void transitionOut(float transitionTime);
    void transitionIn(float transitionTime);
    bool isTransitioning();
    
private:

	void getAdditionLetters(std::string& newWord);
	void placeLetters(std::string &newWord, int wordLength);
	void placeLettersLeftToRight(std::string &newWord, int wordLength, bool spawnNewWord);
	void setTilePosition(WordTile *tile, int wordLength, int row, int col );

	void addMouseEventListener();
    void addTouchEventListener();
	void getClickedTile(cocos2d::Vec2 eventPosition);

    void updateTransition( float delta );
    void dispatchCustomEvent(const std::string &eventName, void *eventData);


	static TileManager*			_sharedInstance;

    cocos2d::Layer* 			_drawLayer;
    std::vector<WordTile*> 		_letterTiles;

    //std::string 				_currentWord;	// word the player is trying to guess
    //std::string 				_guessWord;		// current guess
    
    int 						_gridNumCols;	// number of cols based on word length
    
    int                         _transitioning;  // transitioning in or out of a new word 
    float                       _transitionSpeed;   // speed of the scale based on time
    float                       _angle; // controls the scale of the tiles
};

#endif /* defined(____TileManager__) */
