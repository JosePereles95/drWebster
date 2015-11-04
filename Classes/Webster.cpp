#include "Webster.h"

USING_NS_CC;

Scene* Webster::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = Webster::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool Webster::init()
{
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	// add a "close" icon to exit the progress. it's an autorelease object
	auto closeItem = MenuItemImage::create("medicine1.png", "medicine1.png",
		CC_CALLBACK_1(Webster::menuCloseCallback, this));

	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width / 2,
		origin.y + closeItem->getContentSize().height / 2));

	// create menu, it's an autorelease object
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	//Carpeta1
	archivo1 = Sprite::create("Chica1.jpg");
	archivo1->setPosition(300, 150);
	addChild(archivo1, 1);

	carpeta1 = new Carpeta(archivo1);
	carpeta1->botonCarpeta->setPosition(100, 120);
	carpeta1->abierta->setPosition(100, 120);
	addChild(carpeta1->botonCarpeta, 1);
	addChild(carpeta1->abierta, 2);

	
	//Carpeta2
	archivo2 = Sprite::create("Camarera.jpg");
	archivo2->setPosition(300, 120);
	addChild(archivo2, 1);

	carpeta2 = new Carpeta(archivo2);
	carpeta2->botonCarpeta->setPosition(100, 100);
	carpeta2->abierta->setPosition(100, 100);
	addChild(carpeta2->botonCarpeta, 1);
	addChild(carpeta2->abierta, 2);
	

	//Imagen fondo
	auto background = Sprite::create("fondo_prueba.png");
	background->setPosition(Point((visibleSize.width / 2), (visibleSize.height / 2)));
	addChild(background, 0);

	return true;
}

void Webster::menuCloseCallback(Ref* pSender)
{
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}