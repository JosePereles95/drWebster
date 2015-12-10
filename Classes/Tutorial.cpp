#include "Tutorial.h"
#include "Carpeta.h"
#include "Virus.h"
#include "PauseScene.h"
#include "GameOver.h"

USING_NS_CC;

Scene* Tutorial::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = Tutorial::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool Tutorial::init()
{
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto pause_button = MenuItemImage::create("pause.png", "pause.png",
		CC_CALLBACK_1(Tutorial::goToPauseScene, this));

	pause_button->setPosition(10, 80);

	// add a "close" icon to exit the progress. it's an autorelease object
	auto closeItem = MenuItemImage::create("medicine1.png", "medicine1.png",
		CC_CALLBACK_1(Tutorial::menuCloseCallback, this));

	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width / 2,
		origin.y + closeItem->getContentSize().height / 2));

	//Música de fondo.
	auto musicaAlice = CocosDenshion::SimpleAudioEngine::getInstance();
	//musicaAlice->preloadBackgroundMusic("/music/alice.mp3");
	//musicaAlice->playBackgroundMusic("/music/alice.mp3", true);

	//Efectos
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("/music/carpeta.mp3");

	// create menu, it's an autorelease object
	auto menu = Menu::create(closeItem, pause_button, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	_cursorSprite = Sprite::create("cursor1.png");
	addChild(_cursorSprite, 5);

	papeleraSprite = Sprite::create("papelera.png");
	papeleraSprite->setPosition(460, 280);
	addChild(papeleraSprite, 3);

	//Checks de archivos
	posXChecked1 = 70;
	posYChecked1 = 280;

	noChecked1 = Sprite::create("noCheck.png");
	noChecked1->setPosition(posXChecked1, posYChecked1);
	noChecked1->setVisible(true);
	addChild(noChecked1, 3);

	Checked1 = Sprite::create("Check.png");
	Checked1->setPosition(posXChecked1, posYChecked1);
	Checked1->setVisible(false);
	addChild(Checked1, 3);

	//Carpeta1
	posXarchs1 = 170;
	posYarchs1 = 150;

	arch1_1 = Sprite::create("PanelVirus.png");
	arch1_1->setPosition(posXarchs1, posYarchs1);
	archivos1.insert(0, arch1_1);
	addChild(arch1_1, 2);

	posXCarpeta1 = 65;
	posYCarpeta1 = 120;

	carpeta1 = new Carpeta(archivos1, 0);
	carpeta1->imagen->setPosition(posXCarpeta1, posYCarpeta1);
	carpeta1->pasar->setPosition(posXarchs1 + 30, posYarchs1 - 84);
	carpeta1->escanear->setPosition(posXarchs1 + 60, posYarchs1 - 84);
	carpeta1->abierta->setPosition(posXCarpeta1, posYCarpeta1);
	addChild(carpeta1->botones, 2);
	addChild(carpeta1->abierta, 1);
	
	posXarchs2 = 290;	//Carpeta2

	posYarchs2 = 160;

	arch2_1 = Sprite::create("denegado.png");
	arch2_1->setPosition(posXarchs2, posYarchs2);
	archivos2.insert(0, arch2_1);
	addChild(arch2_1, 2);

	arch2_2 = Sprite::create("HijaFamilia.png");
	arch2_2->setPosition(posXarchs2, posYarchs2);
	archivos2.insert(1, arch2_2);
	addChild(arch2_2, 2);

	posXCarpeta2 = 150;
	posYCarpeta2 = 120;

	carpeta2 = new Carpeta(archivos2, 1);
	carpeta2->imagen->setPosition(posXCarpeta2, posYCarpeta2);
	carpeta2->imagen->setColor(ccc3(200, 0, 0));
	carpeta2->abierta->setColor(ccc3(200, 0, 0));
	carpeta2->pasar->setPosition(posXarchs2 + 30, posYarchs2 - 84);
	carpeta2->escanear->setPosition(posXarchs2 + 60, posYarchs2 - 84);
	carpeta2->abierta->setPosition(posXCarpeta2, posYCarpeta2);
	addChild(carpeta2->botones, 2);
	addChild(carpeta2->abierta, 1);

	//Virus
	allCarpetas.insert(0, carpeta1);

	virus1 = new Virus(allCarpetas, 1, 1);
	virus1->imagen->setPosition(posXarchs1, posYarchs1);
	addChild(virus1->boton, 4);

	allVirus.insert(0, virus1);

	addChild(virus1->spritebatch, 4);
	addChild(virus1->imagenAturdido, 4);

	virus1->ataque = 0;

	//Sprite Sheet
	SpriteBatchNode* spritebatch = SpriteBatchNode::create("Escanear_sheet.png");
	SpriteFrameCache* cache = SpriteFrameCache::getInstance();
	cache->addSpriteFramesWithFile("Escanear_sheet.plist");

	cargando1 = Sprite::createWithSpriteFrameName("Escanear01.png");
	spritebatch->addChild(cargando1, 3);
	addChild(spritebatch, 3);

	cargando1->setVisible(false);

	Vector<SpriteFrame*> animFrames(5);

	char str[100] = { 0 };
	for (int i = 1; i < 5; i++)
	{
		sprintf(str, "Escanear%02d.png", i);
		SpriteFrame* frame = cache->getSpriteFrameByName(str);
		animFrames.pushBack(frame);
	}

	Animation* animation = Animation::createWithSpriteFrames(animFrames, 0.1f);
	cargando1->runAction(RepeatForever::create(Animate::create(animation)));

	//Animacion fuego
	SpriteBatchNode* spritebatch2 = SpriteBatchNode::create("Fire_sheet.png");
	SpriteFrameCache* cache2 = SpriteFrameCache::getInstance();
	cache2->addSpriteFramesWithFile("Fire_sheet.plist");

	animFuego = Sprite::createWithSpriteFrameName("fire_01.png");
	spritebatch2->addChild(animFuego, 3);
	addChild(spritebatch2, 3);
	animFuego->setPosition(460, 280);
	animFuego->setVisible(false);

	Vector<SpriteFrame*> animFrames2(4);

	char str2[100] = { 0 };
	for (int i = 1; i < 4; i++)
	{
		sprintf(str2, "fire_%02d.png", i);
		SpriteFrame* frame2 = cache2->getSpriteFrameByName(str2);
		animFrames2.pushBack(frame2);
	}

	Animation* animation2 = Animation::createWithSpriteFrames(animFrames2, 0.1f);
	animFuego->runAction(RepeatForever::create(Animate::create(animation2)));

	//Imagen fondo
	auto background = Sprite::create("FondoDoctor.png");
	background->setPosition(240, 160);
	addChild(background, 0);
	/*
	auto listener = EventListenerMouse::create();
	//touchListener->onTouchBegan = CC_CALLBACK_2(Tutorial::onTouchBegan, this);
	listener->onMouseDown = CC_CALLBACK_1(Tutorial::clickado, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);*/
	this->scheduleUpdate();

	auto mouseListener = EventListenerMouse::create();
	mouseListener->onMouseMove = CC_CALLBACK_1(Tutorial::onMouseMove, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(mouseListener, this);

	auto mouseListener2 = EventListenerMouse::create();
	mouseListener2->onMouseDown = CC_CALLBACK_1(Tutorial::onMouseDown, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(mouseListener2, this);

	auto mouseListener3 = EventListenerMouse::create();
	mouseListener3->onMouseUp = CC_CALLBACK_1(Tutorial::onMouseUp, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(mouseListener3, this);

	auto mouseListener4 = EventListenerMouse::create();
	mouseListener4->onMouseScroll = CC_CALLBACK_1(Tutorial::onMouseScroll, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(mouseListener4, this);

	return true;
}

void Tutorial::goToPauseScene(Ref *pSender) {
	auto scene = PauseScene::createScene();
	Director::getInstance()->pushScene(scene);
}
void Tutorial::goToGameOver(Ref *pSender) {
	auto scene = GameOver::createScene();
	Director::getInstance()->pushScene(scene);
}

void  Tutorial::onMouseDown(Event *event)
{
	cursorRect = _cursorSprite->getBoundingBox();

	for (const auto& virus : allVirus)
	{
		virusRect = virus->imagen->getBoundingBox();
		if (virusRect.intersectsRect(cursorRect))
		{
			if (virus->aturdido)
				virusElegido = virus;
		}
	}

	for (const auto& carpeta : allCarpetas)
	{
		carpRect = carpeta->escanear->getBoundingBox();
		if (carpRect.intersectsRect(cursorRect))
		{
			carpetaElegida = carpeta;
			if (carpetaElegida->abierta->isVisible()) {
				secuenciaEscaneo = Sequence::create(DelayTime::create(3.0f), CallFunc::create(CC_CALLBACK_0(Tutorial::escaneando, this)), NULL);
				cargando1->setPosition(carpetaElegida->contenido.at(carpetaElegida->elegido)->getPosition().x,
					carpetaElegida->contenido.at(carpetaElegida->elegido)->getPosition().y);
				cargando1->setVisible(true);
				carpetaElegida->imagen->runAction(secuenciaEscaneo);
			}
		}
	}
}

void Tutorial::onMouseMove(Event *event)
{
	auto *e = dynamic_cast<EventMouse *>(event);
	_cursorSprite->setPosition(e->getCursorX() + 2, e->getCursorY() - 2);
}

void Tutorial::onMouseUp(Event *event)
{
	papeleraRect = papeleraSprite->getBoundingBox();
	if (virusElegido != nullptr)
	{
		virusRect = virusElegido->imagen->getBoundingBox();

		if (papeleraRect.intersectsRect(virusRect))
		{
			for (const auto& virus : allVirus)
			{
				if (virus->identificador == virusElegido->identificador && virus->aturdido)
				{
					if (virus->tipoVirus == 1)
						virus->reciclar();

					else if (virus->tipoVirus == 2)
					{
						bool cuernosValido = true;
						for (const auto& otroVirus : allVirus)
						{
							if (otroVirus->tipoVirus == 1 && (!otroVirus->enPapelera && !otroVirus->muerto))
							{
								cuernosValido = false;
							}
						}
						if (cuernosValido)
							virus->reciclar();
					}
				}
			}
		}
	}

	if (virusElegido != nullptr)
	{
		virusElegido = nullptr;
	}
	if (carpetaElegida != nullptr)
	{
		carpetaElegida->imagen->stopAction(secuenciaEscaneo);
		carpetaElegida->tiempoEscanear = false;
		carpetaElegida = nullptr;
		cargando1->setVisible(false);
	}
}

void Tutorial::onMouseScroll(Event *event)
{
	papeleraSprite->setColor(ccc3(255, 0, 0));
	animFuego->setVisible(true);
	auto secuencia = Sequence::create(DelayTime::create(1.0f), CallFunc::create(CC_CALLBACK_0(Tutorial::changeColor, this)), NULL);
	papeleraSprite->runAction(secuencia);

	for (const auto& virus : allVirus)
	{
		if (virus->enPapelera && !virus->muerto)
		{
			virus->muerto = true;
		}
	}
}

void Tutorial::changeColor(void)
{
	papeleraSprite->setColor(ccc3(255, 255, 255));
	animFuego->setVisible(false);
}

void Tutorial::update(float dt)
{
	bool hayVivas = false;

	for (const auto& carpeta : allCarpetas)
	{
		if (carpeta->vida > 0)
			hayVivas = true;
	}

	if (!hayVivas)
	{
		//menuCloseCallback(this);
		goToGameOver(this);
	}
	else
	{
		for (const auto& virus : allVirus)
		{
			if (!virus->muerto)
			{
				virus->movimiento();
			}
		}
	}

	if (carpeta1->validoEscaneado == 1) {
		Checked1->setVisible(true);
	}

	if (carpeta1->abierta->isVisible()) {
		virus1->iniciado = true;
	}

	if (virusElegido != nullptr) {
		virusElegido->imagen->setPosition(_cursorSprite->getPosition().x, _cursorSprite->getPosition().y);
	}
}

void Tutorial::escaneando(void)
{
	if (carpetaElegida != nullptr)
	{
		carpetaElegida->tiempoEscanear = true;
		cargando1->setVisible(false);
	}
}

void Tutorial::menuCloseCallback(Ref* pSender)
{
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}