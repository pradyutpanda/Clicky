//
//  WordSet.cpp
//  clicky
//
//  Created by Pradyut Panda on 11/6/16.
//
//

#include "WordSet.h"
#include "FileReader.h"



bool WordSet::init()
{
	_numWords = 0;
	_numWordsPicked = 0;
	return true;
}

// pick a word at random and return it
void WordSet::getNewWordFromSet(std::string &word)
{
    // pick something that we have not used so far 
    int index = -1;
    bool usedBefore = false;
    do 
    {
    	index = rand() % _numWords;
    	usedBefore = false;
    	for ( int i=0; i<_numWordsPicked; i++)
    	{
    		if ( _pickedWordsFromSet[i]==index )
    		{
    			usedBefore = true;
    			break;
    		}
    	}	
    } while (usedBefore);
    word.assign( _words[index] );

    // store what we have used so that we do not repeat 
    _pickedWordsFromSet[_numWordsPicked] = index;
    _numWordsPicked++;

    CCLOG( " The word to guess is : [%s] ", word.c_str() );
}


void WordSet::initRound()
{
	_numWordsPicked = 0;
}



// FILE IO functions 

void WordSet::readSetFromFile(std::string fileName)
{
	init();
	FileReader fileReader(fileName);
    const vector<string> &fileContents = fileReader.getFileContents();

    _numWords = 0;
    for(int i=0; i < fileContents.size(); i++)
    {
    	string aword = fileContents[i];
        // remove spaces , quotes 
    	aword.erase(std::remove(aword.begin(), aword.end(), ' ' ), aword.end());
    	aword.erase(std::remove(aword.begin(), aword.end(), '\"' ), aword.end());
    	aword.erase(std::remove(aword.begin(), aword.end(), ',' ), aword.end());

    	if (aword[0] != '/')
    	{
    		_words.push_back(aword);
    		_numWords++;
			CCLOG( " string : %s", aword.c_str() );
		}
	}
}


void WordSet::writeSetToFile()
{
	
}
