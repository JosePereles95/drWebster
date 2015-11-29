#ifndef __GAMEOVER_H__
#define __GAMEOVER_H__

#include "cocos2d.h"

class GameOver : public cocos2d::Layer
{
public:
	void resumeGameScreen(Ref *pSender);

	static cocos2d::Scene* createScene();

	void menuCloseCallback(cocos2d::Ref* pSender);

	virtual bool init();

	// implement the "static create()" method manually
	CREATE_FUNC(GameOver);
};

#endif // __GAMEOVER_H__

