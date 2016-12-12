//
//  WordSet.cpp
//  clicky
//
//  Created by Pradyut Panda on 11/6/16.
//
//
#include <iostream>
#include <fstream>

#include "WordSetManager.h"
#include "WordSet.h"
#include "FileReader.h"

using namespace std;
USING_NS_CC;


WordSetManager* WordSetManager::_sharedInstance = NULL;


// create a singleton if it does not exist and return
WordSetManager* WordSetManager::create()
{
   if (_sharedInstance)
        return _sharedInstance;

    WordSetManager *pRet = new(std::nothrow) WordSetManager();
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
WordSetManager *WordSetManager::getInstance()
{
    return _sharedInstance;
}

bool WordSetManager::init()
{
	_numWordSets = 0;
	_activeSet = NULL;

	readAllWordSets();
	return true;
}




// FILE IO functions 


// read in all the word sets that we find in the data folder 
void WordSetManager::readAllWordSets()
{
    std::string allSets[] = { "fruits.json" };
    int wordSetSize = sizeof(allSets) / sizeof(std::string);

    _numWordSets = 0;
    for (int i=0; i<wordSetSize; i++)
    {
        WordSet *set = new WordSet();
        set->init();
        set->readSetFromFile( allSets[i] );
        _wordSets.push_back(*set);

        _numWordSets++;
        _activeSet = set;
   }
}
