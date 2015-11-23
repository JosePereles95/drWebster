#ifndef __PAUSE_SCENE_H__
#define __PAUSE_SCENE_H__

#include "cocos2d.h"

class PauseScene : public cocos2d::Layer
{
public:
	void resumeGameScreen(Ref *pSender);

	static cocos2d::Scene* createScene();

	void menuCloseCallback(cocos2d::Ref* pSender);

	virtual bool init();

	// implement the "static create()" method manually
	CREATE_FUNC(PauseScene);
};

#endif // __PAUSE_SCENE_H__