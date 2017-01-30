//
//  EventDispatch.h
//  
//
//  Created by Pradyut Panda on 8/3/16.
//
//

#ifndef ____EventDispatch__
#define ____EventDispatch__

#include <stdio.h>
#include "cocos2d.h"



// Event related things!
class EventDispatch
{
public:

	static const std::string eventNameSetTimer;
	static const std::string eventNameSetScore;
	static const std::string eventNameSetWord;
	static const std::string eventNameAddLetter;
	static const std::string eventNameClearWord;


    static void dispatchCustomEvent(const std::string &eventName, void *eventData);
};

#endif /* defined(____EventDispatch__) */
