#include "PreAlice.h"
#include "Tutorial.h"
#include "Alice.h"
#include "AnimacionScene.h"

USING_NS_CC;

Scene* PreAlice::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = PreAlice::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool PreAlice::init()
{
	//////////////////////////////GameScreen
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();

	//Cursor
	_cursorSprite = Sprite::create("cursor1.png");
	addChild(_cursorSprite, 7);
	_cursorSprite->setVisible(false);

	_cursorSprite2 = Sprite::create("cursor2.png");
	addChild(_cursorSprite2, 6);

	ficha = Sprite::create("FichaAlice.png");
	ficha->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	addChild(ficha, 2);

	auto pasarNivel = MenuItemImage::create("BotonFicha.png", "BotonFicha2.png",
		CC_CALLBACK_1(PreAlice::empezarNivel, this));
	pasarNivel->setPosition(0, -230);

	auto menu = Menu::create(pasarNivel, NULL);
	addChild(menu, 3);

	ficha->setOpacity(200);
	pasarNivel->setOpacity(200);

	auto background = Sprite::create("Prepaciente.png");
	background->setPosition(Point((visibleSize.width / 2),
		(visibleSize.height / 2)));
	addChild(background, 0);

	auto mouseListener = EventListenerMouse::create();
	mouseListener->onMouseMove = CC_CALLBACK_1(PreAlice::onMouseMove, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(mouseListener, this);

	return true;
}

void PreAlice::onMouseMove(Event *event)
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

void PreAlice::empezarNivel(Ref *pSender) {
	Director::getInstance()->popScene();
	auto scene = Alice::createScene();
	Director::getInstance()->pushScene(scene);
	auto scene2 = AnimacionScene::createScene();
	Director::getInstance()->pushScene(scene2);
	
}

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
exit(0);
#endif