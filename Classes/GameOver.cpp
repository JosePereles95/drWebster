#include "GameOver.h"
#include "Tutorial.h"

USING_NS_CC;

Scene* GameOver::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' isg an autorelease object
	auto layer = GameOver::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool GameOver::init()
{
	//////////////////////////////GameScreen
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto resumeItem = MenuItemImage::create("pause.png", "pause.png",
		CC_CALLBACK_1(GameOver::resumeGameScreen,
			this));

	auto closeItem = MenuItemImage::create("medicine1.png", "medicine1.png",
		CC_CALLBACK_1(GameOver::menuCloseCallback, this));

	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width / 2,
		origin.y + closeItem->getContentSize().height / 2));

	auto menu = Menu::create(resumeItem, closeItem, NULL);

	menu->alignItemsVerticallyWithPadding(visibleSize.height / 4);
	addChild(menu, 1);


	auto background = Sprite::create("Dead.jpg");
	background->setPosition(Point((visibleSize.width / 2),
		(visibleSize.height / 2)));
	addChild(background, 0);

	return true;
}

void GameOver::resumeGameScreen(Ref *pSender) {
	auto scene = Tutorial::createScene();
	Director::getInstance()->popScene();
	Director::getInstance()->replaceScene(scene);
}

void GameOver::menuCloseCallback(Ref* pSender)
{
	Director::getInstance()->end();
}

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
exit(0);
#endif
