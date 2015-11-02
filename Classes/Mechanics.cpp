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
}

// on "init" you need to initialize your instance
bool Mechanics::init()
{
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	// add a "close" icon to exit the progress. it's an autorelease object
	auto closeItem = MenuItemImage::create("medicine1.png","medicine1.png",
		CC_CALLBACK_1(Mechanics::menuCloseCallback, this));

	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width / 2,
		origin.y + closeItem->getContentSize().height / 2));

	// create menu, it's an autorelease object
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 2);

	_playerSprite = Sprite::create("cursor.png");
	//_playerSprite->setPosition(Point(visibleSize.width / 2,	_playerSprite->getContentSize().height * 0.75));
	_playerSprite->setPosition(50, 50);
	addChild(_playerSprite, 1);

	//Imagen
	auto background = Sprite::create("abraham_formateo.jpg");
	background->setPosition(Point((visibleSize.width / 2), (visibleSize.height / 2)));
	addChild(background, 0);

	_podVector = Vec2::ZERO;

	// Setting and binding mouse callbacks
	auto mouseListener = EventListenerMouse::create();
	mouseListener->onMouseMove = CC_CALLBACK_1(Mechanics::onMouseMove, this);

	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(mouseListener, this);

    return true;
}

void Mechanics::onMouseMove(Event *event) {
	static Vec2 *oldPosition;
	auto *e = dynamic_cast<EventMouse *>(event);
	if (oldPosition == NULL) {
		oldPosition = new Vec2(e->getCursorX(), e->getCursorY());
	}
	else {
		_podVector = Vec2(e->getCursorX() - oldPosition->x,
			e->getCursorY() - oldPosition->y);

		if (!_isMovingByMouse) {
			_isMovingByMouse = true;
			oldPosition->x = e->getCursorX();
			oldPosition->y = e->getCursorY();
		}
	}
}

void Mechanics::update(float dt) {
	Size visibleSize = Director::getInstance()->getVisibleSize();

	if (_isMovingByMouse) {
		Vec2 newPos = Vec2(_playerSprite->getPosition().x + _podVector.x, _playerSprite->getPosition().y + _podVector.y);
		
		if (newPos.x >= _playerSprite->getBoundingBox().size.width / 2 &&
			newPos.x <= (visibleSize.width - _playerSprite->getBoundingBox().size.width / 2) &&
			newPos.y >= _playerSprite->getBoundingBox().size.height / 2 &&
			newPos.y <= (visibleSize.height - _playerSprite->getBoundingBox().size.height / 2))
		{
			_playerSprite->setPosition(newPos);
		}
		_playerSprite->setPosition(newPos);
		_isMovingByMouse = false;
	}
}


void Mechanics::menuCloseCallback(Ref* pSender)
{
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}