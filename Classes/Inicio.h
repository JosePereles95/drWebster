#ifndef __Inicio_H__
#define __Inicio_H__

#include "cocos2d.h"

class Inicio : public cocos2d::Layer
{
public:
	void resumeGameScreen(Ref *pSender);

	static cocos2d::Scene* createScene();


	virtual bool init();

	// implement the "static create()" method manually
	CREATE_FUNC(Inicio);
};

#endif // __Inicio_H__