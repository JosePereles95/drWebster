#ifndef __GAMEOVER_H__
#define __GAMEOVER_H__

#include "cocos2d.h"

USING_NS_CC;

class GameOver : public cocos2d::Layer
{
public:
	void resumeGameScreen(Ref *pSender);
	Sprite* _cursorSprite;
	Sprite* _cursorSprite2;
	static cocos2d::Scene* createScene();

	void onMouseMove(Event *event);

	void menuCloseCallback(cocos2d::Ref* pSender);

	virtual bool init();

	// implement the "static create()" method manually
	CREATE_FUNC(GameOver);
};

#endif // __GAMEOVER_H__

