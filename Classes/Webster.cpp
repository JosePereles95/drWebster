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

	//Archivos encontrados
	validosEscaneados = 0;
	validosTotales = 2;

	__String *text = __String::createWithFormat("%d de %d", validosEscaneados, validosTotales);
	archivosEncontrados = Label::createWithTTF(text->getCString(), "fonts/MArker Felt.ttf", 20);

	archivosEncontrados->setPosition(Vec2(100, 250));
	addChild(archivosEncontrados, 3);

	archivosEncontrados = Label::createWithSystemFont(text->getCString(), "arial", 24); //Poner fuente


	//Carpeta1
	posXarchs1 = 300;
	posYarchs1 = 160;
	arch1_1 = Sprite::create("Chica1.jpg");
	arch1_1->setPosition(posXarchs1, posYarchs1);
	archivos1.insert(0, arch1_1);
	addChild(arch1_1, 1);
	
	arch1_2 = Sprite::create("gato1.jpg");
	arch1_2->setPosition(posXarchs1, posYarchs1);
	archivos1.insert(1, arch1_2);
	addChild(arch1_2, 1);
	
	arch1_3 = Sprite::create("gato2.jpg");
	arch1_3->setPosition(posXarchs1, posYarchs1);
	archivos1.insert(2, arch1_3);
	addChild(arch1_3, 1);

	arch1_4 = Sprite::create("gato3.jpg");
	arch1_4->setPosition(posXarchs1, posYarchs1);
	archivos1.insert(3, arch1_4);
	addChild(arch1_4, 1);

	carpeta1 = new Carpeta(archivos1, 0);
	carpeta1->imagen->setPosition(100, 120);
	carpeta1->pasar->setPosition(posXarchs1-75, posYarchs1+80);
	carpeta1->escanear->setPosition(posXarchs1 - 75, posYarchs1 + 60);
	carpeta1->abierta->setPosition(100, 120);
	addChild(carpeta1->botones, 1);
	addChild(carpeta1->abierta, 2);	

	//Carpeta2
	posXarchs2 = 310;
	posYarchs2 = 180;
	arch2_1 = Sprite::create("perro1.jpg");
	arch2_1->setPosition(posXarchs2, posYarchs2);
	archivos2.insert(0, arch2_1);
	addChild(arch2_1, 1);

	arch2_2 = Sprite::create("perro2.jpg");
	arch2_2->setPosition(posXarchs2, posYarchs2);
	archivos2.insert(1, arch2_2);
	addChild(arch2_2, 1);

	arch2_3 = Sprite::create("perro3.jpg");
	arch2_3->setPosition(posXarchs2, posYarchs2);
	archivos2.insert(2, arch2_3);
	addChild(arch2_3, 1);

	arch2_4 = Sprite::create("perro4.jpg");
	arch2_4->setPosition(posXarchs2, posYarchs2);
	archivos2.insert(3, arch2_4);
	addChild(arch2_4, 1);

	carpeta2 = new Carpeta(archivos2, 2);
	carpeta2->imagen->setPosition(100, 100);
	carpeta2->pasar->setPosition(posXarchs2-75, posYarchs2+80);
	carpeta2->escanear->setPosition(posXarchs2 - 75, posYarchs2 + 60);
	carpeta2->abierta->setPosition(100, 100);
	addChild(carpeta2->botones, 1);
	addChild(carpeta2->abierta, 2);

	//Imagen fondo
	auto background = Sprite::create("fondo_prueba.png");
	background->setPosition(Point((visibleSize.width / 2), (visibleSize.height / 2)));
	addChild(background, 0);

	this->scheduleUpdate();

	return true;
}

void Webster::update(float dt)
{
	validosEscaneados = carpeta1->validoEscaneado + carpeta2->validoEscaneado;
	/*if (_score > GameScene::_maxScore)
		GameScene::_maxScore = _score;
		*/
	__String *text = __String::createWithFormat("Score %d MAX %d", validosEscaneados, validosEscaneados);
	archivosEncontrados->setString(text->getCString());

}

void Webster::menuCloseCallback(Ref* pSender)
{
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}