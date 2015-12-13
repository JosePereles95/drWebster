#include "Tutorial.h"
#include "Carpeta.h"
#include "Virus.h"
#include "PauseScene.h"
#include "GameOver.h"

USING_NS_CC;

Scene* Tutorial::createScene()
{
	auto scene = Scene::create();
	auto layer = Tutorial::create();
	scene->addChild(layer);
	return scene;
}

bool Tutorial::init()
{
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//Música de fondo.
	musicaWebster = CocosDenshion::SimpleAudioEngine::getInstance();
	//musicaAlice->preloadBackgroundMusic("/music/alice.mp3");
	musicaWebster->playBackgroundMusic("/music/alice.mp3", true);
	musicaWebster->stopBackgroundMusic(false);
	musicaWebster->setBackgroundMusicVolume(0.25f);

	//Efectos
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("/music/carpeta.mp3");

	//Cursor
	_cursorSprite = Sprite::create("cursor1.png");
	addChild(_cursorSprite, 6);

	//Papelera
	papeleraSprite = Sprite::create("papelera.png");
	papeleraSprite->setPosition(visibleSize.width - papeleraSprite->getContentSize().width / 2 - 15, 
		visibleSize.height - papeleraSprite->getContentSize().height / 2 - 15);
	addChild(papeleraSprite, 3);

	//Interfaz
	interfazSprite = Sprite::create("IntWebster.png");
	interfazSprite->setPosition(origin.x + interfazSprite->getContentSize().width / 2,
		origin.y + visibleSize.height - interfazSprite->getContentSize().height / 2);
	addChild(interfazSprite, 1);

	//Checks de archivos
	posXChecked1 = 202;
	posYChecked1 = visibleSize.height - 110;

	noChecked1 = Sprite::create("noCheck.png");
	noChecked1->setPosition(posXChecked1, posYChecked1);
	noChecked1->setVisible(true);
	addChild(noChecked1, 2);

	Checked1 = Sprite::create("Check.png");
	Checked1->setPosition(posXChecked1, posYChecked1);
	Checked1->setVisible(false);
	addChild(Checked1, 2);

	//Carpeta1
	posXarchs1 = 400;
	posYarchs1 = 360;

	arch1_1 = Sprite::create("PanelVirus.png");
	arch1_1->setPosition(posXarchs1, posYarchs1);
	archivos1.insert(0, arch1_1);
	addChild(arch1_1, 2);

	arch1_2 = Sprite::create("entrada_ponencia.png");
	arch1_2->setPosition(posXarchs1, posYarchs1);
	archivos1.insert(1, arch1_2);
	addChild(arch1_2, 2);

	posXCarpeta1 = 50;
	posYCarpeta1 = 200;

	carpeta1 = new Carpeta(archivos1, 1, 1);
	carpeta1->imagen->setPosition(posXCarpeta1, posYCarpeta1);
	carpeta1->pasar->setPosition(posXarchs1 + 90, posYarchs1 - 230);
	carpeta1->escanear->setPosition(posXarchs1 + 165, posYarchs1 - 230);
	carpeta1->abierta->setPosition(posXCarpeta1, posYCarpeta1);
	addChild(carpeta1->botones, 2);
	addChild(carpeta1->abierta, 2);

	//Carpeta2
	posXarchs2 = 1000;
	posYarchs2 = 420;

	arch2_1 = Sprite::create("denegado.png");
	arch2_1->setPosition(posXarchs2, posYarchs2);
	archivos2.insert(0, arch2_1);
	addChild(arch2_1, 2);

	posXCarpeta2 = visibleSize.width / 2;
	posYCarpeta2 = visibleSize.height / 2;

	carpeta2 = new Carpeta(archivos2, -1, 1);
	carpeta2->imagen->setPosition(posXCarpeta2, posYCarpeta2);
	carpeta2->imagen->setColor(ccc3(200, 0, 0));
	carpeta2->abierta->setColor(ccc3(200, 0, 0));
	carpeta2->pasar->setPosition(posXarchs2 + 90, posYarchs2 - 230);
	carpeta2->escanear->setPosition(posXarchs2 + 165, posYarchs2 - 230);
	carpeta2->abierta->setPosition(posXCarpeta2, posYCarpeta2);
	addChild(carpeta2->botones, 2);
	addChild(carpeta2->abierta, 2);

	//Mensajes tutorial
	tuto1 = Sprite::create("tutorial1.png");
	tuto1->setPosition(visibleSize.width / 2,
		visibleSize.height / 2 - tuto1->getContentSize().height / 2 - 35);
	addChild(tuto1, 4);

	//Barra tareas
	barra = Sprite::create("Barra_tareas3.png");
	barra->setPosition(visibleSize.width / 2, barra->getContentSize().height / 2);
	addChild(barra, 1);

	//Correo
	archMail_1 = Sprite::create("webster_correo1.png");
	posXarchsMail = visibleSize.width - archMail_1->getContentSize().width / 2 - 55;
	posYarchsMail = visibleSize.height / 2 - 40;
	archMail_1->setPosition(posXarchsMail, posYarchsMail);
	allMails.insert(0, archMail_1);
	addChild(archMail_1, 2);

	archMail_2 = Sprite::create("webster_correo2.png");
	archMail_2->setPosition(posXarchsMail, posYarchsMail);
	allMails.insert(1, archMail_2);
	addChild(archMail_2, 2);

	archMail_3 = Sprite::create("webster_correo3.png");
	archMail_3->setPosition(posXarchsMail, posYarchsMail);
	allMails.insert(2, archMail_3);
	addChild(archMail_3, 2);

	posXMail = visibleSize.width / 2 + 165;
	posYMail = barra->getContentSize().height / 2;

	mail = new Carpeta(allMails, -1, 3);
	mail->imagen->setPosition(posXMail, posYMail);
	mail->pasar->setPosition(posXarchsMail + 20, posYarchsMail - 257);
	mail->escanear->setPosition(posXarchsMail + 120, posYarchsMail - 257);
	mail->abierta->setPosition(posXMail, posYMail);
	addChild(mail->botones, 2);
	addChild(mail->abierta, 2);

	//Noticias
	archNews_1 = Sprite::create("webster_noticia1.png");
	posXarchsNews = visibleSize.width - archNews_1->getContentSize().width / 2 - 30;
	posYarchsNews = visibleSize.height / 2;
	archNews_1->setPosition(posXarchsNews, posYarchsNews);
	allNoticias.insert(0, archNews_1);
	addChild(archNews_1, 2);

	posXNoticias = visibleSize.width / 2 + 295;
	posYNoticias = barra->getContentSize().height / 2;

	noticias = new Carpeta(allNoticias, -1, 6);
	noticias->imagen->setPosition(posXNoticias, posYNoticias);
	noticias->pasar->setPosition(posXarchsNews - 40, posYarchsNews - 250);
	noticias->escanear->setPosition(posXarchsNews + 40, posYarchsNews - 250);
	noticias->abierta->setPosition(posXNoticias, posYNoticias);
	addChild(noticias->botones, 2);
	addChild(noticias->abierta, 2);
	
	//Estado
	estado = Sprite::create("estado.png");
	estado->setPosition(visibleSize.width / 2,
		barra->getContentSize().height / 2 + 10);
	addChild(estado, 2);

	//Musica y boton pausa
	auto pause_button = MenuItemImage::create("pause.png", "pause.png",
		CC_CALLBACK_1(Tutorial::goToPauseScene, this));
	pause_button->setPosition(164, visibleSize.height - 25);

	auto musica = MenuItemImage::create("musica.png", "musica.png",
		CC_CALLBACK_1(Tutorial::playMusic, this));
	musica->setPosition(visibleSize.width / 2 - 287,
		barra->getContentSize().height / 2);
	
	//Menu con botones
	auto menu = Menu::create(pause_button, musica, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 3);

	/*
	mail = new Carpeta(archivos2, -1, 3);
	mail->imagen->setPosition(160, 45);
	mail->abierta->setPosition(160, 45);
	addChild(mail->botones, 1);
	addChild(mail->abierta, 1);


	pensamientos = new Carpeta(archivos2, -1, 55);
	pensamientos->imagen->setPosition(310, 45);
	pensamientos->abierta->setPosition(310, 45);
	addChild(pensamientos->botones, 1);
	addChild(pensamientos->abierta, 1);
	*/

	//Virus
	allCarpetas.insert(0, carpeta1);
	allCarpetas.insert(1, noticias);
	allCarpetas.insert(2, mail);

	virus1 = new Virus(allCarpetas, 1, 3);
	virus1->imagen->setPosition(posXarchs1, posYarchs1);
	addChild(virus1->boton, 5);

	allVirus.insert(0, virus1);

	addChild(virus1->spritebatch, 5);
	addChild(virus1->imagenAturdido, 5);

	//Animacion escaneando
	SpriteBatchNode* spritebatch = SpriteBatchNode::create("Escanear_sheet.png");
	SpriteFrameCache* cache = SpriteFrameCache::getInstance();
	cache->addSpriteFramesWithFile("Escanear_sheet.plist");

	cargando1 = Sprite::createWithSpriteFrameName("Escanear01.png");
	spritebatch->addChild(cargando1, 4);
	addChild(spritebatch, 4);

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
	spritebatch2->addChild(animFuego, 4);
	addChild(spritebatch2, 4);
	animFuego->setPosition(papeleraSprite->getPosition().x,
		papeleraSprite->getPosition().y);
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
	background->setPosition(Point((visibleSize.width / 2),
		(visibleSize.height / 2)));
	addChild(background, 0);

	this->scheduleUpdate();

	//Eventos de ratón
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

void Tutorial::playMusic(Ref *pSender) {
	if (!musicaWebster->isBackgroundMusicPlaying()) {
		musicaWebster->resumeBackgroundMusic();
	}
	else {
		musicaWebster->pauseBackgroundMusic();
	}
}

//Pausa
void Tutorial::goToPauseScene(Ref *pSender) {
	auto scene = PauseScene::createScene();
	Director::getInstance()->pushScene(scene);
}

//Muerto
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
	_cursorSprite->setPosition(e->getCursorX() + 17, e->getCursorY() - 17);
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
					if (virus->tipoVirus == 1 || virus->tipoVirus == 3)
						virus->reciclar();

					else if (virus->tipoVirus == 2)
					{
						bool cuernosValido = true;
						for (const auto& otroVirus : allVirus)
						{
							if ((otroVirus->tipoVirus == 1 || otroVirus->tipoVirus == 3)
								&& (!otroVirus->enPapelera && !otroVirus->muerto))
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
/*
void Tutorial::menuCloseCallback(Ref* pSender)
{
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}*/