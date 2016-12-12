//
//  GameUILayer.hpp
//  clicky
//
//  Created by Pradyut Panda on 10/24/16.
//
//

#ifndef GameUILayer_hpp
#define GameUILayer_hpp

#include "cocos2d.h"


class GameUILayer : public cocos2d::Layer
{
public:
    
    virtual bool init();
    
    void menuCloseCallback(Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(GameUILayer);

    void setScoreText(int newScore);
	void setTimerText(float newTimerValue );
	void setCurrentWordText(std::string& word );

private:
	void buildGameUI();
	

	cocos2d::Label* 		_scoreLabel;
	cocos2d::Label*			_timerLabel;
	cocos2d::Label*			_currentWordLabel;
};


#endif /* GameUILayer_hpp */
