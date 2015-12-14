#ifndef __PAUSE_SCENE_H__
#define __PAUSE_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;

class PauseScene : public cocos2d::Layer
{
public:
	static int TutorialPantalla;
	static int AlicePantalla;
	Sprite* _cursorSprite;
	Sprite* _cursorSprite2;
	void resumeGameScreen(Ref *pSender);

	static cocos2d::Scene* createScene();
	
	void onMouseMove(Event *event);

	void menuCloseCallback(cocos2d::Ref* pSender);

	virtual bool init();

	// implement the "static create()" method manually
	CREATE_FUNC(PauseScene);
};

#endif // __PAUSE_SCENE_H__