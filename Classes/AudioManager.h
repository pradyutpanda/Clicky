//
//  EventDispatch.h
//  
//
//  Created by Pradyut Panda on 8/3/16.
//
//

#ifndef ____AudioManager__
#define ____AudioManager__

#include <stdio.h>
#include "cocos2d.h"
#include "SimpleAudioEngine.h"



// Audio master control
class AudioManager
{
public:

	AudioManager();
	void resetValues();
    bool init();

    void playBackgroundMusic(const char* musicName);
    void playEffect(const char* effectName);


    static AudioManager* create();
	//static AudioManager* getInstance();
private:

    static AudioManager* _sharedInstance;
    
	CocosDenshion::SimpleAudioEngine* 		_audio;
	
};

#endif /* defined(____AudioManager__) */
