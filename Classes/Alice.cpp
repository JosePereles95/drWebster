#include "Alice.h"
#include "Carpeta.h"
#include "Virus.h"
#include "PauseScene.h"
#include "GameOver.h"
#include "Final.h"

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
	musicaAlice = CocosDenshion::SimpleAudioEngine::getInstance();
	musicaAlice->playBackgroundMusic("/music/alice.mp3", true);
	musicaAlice->stopBackgroundMusic(false);

	//Efectos
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("/music/carpeta.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("/music/notificacion_estado.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("/music/acierto_escaneo.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("/music/fallo_escaneo.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("/music/abre1.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("/music/cierra1.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("/music/scan.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("/music/aturde.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("/music/quemar.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("/music/victory2.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("/music/monitor.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("/music/final_nivel.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("/music/error_papelera.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("/music/ventosa.mp3");

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

	//Barra de vida
	barraVida = Sprite::create("BarraVida.png");
	barraVida->setPosition(302, 702); // La vida dura 228
	addChild(barraVida, 1);

	//Interfaz
	interfazSprite = Sprite::create("ChicaInt.png");
	interfazSprite->setPosition(origin.x + interfazSprite->getContentSize().width / 2,
		origin.y + visibleSize.height - interfazSprite->getContentSize().height / 2);
	addChild(interfazSprite, 1);

	//Mensaje1
	victorySprite = Sprite::create("mensaje_scan.png");
	victorySprite->setPosition(interfazSprite->getPosition().x - 15,
		interfazSprite->getPosition().y - 140);
	addChild(victorySprite, 4);
	victorySprite->setVisible(false);

	//Mensaje2
	sanoSprite = Sprite::create("mensaje_vida.png");
	sanoSprite->setPosition(interfazSprite->getPosition().x - 15,
		interfazSprite->getPosition().y - 225);
	addChild(sanoSprite, 4);
	sanoSprite->setVisible(false);

	//Labels
	NDosis = 1;
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
	posXarchs1 = 255;
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
	carpeta1->pasar->setPosition(posXarchs1 + 110, posYarchs1 + 260);
	carpeta1->escanear->setPosition(posXarchs1 + 160, posYarchs1 + 260);
	carpeta1->cerrar->setPosition(posXarchs1 + 210, posYarchs1 + 260);
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
	carpeta2->pasar->setPosition(posXarchs2 + 110, posYarchs2 + 260);
	carpeta2->escanear->setPosition(posXarchs2 + 160, posYarchs2 + 260);
	carpeta2->cerrar->setPosition(posXarchs2 + 210, posYarchs2 + 260);
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
	posYCarpeta3 = carpeta1->imagen->getPosition().y + 10;

	carpeta3 = new Carpeta(archivos3, -1, 1);
	carpeta3->imagen->setPosition(posXCarpeta3, posYCarpeta3);
	carpeta3->abierta->setPosition(posXCarpeta3, posYCarpeta3);
	carpeta3->pasar->setPosition(-100, -100);
	carpeta3->escanear->setPosition(posXarchs3 + 160, posYarchs3 + 260);
	carpeta3->cerrar->setPosition(posXarchs3 + 210, posYarchs3 + 260);
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
	mail->pasar->setPosition(posXarchsMail + 130, posYarchsMail + 214);
	mail->escanear->setPosition(posXarchsMail + 175, posYarchsMail + 214);
	mail->cerrar->setPosition(posXarchsMail + 220, posYarchsMail + 214);
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
	noticias->pasar->setPosition(-100, -100);
	noticias->escanear->setPosition(posXarchsNews + 160, posYarchsNews + 260);
	noticias->cerrar->setPosition(posXarchsNews + 210, posYarchsNews + 260);
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
	estado->cerrar->setPosition(posXarchsStatus + 130, posYarchsStatus + 80);
	estado->abierta->setPosition(posXStatus, posYStatus);
	addChild(estado->botones, 4);
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
	pensamientos->cerrar->setPosition(posXarchsThoughs + 130, posYarchsThoughs + 80);
	pensamientos->abierta->setPosition(posXThoughs, posYThoughs);
	addChild(pensamientos->botones, 2);
	addChild(pensamientos->abierta, 2);

	//Musica, boton pausa y terminar nivel
	auto pause_button = MenuItemImage::create("pause.png", "pause.png",
		CC_CALLBACK_1(Alice::goToPauseScene, this));
	pause_button->setPosition(165, visibleSize.height - 26);

	musica = MenuItemImage::create("musica.png", "musica1.png",
		CC_CALLBACK_1(Alice::playMusic, this));
	musica->setPosition(visibleSize.width / 2 - 287,
		barra->getContentSize().height / 2);

	//Menu con botones
	auto menu = Menu::create(pause_button, musica, pasarNivel, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 3);

	//Virus
	allCarpetas.insert(0, carpeta1);
	allCarpetas.insert(1, carpeta2);
	allCarpetas.insert(2, carpeta3);
	allCarpetas.insert(3, noticias);
	allCarpetas.insert(4, mail);

	for (const auto& carpeta : allCarpetas)
	{
		vidaTotal += (float) carpeta->vida;
	}

	relVida = (float) (228.0f / vidaTotal);

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

	//chapuzas booleanas
	bool_aux2 = true;
	bool_aux3 = true;
	bool_aux4 = true;
	tiempoEspera = true;
	diagnostico = true;
	bool_auxshake = false;

	//Shake
	punto = this->getPosition();

	//Animacion escaneando
	SpriteBatchNode* spritebatch = SpriteBatchNode::create("Escanear_sheet.png");
	SpriteFrameCache* cache = SpriteFrameCache::getInstance();
	cache->addSpriteFramesWithFile("Escanear_sheet.plist");

	cargando1 = Sprite::createWithSpriteFrameName("Escanear01.png");
	spritebatch->addChild(cargando1, 4);
	addChild(spritebatch, 4);

	cargando1->setVisible(false);

	Vector<SpriteFrame*> animFrames(4);

	char str[100] = { 0 };
	for (int i = 1; i < 4; i++)
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
	if (!musicaAlice->isBackgroundMusicPlaying()) {
		musicaAlice->resumeBackgroundMusic();
	}
	else {
		musicaAlice->pauseBackgroundMusic();
	}
}

//Pausa
void Alice::goToPauseScene(Ref *pSender) {
	auto scene = PauseScene::createScene();
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("/music/abre1.mp3");
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
		if (virusRect.intersectsRect(cursorRect) && virus->imagen->isVisible())
		{
			//Shake
			bool_auxshake = true;
			this->schedule(schedule_selector(Alice::shakeScreen));
			if (virus->aturdido)
				virusElegido = virus;
			else {
				//Particula1
				auto sprite = Sprite::create("Textura.png");
				auto particula = ParticleSun::create();
				particula->setTexture(sprite->getTexture());
				particula->setStartColor(Color4F(255, 255, 255, 1));
				particula->setEndColor(Color4F(255, 0, 0, 0.5));
				particula->setSpeed(60);
				particula->setEmitterMode(kCCParticleModeRadius);
				particula->setStartRadius(20);
				particula->setEndRadius(30);

				particula->setStartSize(1);
				particula->setEndSize(5);
				particula->setLife(0.5);

				particula->setDuration(0.5);
				particula->setPosition(_cursorSprite->getPosition());
				addChild(particula, 6);

				//Particula2
				auto particula2 = ParticleSun::create();
				particula2->setTexture(sprite->getTexture());
				particula2->setStartColor(Color4F(255, 255, 255, 1));
				particula2->setEndColor(Color4F(255, 0, 0, 0.5));
				particula2->setSpeed(60);
				particula2->setEmitterMode(kCCParticleModeRadius);
				particula2->setStartRadius(1);
				particula2->setEndRadius(10);

				particula2->setStartSize(1);
				particula2->setEndSize(5);
				particula2->setLife(0.2);

				particula2->setDuration(0.5);
				particula2->setPosition(_cursorSprite->getPosition());
				addChild(particula2, 6);
			}
		}
	}

	for (const auto& carpeta : allCarpetas)
	{
		carpRect = carpeta->escanear->getBoundingBox();
		if (carpRect.intersectsRect(cursorRect))
		{
			carpetaElegida = carpeta;
			if (carpetaElegida->abierta->isVisible()) {
				scanEffect = CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("/music/scan.mp3");
				secuenciaEscaneo = Sequence::create(DelayTime::create(2.0f), CallFunc::create(CC_CALLBACK_0(Alice::escaneando, this)), NULL);
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

	//huella
	auto huella = Sprite::create("cursor2.png");
	huella->setPosition(_cursorSprite2->getPosition());
	huella->setOpacity(50);
	addChild(huella, 6);
	auto action = FadeOut::create(0.25);

	huella->runAction(action);
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
					if (virus->tipoVirus == 1 || virus->tipoVirus == 3) {
						virus->reciclar();
						CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("/music/ventosa.mp3");
					}
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
						if (cuernosValido) {
							virus->reciclar();
							CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("/music/ventosa.mp3");
						}
						else
							CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("/music/error_papelera.mp3");
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
		CocosDenshion::SimpleAudioEngine::getInstance()->stopEffect(scanEffect);
		cargando1->setVisible(false);
	}
}

void Alice::onMouseScroll(Event *event)
{
	if (NDosis > 0 && tiempoEspera) {
		NDosis--;
		std::string letra = std::to_string(NDosis);
		Dosis->setString(letra);
		papeleraSprite->setColor(ccc3(255, 0, 0));
		animFuego->setVisible(true);
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("/music/quemar.mp3");
		tiempoEspera = false;
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
	tiempoEspera = true;
}

void Alice::update(float dt)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	bool todosvisibles = true;
	bool todosmuertos = true;
	for (const auto& virus : allVirus)
	{
		if (!virus->iniciado)
		{
			todosvisibles = false;
		}
		if (!virus->muerto)
		{
			todosmuertos = false;
		}
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
	auto vidaPaciente = 0.0f;

	for (const auto& carpeta : allCarpetas)
	{
		vidaPaciente += (float) carpeta->vida;
		if (carpeta->vida > 0)
			hayVivas = true;
	}

	barraVida->setPositionX((float) (302.0f - (vidaTotal - vidaPaciente)*relVida));

	if (todosmuertos && diagnostico)
	{
		auto secuencia = Sequence::create(DelayTime::create(10.0f), CallFunc::create(CC_CALLBACK_0(Alice::tiempoFinal, this)), NULL);
		this->runAction(secuencia);

		if (barraVida->getPosition().x > 225.0f) { //El rango A va de 225 a 302
			auto secuencia2 = Sequence::create(DelayTime::create(1.0f), CallFunc::create(CC_CALLBACK_0(Alice::sano, this)), NULL);
			this->runAction(secuencia2);
		}

		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("/music/final_nivel.mp3");
		diag = Sprite::create("FichaAlice2.png");
		diag->setPosition(Point((visibleSize.width / 2),
			(visibleSize.height / 2)));
		addChild(diag, 3);

		BarraDiag = Sprite::create("BarraDiag.png");
		BarraDiag->setPosition(Point((visibleSize.width / 2),
			(visibleSize.height / 4)));
		addChild(BarraDiag, 4);

		texto = Label::createWithSystemFont("hello", "Impact.ttf", 20);
		Ntexto = 10;
		std::string letra2 = std::to_string(Ntexto);
		texto->setString("ENVIANDO DIAGNOSTICO  " + letra2 + "s");
		texto->setColor(Color3B(255, 0, 0));
		texto->setPosition(Point((visibleSize.width / 2.27),
			(visibleSize.height / 3.60)));
		addChild(texto, 5);

		for (int i = 0; i < 10; i++)
		{
			float delay = (i);
			auto action = Sequence::create(DelayTime::create(delay), CallFunc::create(CC_CALLBACK_0(Alice::Cargar, this)), NULL);
			this->runAction(action);
		}

		for (int i = 0; i <35; i++)
		{
			float delay = (0.3*i);
			auto action = Sequence::create(DelayTime::create(delay), CallFunc::create(CC_CALLBACK_0(Alice::Mover, this)), NULL);
			this->runAction(action);
		}

		diagnostico = false;
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

	if (carpeta1->validoEscaneado == 1 && bool_aux2) {
		Checked1->setVisible(true);
		NDosis += 1;
		std::string letra = std::to_string(NDosis);
		Dosis->setString(letra);
		bool_aux2 = false;
		//Particula3
		auto sprite = Sprite::create("Textura2.png");
		auto particula = ParticleSun::create();
		particula->setTexture(sprite->getTexture());
		particula->setStartColor(Color4F(255, 255, 255, 1));
		particula->setEndColor(Color4F(255, 255, 255, 0.5));
		particula->setSpeed(60);
		particula->setEmitterMode(kCCParticleModeRadius);
		particula->setStartRadius(1);
		particula->setEndRadius(80);

		particula->setStartSize(5);
		particula->setEndSize(20);
		particula->setLife(0.5);

		particula->setDuration(0.5);
		particula->setPosition(Checked1->getPosition());
		addChild(particula, 6);
	}

	if (mail->validoEscaneado == 1 && bool_aux3) {
		Checked2->setVisible(true);
		NDosis += 1;
		std::string letra = std::to_string(NDosis);
		Dosis->setString(letra);
		bool_aux3 = false;
		//Particula4
		auto sprite = Sprite::create("Textura2.png");
		auto particula = ParticleSun::create();
		particula->setTexture(sprite->getTexture());
		particula->setStartColor(Color4F(255, 255, 255, 1));
		particula->setEndColor(Color4F(255, 255, 255, 0.5));
		particula->setSpeed(60);
		particula->setEmitterMode(kCCParticleModeRadius);
		particula->setStartRadius(1);
		particula->setEndRadius(80);

		particula->setStartSize(5);
		particula->setEndSize(20);
		particula->setLife(0.5);

		particula->setDuration(0.5);
		particula->setPosition(Checked2->getPosition());
		addChild(particula, 6);
	}

	if (Checked1->isVisible() && Checked2->isVisible() && bool_aux4) {
		auto secuencia = Sequence::create(DelayTime::create(1.0f), CallFunc::create(CC_CALLBACK_0(Alice::victoria, this)), NULL);
		this->runAction(secuencia);
		bool_aux4 = false;
	}

	if (mail->abierta->isVisible() || !mail->imagen->isVisible()) {
		virus1->iniciado = true;
	}

	if (carpeta2->abierta->isVisible() || !carpeta2->imagen->isVisible()) {
		virus2->iniciado = true;
		virus3->iniciado = true;
	}

	if (virusElegido != nullptr) {
		virusElegido->imagen->setPosition(_cursorSprite->getPosition().x, _cursorSprite->getPosition().y);
	}
	
}

void Alice::victoria(void) {
	victorySprite->setVisible(true);
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("/music/victory2.mp3");
	auto secuencia = Sequence::create(DelayTime::create(4.0f), CallFunc::create(CC_CALLBACK_0(Alice::quitaMensaje, this)), NULL);
	victorySprite->runAction(secuencia);
}

void Alice::sano(void) {
	sanoSprite->setVisible(true);
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("/music/victory2.mp3");
	auto secuencia = Sequence::create(DelayTime::create(4.0f), CallFunc::create(CC_CALLBACK_0(Alice::quitaMensaje2, this)), NULL);
	sanoSprite->runAction(secuencia);
}

void Alice::quitaMensaje(void) {
	victorySprite->setVisible(false);
}

void Alice::quitaMensaje2(void) {
	sanoSprite->setVisible(false);
}

void Alice::escaneando(void)
{
	if (carpetaElegida != nullptr)
	{
		carpetaElegida->tiempoEscanear = true;
		CocosDenshion::SimpleAudioEngine::getInstance()->stopEffect(scanEffect);
		cargando1->setVisible(false);
	}
}

void Alice::Mover(void)
{

	auto action = FadeOut::create(2);
	auto flecha = Sprite::create("flechaDiag.png");
	flecha->setPosition(BarraDiag->getPosition().x - BarraDiag->getContentSize().width / 2 + 30, BarraDiag->getPosition().y - 15);
	auto vect = flecha->getPosition();
	vect.x += 350;
	auto moverse = MoveTo::create(2, vect);
	flecha->runAction(moverse);
	flecha->runAction(action);
	addChild(flecha, 5);
}

void Alice::Cargar(void)
{
	Ntexto--;
	std::string letra3 = std::to_string(Ntexto);
	texto->setString("ENVIANDO DIAGNOSTICO  " + letra3 + "s");
}

void Alice::tiempoFinal(void) {
	goToFinal(this);
}

void Alice::goToFinal(Ref *pSender) {
	PauseScene::AlicePantalla = 1;
	auto scene2 = Final::createScene();
	Director::getInstance()->pushScene(scene2);
}
//Shake Metodos
void Alice::shakeScreen(float dt)
{
	float randx = rangeRandom(-1.5f, 1.5);
	float randy = rangeRandom(-1.5f, 1.5);

	this->setPosition(Point(randx, randy));
	this->setPosition(Point(punto.x + randx, punto.y + randy));


	if (!bool_auxshake) {
		//bool_auxshake = false;
		this->setPosition(Point(punto.x, punto.y));
		this->unschedule(schedule_selector(Alice::shakeScreen));
	}
	else {
		auto detenershake = Sequence::create(DelayTime::create(0.5f), CallFunc::create(CC_CALLBACK_0(Alice::Detenershake, this)), NULL);
		this->runAction(detenershake);
	}

}
void Alice::Detenershake(void)
{
	bool_auxshake = false;
	this->schedule(schedule_selector(Alice::shakeScreen));

}
float Alice::rangeRandom(float min, float max)
{
	float rnd = ((float)rand() / (float)RAND_MAX);
	return rnd*(max - min) + min;
}