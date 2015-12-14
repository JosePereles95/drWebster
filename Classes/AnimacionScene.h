#ifndef __ANIMCAIONSCENE_H__
#define __ANIMCAIONSCENE_H__

#include "cocos2d.h"

class AnimacionScene : public cocos2d::Layer
{
public:
	
	Sprite* V1;
	Sprite* V1Final;
	void resumeGameScreen(Ref *pSender);

	static cocos2d::Scene* createScene();

	
	void Mover(void);
	void Cambio(void);
	void Pasar(void);

	virtual bool init();

	// implement the "static create()" method manually
	CREATE_FUNC(AnimacionScene);
};

#endif // __ANIMCAIONSCENE_H__
