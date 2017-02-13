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
const std::string EventDispatch::eventNameSetWordIndex = "eventNameSetWordIndex";
const std::string EventDispatch::eventNameShowPlayerFeedback = "eventNameShowPlayerFeedback";


const std::string EventDispatch::eventNameClearWord = "EventNameClearWord";
const std::string EventDispatch::eventNameNextWord = "EventNameNextWord";


const std::string EventDispatch::eventNamePlayEffect = "eventNamePlayEffect";



// contains the boiler plate code to listen for a custom event
void EventDispatch::listenCustomEvent(const std::string &eventName, std::function<void(cocos2d::EventCustom*)> callbackFunc)
{
	auto dispatcher = Director::getInstance()->getEventDispatcher();
	auto listenerClearWord = EventListenerCustom::create(eventName, callbackFunc);
    dispatcher->addEventListenerWithFixedPriority(listenerClearWord, 1);
}


// contains the boiler plate code to send off a custon event 
void EventDispatch::dispatchCustomEvent(const std::string &eventName, void *eventData)
{
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    EventCustom event(eventName);
    event.setUserData(eventData);
    dispatcher->dispatchEvent(&event);
}
