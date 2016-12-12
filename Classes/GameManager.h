//
//  GameManager.hpp
//  clicky
//
//  Created by Pradyut Panda on 10/25/16.
//
//

#ifndef GameManager_hpp
#define GameManager_hpp

#include <stdio.h>
#include "WordSet.h"



class GameManager
{
public:	

    GameManager();
    static GameManager* create();
    static GameManager* getInstance();

    void resetValues();
    void startRound();
    void endRound();
    void wordFound();

    void update(float dt);
    
    
    static const std::string 	eventNameSetTimer;
	static const std::string 	eventNameSetScore;

private:
	void dispatchCustomEvent(const std::string &eventName, void *eventData);

	void startWordGuessTime();
	void endWordGuessTimeRound();

    static GameManager*         _sharedInstance;

    WordSet*                    _wordSet;
    
    int         _state;         // current state 
    float       _timer;			// track time taken for each word 
    int         _score; 		// overall score 
    int 		_numWords;		// num words done so far in the round 
    float		_updateLabelTimer; 
};

#endif /* GameManager_hpp */
