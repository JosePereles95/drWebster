#include "Mechanics.h"

USING_NS_CC;

Scene* Mechanics::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = Mechanics::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;

	//prueba GitHub
	//prueba2
	//cambio ok perfe
}

// on "init" you need to initialize your instance
bool Mechanics::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();

    return true;
}
