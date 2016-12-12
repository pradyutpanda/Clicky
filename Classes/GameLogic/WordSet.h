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
