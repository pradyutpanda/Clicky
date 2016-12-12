//
//  WordTile.h
//  clicky
//
//  Created by Pradyut Panda on 10/23/16.
//
//

#ifndef WordTile_h
#define WordTile_h

#include <stdio.h>

class WordTile : public cocos2d::Sprite
{
public:
	constexpr static const float HOVER_SPEED = 60.0f;
	constexpr static const float HOVER_AMP = 5.0f;
	static const int TILE_SIZE = 50;


	bool init();
	void reset();
	void setLetter(char letter);
	inline const char getLetter()
	{
		return _letter;
	}

	void update(float delta);

	virtual void setPosition(const cocos2d::Vec2& pos);

	 /**
     * Creates a word tile with an image filename
     *
     * @param   filename A path to image file, e.g., "scene1/monster.png".
     * @return  An autoreleased sprite object.
     */
	static WordTile* create(const std::string& filename);

private:
	void addEventListener();


	char				_letter;
	cocos2d::Vec2		_position;
	cocos2d::Vec2		_velocity;
	float 				_angle; 

};


#endif /* WordTile_h */
