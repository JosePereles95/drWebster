#ifndef __FINAL_H__
#define __FINAL_H__

#include "cocos2d.h"

class Final : public cocos2d::Layer
{
public:


	static cocos2d::Scene* createScene();
	void salir(void);
	void menuCloseCallback(cocos2d::Ref* pSender);

	virtual bool init();

	// implement the "static create()" method manually
	CREATE_FUNC(Final);
};

#endif // __FINAL_H__



