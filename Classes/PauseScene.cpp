#include "PauseScene.h"
#include "Tutorial.h"

USING_NS_CC;

//Variable Global
int PauseScene::TutorialPantalla;
int PauseScene::AlicePantalla;

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

	//Cursor
	_cursorSprite = Sprite::create("cursor1.png");
	addChild(_cursorSprite, 7);
	_cursorSprite->setVisible(false);

	_cursorSprite2 = Sprite::create("cursor2.png");
	addChild(_cursorSprite2, 6);

	auto resumeItem = MenuItemImage::create("reanudar.png", "reanudar.png",
		CC_CALLBACK_1(PauseScene::resumeGameScreen,
			this));

	auto closeItem = MenuItemImage::create("medicine1.png", "medicine1.png",
		CC_CALLBACK_1(PauseScene::menuCloseCallback, this));

	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width / 2,
		origin.y + closeItem->getContentSize().height / 2));

	auto menu = Menu::create(resumeItem, closeItem, NULL);

	menu->alignItemsVerticallyWithPadding(visibleSize.height / 4);
	addChild(menu, 1);

	if (TutorialPantalla == 0) {
		auto background = Sprite::create("PausaWebster.png");
		background->setPosition(Point((visibleSize.width / 2),
			(visibleSize.height / 2)));
		addChild(background, 0);
	}
	if(TutorialPantalla == 1)
	{
		auto background = Sprite::create("PausaNina2.png");
		background->setPosition(Point((visibleSize.width / 2),
			(visibleSize.height / 2)));
		addChild(background, 0);
	}

	auto mouseListener = EventListenerMouse::create();
	mouseListener->onMouseMove = CC_CALLBACK_1(PauseScene::onMouseMove, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(mouseListener, this);

	return true;
}

void PauseScene::onMouseMove(Event *event)
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