#include "Alice.h"
#include "Carpeta.h"
#include "Virus.h"
#include "PauseScene.h"
#include "GameOver.h"
#include "Final.h"
#include "PauseScene.h"

USING_NS_CC;

Scene* Alice::createScene()
{
	auto scene = Scene::create();
	auto layer = Alice::create();
	scene->addChild(layer);
	return scene;
}

bool Alice::init()
{
	if (!Layer::init())
	{
		return false;
	}
	PauseScene::AlicePantalla = 0;

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
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("/music/notificacion_estado.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("/music/acierto_escaneo.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("/music/fallo_escaneo.mp3");

	//Cursor
	_cursorSprite = Sprite::create("cursor1.png");
	addChild(_cursorSprite, 7);
	_cursorSprite->setVisible(false);

	_cursorSprite2 = Sprite::create("cursor2.png");
	addChild(_cursorSprite2, 6);

	//Papelera
	papeleraSprite = Sprite::create("papelera.png");
	papeleraSprite->setPosition(visibleSize.width - papeleraSprite->getContentSize().width / 2 - 15,
		visibleSize.height - papeleraSprite->getContentSize().height / 2 - 15);
	addChild(papeleraSprite, 3);
	/*//barravida
	Vida = Sprite::create("ChicaInt.png");
	Vida->setPosition(origin.x + interfazSprite->getContentSize().width / 2,
		origin.y + visibleSize.height - interfazSprite->getContentSize().height / 2);
	addChild(interfazSprite, 1);*/

	//Interfaz
	interfazSprite = Sprite::create("ChicaInt.png");
	interfazSprite->setPosition(origin.x + interfazSprite->getContentSize().width / 2,
		origin.y + visibleSize.height - interfazSprite->getContentSize().height / 2);
	addChild(interfazSprite, 1);

	//Labels
	NDosis = 2;
	Dosis = Label::createWithSystemFont("1", "Arial.ttf", 26);
	std::string letra = std::to_string(NDosis);
	Dosis->setString(letra);
	Dosis->setColor(Color3B(0, 0, 0));
	Dosis->setPosition(174, visibleSize.height - 159);
	addChild(Dosis, 2);

	Alarma = Label::createWithSystemFont("!", "Impact.ttf", 26);
	Alarma->setColor(Color3B(255, 0, 0));
	Alarma->setPosition(250, visibleSize.height - 159);
	addChild(Alarma, 2);

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

	posXChecked2 = 225;
	posYChecked2 = visibleSize.height - 110;

	noChecked2 = Sprite::create("noCheck.png");
	noChecked2->setPosition(posXChecked2, posYChecked2);
	noChecked2->setVisible(true);
	addChild(noChecked2, 2);

	Checked2 = Sprite::create("Check.png");
	Checked2->setPosition(posXChecked2, posYChecked2);
	Checked2->setVisible(false);
	addChild(Checked2, 2);

	//Carpeta1
	posXarchs1 = 240;
	posYarchs1 = 345;

	arch1_1 = Sprite::create("HijaFamilia.png");
	arch1_1->setPosition(posXarchs1, posYarchs1);
	archivos1.insert(0, arch1_1);
	addChild(arch1_1, 2);

	arch1_2 = Sprite::create("HijaTrabajo.png");
	arch1_2->setPosition(posXarchs1, posYarchs1);
	archivos1.insert(1, arch1_2);
	addChild(arch1_2, 2);

	arch1_3 = Sprite::create("HijaPadre.png");
	arch1_3->setPosition(posXarchs1, posYarchs1);
	archivos1.insert(2, arch1_3);
	addChild(arch1_3, 2);

	posXCarpeta1 = interfazSprite->getPosition().x + 300;
	posYCarpeta1 = interfazSprite->getPosition().y + 50;

	carpeta1 = new Carpeta(archivos1, 1, 1);
	carpeta1->imagen->setPosition(posXCarpeta1, posYCarpeta1);
	carpeta1->pasar->setPosition(posXarchs1 + 90, posYarchs1 - 230);
	carpeta1->escanear->setPosition(posXarchs1 + 165, posYarchs1 - 230);
	carpeta1->abierta->setPosition(posXCarpeta1, posYCarpeta1);
	addChild(carpeta1->botones, 2);
	addChild(carpeta1->abierta, 2);

	//Carpeta2
	posXarchs2 = visibleSize.width / 2 + 85;
	posYarchs2 = visibleSize.height / 2;

	arch2_1 = Sprite::create("trabajohistoria.png");
	arch2_1->setPosition(posXarchs2, posYarchs2);
	archivos2.insert(0, arch2_1);
	addChild(arch2_1, 2);

	arch2_2 = Sprite::create("resfriado.png");
	arch2_2->setPosition(posXarchs2, posYarchs2);
	archivos2.insert(1, arch2_2);
	addChild(arch2_2, 2);

	posXCarpeta2 = 100;
	posYCarpeta2 = 49;

	carpeta2 = new Carpeta(archivos2, -1, 1);
	carpeta2->imagen->setPosition(posXCarpeta2, posYCarpeta2);
	carpeta2->pasar->setPosition(posXarchs2 + 90, posYarchs2 - 230);
	carpeta2->escanear->setPosition(posXarchs2 + 165, posYarchs2 - 230);
	carpeta2->abierta->setPosition(posXCarpeta2, posYCarpeta2);
	addChild(carpeta2->botones, 2);
	addChild(carpeta2->abierta, 2);

	//Carpeta3
	posXarchs3 = 900;
	posYarchs3 = 400;

	arch3_1 = Sprite::create("gato1.png");
	arch3_1->setPosition(posXarchs3, posYarchs3);
	archivos3.insert(0, arch3_1);
	addChild(arch3_1, 2);

	posXCarpeta3 = carpeta1->imagen->getPosition().x + 250;
	posYCarpeta3 = carpeta1->imagen->getPosition().y - 50;

	carpeta3 = new Carpeta(archivos3, -1, 1);
	carpeta3->imagen->setPosition(posXCarpeta3, posYCarpeta3);
	carpeta3->abierta->setPosition(posXCarpeta3, posYCarpeta3);
	carpeta3->pasar->setPosition(posXarchs3 + 90, posYarchs3 - 230);
	carpeta3->escanear->setPosition(posXarchs3 + 165, posYarchs3 - 230);
	addChild(carpeta3->botones, 2);
	addChild(carpeta3->abierta, 2);

	//Barra tareas
	auto tinto = TintTo::create(0.0f, 255.0f, 102.0f, 255.0f);
	barra = Sprite::create("Barra_tareas3.png");
	barra->setPosition(visibleSize.width / 2, barra->getContentSize().height / 2);
	addChild(barra, 1);
	barra->runAction(tinto);

	//Correo
	archMail_1 = Sprite::create("alice_correo1.png");
	posXarchsMail = visibleSize.width - archMail_1->getContentSize().width / 2 - 55;
	posYarchsMail = visibleSize.height / 2 - 40;
	archMail_1->setPosition(posXarchsMail, posYarchsMail);
	allMails.insert(0, archMail_1);
	addChild(archMail_1, 2);

	archMail_2 = Sprite::create("alice_correo2.png");
	archMail_2->setPosition(posXarchsMail, posYarchsMail);
	allMails.insert(1, archMail_2);
	addChild(archMail_2, 2);

	posXMail = visibleSize.width / 2 + 165;
	posYMail = barra->getContentSize().height / 2;

	mail = new Carpeta(allMails, 1, 3);
	mail->imagen->setPosition(posXMail, posYMail);
	mail->pasar->setPosition(posXarchsMail + 20, posYarchsMail - 257);
	mail->escanear->setPosition(posXarchsMail + 120, posYarchsMail - 257);
	mail->abierta->setPosition(posXMail, posYMail);
	addChild(mail->botones, 2);
	addChild(mail->abierta, 2);

	//Noticias
	archNews_1 = Sprite::create("alice_noticia1.png");
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
	archStatus_1 = Sprite::create("estadoAlice.png");
	posXarchsStatus = visibleSize.width / 2;
	posYarchsStatus = visibleSize.height / 2 - 200;
	archStatus_1->setPosition(posXarchsStatus, posYarchsStatus);
	allStatus.insert(0, archStatus_1);
	addChild(archStatus_1, 4);

	posXStatus = visibleSize.width / 2 ;
	posYStatus = visibleSize.height / 2 - 330;

	estado = new Carpeta(allStatus, -1, 4);
	estado->imagen->setPosition(posXStatus, posYStatus);
	estado->pasar->setPosition(-100, -100);
	estado->escanear->setPosition(-100, -100);
	estado->abierta->setPosition(posXStatus, posYStatus);
	addChild(estado->botones, 2);
	addChild(estado->abierta, 2);

	//Pensamiento
	archThoughs_1 = Sprite::create("pensamientos_alice.png");
	posXarchsThoughs = visibleSize.width / 2;
	posYarchsThoughs = visibleSize.height / 2 - 200;
	archThoughs_1->setPosition(posXarchsThoughs, posYarchsThoughs);
	allStatus.insert(0, archThoughs_1);
	addChild(archThoughs_1, 2);

	posXThoughs = visibleSize.width / 2 - 160;
	posYThoughs = visibleSize.height / 2 - 330;

	pensamientos = new Carpeta(allStatus, -1, 5);
	pensamientos->imagen->setPosition(posXThoughs, posYThoughs);
	pensamientos->pasar->setPosition(-100, -100);
	pensamientos->escanear->setPosition(-100, -100);
	pensamientos->abierta->setPosition(posXThoughs, posYThoughs);
	addChild(pensamientos->botones, 2);
	addChild(pensamientos->abierta, 2);

	//Musica, boton pausa y terminar nivel
	auto pause_button = MenuItemImage::create("pause.png", "pause.png",
		CC_CALLBACK_1(Alice::goToPauseScene, this));
	pause_button->setPosition(165, visibleSize.height - 26);

	musica = MenuItemImage::create("musica.png", "musica.png",
		CC_CALLBACK_1(Alice::playMusic, this));
	musica->setPosition(visibleSize.width / 2 - 287,
		barra->getContentSize().height / 2);
	/*
	pasarNivel = MenuItemImage::create("BotonFicha.png", "BotonFicha2.png",
		CC_CALLBACK_1(Alice::playMusic, this));
	pasarNivel->setPosition(posXarchs3, posYarchs3 - 230);
	pasarNivel->setVisible(false);*/

	//Menu con botones
	auto menu = Menu::create(pause_button, musica, pasarNivel, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 3);

	/*
	pensamientos = new Carpeta(archivos2, -1, 55);
	pensamientos->imagen->setPosition(310, 45);
	pensamientos->abierta->setPosition(310, 45);
	addChild(pensamientos->botones, 1);
	addChild(pensamientos->abierta, 1);
	*/

	//Virus
	allCarpetas.insert(0, carpeta1);
	allCarpetas.insert(1, carpeta2);
	allCarpetas.insert(2, carpeta3);
	allCarpetas.insert(3, noticias);
	allCarpetas.insert(4, mail);

	virus1 = new Virus(allCarpetas, 1, 1);
	virus1->imagen->setPosition(posXarchsMail, posYarchsMail);
	addChild(virus1->boton, 5);

	allVirus.insert(0, virus1);

	addChild(virus1->spritebatch, 5);
	addChild(virus1->imagenAturdido, 5);

	virus2 = new Virus(allCarpetas, 2, 1);
	virus2->imagen->setPosition(posXarchs2, posYarchs2);
	addChild(virus2->boton, 5);

	allVirus.insert(1, virus2);

	addChild(virus2->spritebatch, 5);
	addChild(virus2->imagenAturdido, 5);

	virus3 = new Virus(allCarpetas, 3, 2);
	virus3->imagen->setPosition(posXarchs2, posYarchs2);
	addChild(virus3->boton, 5);

	allVirus.insert(2, virus3);

	addChild(virus3->spritebatch, 5);
	addChild(virus3->imagenAturdido, 5);

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
	auto background = Sprite::create("FondoAlice.png");
	background->setPosition(Point((visibleSize.width / 2),
		(visibleSize.height / 2)));
	addChild(background, 0);

	this->scheduleUpdate();

	//Eventos de ratón
	auto mouseListener = EventListenerMouse::create();
	mouseListener->onMouseMove = CC_CALLBACK_1(Alice::onMouseMove, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(mouseListener, this);

	auto mouseListener2 = EventListenerMouse::create();
	mouseListener2->onMouseDown = CC_CALLBACK_1(Alice::onMouseDown, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(mouseListener2, this);

	auto mouseListener3 = EventListenerMouse::create();
	mouseListener3->onMouseUp = CC_CALLBACK_1(Alice::onMouseUp, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(mouseListener3, this);

	auto mouseListener4 = EventListenerMouse::create();
	mouseListener4->onMouseScroll = CC_CALLBACK_1(Alice::onMouseScroll, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(mouseListener4, this);

	return true;
}

void Alice::playMusic(Ref *pSender) {
	if (!musicaWebster->isBackgroundMusicPlaying()) {
		musicaWebster->resumeBackgroundMusic();
	}
	else {
		musicaWebster->pauseBackgroundMusic();
	}
}

//Pausa
void Alice::goToPauseScene(Ref *pSender) {
	auto scene = PauseScene::createScene();
	Director::getInstance()->pushScene(scene);
}

//Muerto
void Alice::goToGameOver(Ref *pSender) {
	auto scene = GameOver::createScene();
	Director::getInstance()->pushScene(scene);
}

void  Alice::onMouseDown(Event *event)
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
				secuenciaEscaneo = Sequence::create(DelayTime::create(3.0f), CallFunc::create(CC_CALLBACK_0(Alice::escaneando, this)), NULL);
				cargando1->setPosition(carpetaElegida->contenido.at(carpetaElegida->elegido)->getPosition().x,
					carpetaElegida->contenido.at(carpetaElegida->elegido)->getPosition().y);
				cargando1->setVisible(true);
				carpetaElegida->imagen->runAction(secuenciaEscaneo);
			}
		}
	}
}

void Alice::onMouseMove(Event *event)
{
	auto *e = dynamic_cast<EventMouse *>(event);
	_cursorSprite2->setPosition(e->getCursorX() + 16, e->getCursorY() - 16);
	_cursorSprite->setPosition(_cursorSprite2->getPosition().x - 14, _cursorSprite2->getPosition().y + 14);
}

void Alice::onMouseUp(Event *event)
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

void Alice::onMouseScroll(Event *event)
{
	if (NDosis > 0) {
		NDosis--;
		std::string letra = std::to_string(NDosis);
		Dosis->setString(letra);
		papeleraSprite->setColor(ccc3(255, 0, 0));
		animFuego->setVisible(true);
		auto secuencia = Sequence::create(DelayTime::create(1.0f), CallFunc::create(CC_CALLBACK_0(Alice::changeColor, this)), NULL);
		papeleraSprite->runAction(secuencia);

		for (const auto& virus : allVirus)
		{
			if (virus->enPapelera && !virus->muerto)
			{
				virus->muerto = true;
			}
		}
	}
}

void Alice::changeColor(void)
{
	papeleraSprite->setColor(ccc3(255, 255, 255));
	animFuego->setVisible(false);
}

void Alice::update(float dt)
{
	bool todosvisibles=true;
	for (const auto& virus : allVirus)
	{
		if (!virus->iniciado)
		{
			todosvisibles = false;
		}
	}

	bool todosmuertos= true;
	for (const auto& virus : allVirus)
	{
		if (!virus->muerto)
		{
			todosmuertos = false;
		}
	}
	if(todosmuertos)
	{
		goToFinal(this);
	}
	if (todosvisibles && Alarma->isVisible()) { 
		Alarma->setVisible(false); 
	}
	
	if (estado->contenido.at(0)->isVisible() && bool_aux) {
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("/music/notificacion_estado.mp3");
		bool_aux = false;
	}
	else if (!estado->contenido.at(0)->isVisible()){
		bool_aux = true;
	}

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

	if (mail->validoEscaneado == 1) {
		Checked2->setVisible(true);
	}

	if (mail->abierta->isVisible()) {
		virus1->iniciado = true;
	}

	if (carpeta2->abierta->isVisible()) {
		virus2->iniciado = true;
		virus3->iniciado = true;
	}

	if (virusElegido != nullptr) {
		virusElegido->imagen->setPosition(_cursorSprite->getPosition().x, _cursorSprite->getPosition().y);
	}
}

void Alice::escaneando(void)
{
	if (carpetaElegida != nullptr)
	{
		carpetaElegida->tiempoEscanear = true;
		cargando1->setVisible(false);
	}
}
void Alice::goToFinal(Ref *pSender) {
	PauseScene::AlicePantalla = 1;
	auto scene2 = Final::createScene();
	Director::getInstance()->pushScene(scene2);
}