#ifndef __MECHANICS_SCENE_H__
#define __MECHANICS_SCENE_H__

#include "cocos2d.h"

class Mechanics : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(Mechanics);
};

#endif // __MECHANICS_SCENE_H__
