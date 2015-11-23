#include "PauseScene.h"
#include "Webster.h"

USING_NS_CC;

Scene* PauseScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = PauseScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool PauseScene::init()
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
		CC_CALLBACK_1(PauseScene::resumeGameScreen,
			this));

	auto closeItem = MenuItemImage::create("medicine1.png", "medicine1.png",
		CC_CALLBACK_1(PauseScene::menuCloseCallback, this));

	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width / 2,
		origin.y + closeItem->getContentSize().height / 2));

	auto menu = Menu::create(resumeItem, closeItem, NULL);

	menu->alignItemsVerticallyWithPadding(visibleSize.height / 4);
	addChild(menu, 1);


	auto background = Sprite::create("fondoPausa.jpg");
	background->setPosition(Point((visibleSize.width / 2),
		(visibleSize.height / 2)));
	addChild(background, 0);

	return true;
}

void PauseScene::resumeGameScreen(Ref *pSender) {
	Director::getInstance()->popScene();
}

void PauseScene::menuCloseCallback(Ref* pSender)
{
	Director::getInstance()->end();
}

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
exit(0);
#endif