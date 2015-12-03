#include "Inicio.h"
#include "Tutorial.h"


USING_NS_CC;

Scene* Inicio::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = Inicio::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool Inicio::init()
{
	//////////////////////////////GameScreen
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto resumeItem = MenuItemImage::create("Logo.png"," Logo.png",
		CC_CALLBACK_1(Inicio::resumeGameScreen,
			this));

	
	auto menu = Menu::create(resumeItem,NULL);

	menu->alignItemsVerticallyWithPadding(visibleSize.height / 4);
	addChild(menu, 1);


	auto background = Sprite::create("fondoPausa.jpg");
	background->setPosition(Point((visibleSize.width / 2),
		(visibleSize.height / 2)));
	addChild(background, 0);

	return true;
}

void Inicio::resumeGameScreen(Ref *pSender) {
	auto scene = Tutorial::createScene();
	Director::getInstance()->pushScene(scene);
}



#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
exit(0);
#endif