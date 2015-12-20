#ifndef __PRE_ALICE_H__
#define __PRE_ALICE_H__

#include "cocos2d.h"

USING_NS_CC;

class PreAlice : public cocos2d::Layer
{
public:
	static int TutorialPantalla;
	static int AlicePantalla;
	Sprite* _cursorSprite;
	Sprite* _cursorSprite2;
	Sprite* ficha;
	void empezarNivel(Ref *pSender);

	static cocos2d::Scene* createScene();

	void onMouseMove(Event *event);

	virtual bool init();

	// implement the "static create()" method manually
	CREATE_FUNC(PreAlice);
};

#endif // __PRE_ALICE_H__