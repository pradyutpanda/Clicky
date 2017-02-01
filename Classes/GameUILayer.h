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
    //void clearButtonTouchCallback(Ref* sender, cocos2d::ui::Widget::TouchEventType type);
    void clearButtonClickCallback(Ref* sender);
    void nextButtonClickCallback(Ref* sender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(GameUILayer);


private:
	void buildGameUI();
	void showPlayerFeedback(std::string feedback);
	
	void setScoreText(int newScore);
	void setTimerText(float newTimerValue );
	void setCurrentWordText(std::string& word );
	void setWordIndexText(int index, int total );

	cocos2d::Label* 		_scoreLabel;
	cocos2d::Label*			_timerLabel;
	cocos2d::Label*			_currentWordLabel;
	cocos2d::Label*			_wordIndexLabel;
};


#endif /* GameUILayer_hpp */
