//
//  AudioManager.cpp
//  clicky
//
//  Created by Pradyut Panda on 10/25/16.
//
//

#include "AudioManager.h"
#include "SimpleAudioEngine.h"
#include "EventDispatch.h"



USING_NS_CC;


const float     BACKGROUND_MUSIC_VOLUME = 0.5f;
const float     EFFECTS_MUSIC_VOLUME = 0.5f;


AudioManager* AudioManager::_sharedInstance = NULL;




AudioManager::AudioManager()
{
    resetValues();
}

// create a singleton if it does not exist and return
AudioManager* AudioManager::create()
{
   if (_sharedInstance)
        return _sharedInstance;

    AudioManager *pRet = new(std::nothrow) AudioManager();
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
//AudioManager *AudioManager::getInstance()
//{
//    return _sharedInstance;
//}

void AudioManager::resetValues()
{
    _audio = nullptr;
}


bool AudioManager::init()
{

    _audio = CocosDenshion::SimpleAudioEngine::getInstance();
    _audio->setEffectsVolume(EFFECTS_MUSIC_VOLUME);
    _audio->setBackgroundMusicVolume(BACKGROUND_MUSIC_VOLUME);

    // callback to play an effect by name 
    auto callbackPlayEffect = [this](EventCustom* event){
        std::string *effectName = ((std::string *)event->getUserData());

        // play a sound effect
        std::string effectNameMP3 = *effectName + ".mp3";
        this->playEffect(effectNameMP3.c_str());
    };
    EventDispatch::listenCustomEvent(EventDispatch::eventNamePlayEffect, callbackPlayEffect);
    return true;
}



void AudioManager::playBackgroundMusic(const char* musicName)
{
    _audio->playBackgroundMusic(musicName, true);
}

void AudioManager::playEffect(const char* effectName)
{
    _audio->playEffect(effectName);
}

