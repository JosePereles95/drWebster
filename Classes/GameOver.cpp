#include "GameOver.h"
#include "Tutorial.h"
#include "Alice.h"

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

	//Cursor
	_cursorSprite = Sprite::create("cursor1.png");
	addChild(_cursorSprite, 7);
	_cursorSprite->setVisible(false);

	_cursorSprite2 = Sprite::create("cursor2.png");
	addChild(_cursorSprite2, 6);

	dead = CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("/music/monitor.mp3");

	auto resumeItem = MenuItemImage::create("reanudar.png", "reanudar.png",
		CC_CALLBACK_1(GameOver::resumeGameScreen,
			this));

	auto closeItem = MenuItemImage::create("medicine1.png", "medicine1.png",
		CC_CALLBACK_1(GameOver::menuCloseCallback, this));

	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width / 2,
		origin.y + closeItem->getContentSize().height / 2));

	auto menu = Menu::create(resumeItem, closeItem, NULL);

	menu->alignItemsVerticallyWithPadding(visibleSize.height / 4);
	addChild(menu, 1);

	auto background = Sprite::create("dead.png");
	background->setPosition(Point((visibleSize.width / 2),
		(visibleSize.height / 2)));
	addChild(background, 0);

	auto mouseListener = EventListenerMouse::create();
	mouseListener->onMouseMove = CC_CALLBACK_1(GameOver::onMouseMove, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(mouseListener, this);

	return true;
}

void GameOver::onMouseMove(Event *event)
{
	auto *e = dynamic_cast<EventMouse *>(event);
	_cursorSprite2->setPosition(e->getCursorX() + 16, e->getCursorY() - 16);
	_cursorSprite->setPosition(_cursorSprite2->getPosition().x - 14, _cursorSprite2->getPosition().y + 14);

	//huella
	auto huella = Sprite::create("cursor2.png");
	huella->setPosition(_cursorSprite2->getPosition());
	huella->setOpacity(50);
	addChild(huella, 6);
	auto action = FadeOut::create(0.25);

	huella->runAction(action);
}

void GameOver::resumeGameScreen(Ref *pSender) {
	auto scene = Alice::createScene();
	CocosDenshion::SimpleAudioEngine::getInstance()->stopEffect(dead);
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
