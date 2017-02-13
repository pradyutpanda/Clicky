//
//  WordSet.h
//  clicky
//
//  Created by Pradyut Panda on 11/6/16.
//
//

#ifndef WordSet_h
#define WordSet_h

#include <stdio.h>


// represents a set of words that are related by some common theme 
// populates from a file 
// get a random word from the set without repeats
class WordSet 
{
public:

    bool init();
    void initRound();
	void getNewWordFromSet(std::string &word);

	void readSetFromFile(std::string fileName);
	void writeSetToFile();

private:

	int 							_numWords;
	std::vector<std::string>		_words; 
	

	int 	_pickedWordsFromSet[256];
	int 	_numWordsPicked;
};

#endif /* WordSet_h */
