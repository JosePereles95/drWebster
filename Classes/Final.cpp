#include "GameOver.h"
#include "Tutorial.h"
#include "Final.h"

USING_NS_CC;

Scene* Final::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' isg an autorelease object
	auto layer = Final::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool Final::init()
{
	//////////////////////////////GameScreen
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto background = Sprite::create("GraciasJugar.png");
	background->setPosition(Point((visibleSize.width / 2),
		(visibleSize.height / 2)));
	addChild(background, 0);

	auto secuencia2 = Sequence::create(DelayTime::create(12.0f), CallFunc::create(CC_CALLBACK_0(Final::salir , this)), NULL);
	this->runAction(secuencia2);

	return true;
}

void Final::menuCloseCallback(Ref* pSender)
{
	Director::getInstance()->end();
}
void Final::salir()
{
	menuCloseCallback(this);
}
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
exit(0);
#endif