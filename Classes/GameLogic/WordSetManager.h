//
//  WordSetManager.h
//  clicky
//
//  Created by Pradyut Panda on 11/6/16.
//
//

#ifndef WordSetManager_h
#define WordSetManager_h

#include <stdio.h>
#include "WordSet.h"



class WordSetManager 
{
public:
	
	static WordSetManager* create();
    static WordSetManager* getInstance();

    bool init();
    void readAllWordSets(); 
    WordSet* getActive()
    {
    	return _activeSet;
    }

private:
	
	static WordSetManager*			_sharedInstance;

	int 			_numWordSets;
	std::vector<WordSet>	_wordSets;
	WordSet*		_activeSet;
	
};

#endif /* WordSetManager_h */
