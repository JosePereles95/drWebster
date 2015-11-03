#ifndef __MECHANICS_H__
#define __MECHANICS_H__

#include "cocos2d.h"

USING_NS_CC;

const int POD_STEP_MOVE = 10;
class Mechanics : public cocos2d::Layer
{
private:
	Vec2 _podVector;
	Sprite *_playerSprite;

public:
   static cocos2d::Scene* createScene();

	bool _isMovingByMouse;
	void update(float dt);
	void onMouseMove(Event *event);

    virtual bool init();

	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);

    // implement the "static create()" method manually
    CREATE_FUNC(Mechanics);
};
#endif // __MECHANICS_H__