#ifndef __MECHANICS_H__
#define __MECHANICS_H__

#include "cocos2d.h"

class Mechanics : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(Mechanics);
};

#endif // __MECHANICS_H__
