//
//  EventDispatch.cpp
//  clicky
//
//  Created by Pradyut Panda on 10/25/16.
//
//

#include "EventDispatch.h"


USING_NS_CC;



const std::string EventDispatch::eventNameSetTimer  = "EventNameSetTimer";
const std::string EventDispatch::eventNameSetScore  = "EventNameSetScore";
const std::string EventDispatch::eventNameSetWord   = "EventNameSetWord";
const std::string EventDispatch::eventNameAddLetter = "EventNameAddLetter";
const std::string EventDispatch::eventNameClearWord = "EventNameClearWord";



// contains the boiler plate code to send off a custon event 
void EventDispatch::dispatchCustomEvent(const std::string &eventName, void *eventData)
{
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    EventCustom event(eventName);
    event.setUserData(eventData);
    dispatcher->dispatchEvent(&event);
}