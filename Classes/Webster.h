#ifndef __Webster_H__
#define __Webster_H__

#include "cocos2d.h"
#include "Carpeta.h"

USING_NS_CC;

class Webster : public cocos2d::Layer
{
public:
	Sprite* archivo1;
	Carpeta* carpeta1;

	Sprite* archivo2;
	Carpeta* carpeta2;

	static cocos2d::Scene* createScene();

	virtual bool init();

	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);

	// implement the "static create()" method manually
	CREATE_FUNC(Webster);
};
#endif // __Webster_H__