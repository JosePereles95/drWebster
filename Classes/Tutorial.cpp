#include "Tutorial.h"
#include "Carpeta.h"
#include "Virus.h"
#include "PauseScene.h"
#include "GameOver.h"
#include "Alice.h"
#include "AnimacionScene.h"
#include "PauseScene.h"

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
	PauseScene::TutorialPantalla = 0;
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

	//Interfaz
	interfazSprite = Sprite::create("IntWebster.png");
	interfazSprite->setPosition(origin.x + interfazSprite->getContentSize().width / 2,
		origin.y + visibleSize.height - interfazSprite->getContentSize().height / 2);
	addChild(interfazSprite, 1);

	//Labels
	Dosis= Label::createWithSystemFont("1", "Arial.ttf", 26);
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

	//Carpeta1
	posXarchs1 = 350;
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
	carpeta1->imagen->setVisible(false);
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
	carpeta2->imagen->setVisible(false);
	addChild(carpeta2->abierta, 2);

	//Carpeta3
	posXarchs3 = 1100;
	posYarchs3 = 440;

	arch3_1 = Sprite::create("FichaAlice.png");
	arch3_1->setPosition(posXarchs3, posYarchs3);
	archivos3.insert(0, arch3_1);
	addChild(arch3_1, 3);

	posXCarpeta3 = 75;
	posYCarpeta3 = 450;

	carpeta3 = new Carpeta(archivos3, -1, 1);
	carpeta3->imagen->setPosition(posXCarpeta3, posYCarpeta3);
	carpeta3->abierta->setPosition(posXCarpeta3, posYCarpeta3);
	carpeta3->escanear->setVisible(false);
	carpeta3->pasar->setVisible(false);
	addChild(carpeta3->botones, 2);
	carpeta3->imagen->setVisible(false);
	addChild(carpeta3->abierta, 2);

	//Carpeta4
	posXarchs4 = 1100;
	posYarchs4 = 450;

	arch4_1 = Sprite::create("About.png");
	arch4_1->setPosition(posXarchs4, posYarchs4);
	archivos4.insert(0, arch4_1);
	addChild(arch4_1, 2);

	posXCarpeta4 = visibleSize.width / 2;
	posYCarpeta4 = visibleSize.height / 2 + 100;

	carpeta4 = new Carpeta(archivos4, -1, 1);
	carpeta4->imagen->setPosition(posXCarpeta4, posYCarpeta4);
	carpeta4->pasar->setPosition(posXarchs4 + 90, posYarchs4 - 230);
	carpeta4->escanear->setPosition(posXarchs4 + 165, posYarchs4 - 230);
	carpeta4->abierta->setPosition(posXCarpeta4, posYCarpeta4);
	addChild(carpeta4->botones, 2);
	carpeta4->imagen->setVisible(false);
	addChild(carpeta4->abierta, 2);

	//Mensajes tutorial
	tuto1 = Sprite::create("tutorial1.png");
	tuto1->setPosition(visibleSize.width / 2,
		visibleSize.height / 2 - tuto1->getContentSize().height / 2 - 35);
	addChild(tuto1, 4);
	tuto1->setVisible(false);

	tuto2 = Sprite::create("tutorial2.png");
	tuto2->setPosition(visibleSize.width / 2,
		visibleSize.height / 2 - tuto2->getContentSize().height / 2 - 35);
	addChild(tuto2, 4);
	tuto2->setVisible(false);

	tuto3 = Sprite::create("tutorial3.png");
	tuto3->setPosition(visibleSize.width / 2,
		visibleSize.height / 2 - tuto3->getContentSize().height / 2 - 35);
	addChild(tuto3, 4);
	tuto3->setVisible(false);

	tuto4 = Sprite::create("tutorial4.png");
	tuto4->setPosition(visibleSize.width / 2,
		visibleSize.height / 2 - tuto4->getContentSize().height / 2 - 35);
	addChild(tuto4, 4);
	tuto4->setVisible(false);

	tuto5 = Sprite::create("tutorial5.png");
	tuto5->setPosition(visibleSize.width / 2,
		visibleSize.height / 2 - tuto5->getContentSize().height / 2 - 35);
	addChild(tuto5, 4);
	tuto5->setVisible(false);

	tuto6 = Sprite::create("tutorial6.png");
	tuto6->setPosition(visibleSize.width / 2,
		visibleSize.height / 2 - tuto6->getContentSize().height / 2 - 35);
	addChild(tuto6, 4);
	tuto6->setVisible(false);

	tuto7 = Sprite::create("tutorial7.png");
	tuto7->setPosition(visibleSize.width / 2,
		visibleSize.height / 2 - tuto7->getContentSize().height / 2 - 35);
	addChild(tuto7, 4);
	tuto7->setVisible(false);

	tuto8 = Sprite::create("tutorial8.png");
	tuto8->setPosition(visibleSize.width / 2,
		visibleSize.height / 2 - tuto8->getContentSize().height / 2 - 35);
	addChild(tuto8, 4);
	tuto8->setVisible(false);

	tuto9 = Sprite::create("tutorial9.png");
	tuto9->setPosition(visibleSize.width / 2,
		visibleSize.height / 2 - tuto9->getContentSize().height / 2 - 35);
	addChild(tuto9, 4);
	tuto9->setVisible(false);

	bool_aux = true;
	bool_aux2 = true;
	bool_aux3 = true;
	bool_aux4 = true;
	auto secuencia2 = Sequence::create(DelayTime::create(2.0f), CallFunc::create(CC_CALLBACK_0(Tutorial::changeTutorial1, this)), NULL);
	this->runAction(secuencia2);

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
	mail->imagen->setVisible(false);
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
	noticias->imagen->setVisible(false);
	addChild(noticias->abierta, 2);
	
	//Estado
	estado = Sprite::create("estado.png");
	estado->setPosition(visibleSize.width / 2,
		barra->getContentSize().height / 2 + 10);
	addChild(estado, 2);

	//Pensamiento
	archThoughs_1 = Sprite::create("pensamientos_webster.png");
	posXarchsThoughs = visibleSize.width / 2;
	posYarchsThoughs = visibleSize.height / 2 - 200;
	archThoughs_1->setPosition(posXarchsThoughs, posYarchsThoughs);
	allStatus.insert(0, archThoughs_1);
	addChild(archThoughs_1, 4);

	posXThoughs = visibleSize.width / 2 - 160;
	posYThoughs = visibleSize.height / 2 - 330;

	pensamientos = new Carpeta(allStatus, -1, 5);
	pensamientos->imagen->setPosition(posXThoughs, posYThoughs);
	pensamientos->pasar->setPosition(-100, -100);
	pensamientos->escanear->setPosition(-100, -100);
	pensamientos->abierta->setPosition(posXThoughs, posYThoughs);
	addChild(pensamientos->botones, 2);
	pensamientos->imagen->setVisible(false);
	addChild(pensamientos->abierta, 2);

	//Musica, boton pausa y terminar nivel
	auto pause_button = MenuItemImage::create("pause.png", "pause.png",
		CC_CALLBACK_1(Tutorial::goToPauseScene, this));
	pause_button->setPosition(164, visibleSize.height - 25);

	musica = MenuItemImage::create("musica.png", "musica.png",
		CC_CALLBACK_1(Tutorial::playMusic, this));
	musica->setPosition(visibleSize.width / 2 - 287,
		barra->getContentSize().height / 2);
	musica->setVisible(false);

	pasarNivel = MenuItemImage::create("BotonFicha.png", "BotonFicha2.png",
		CC_CALLBACK_1(Tutorial::terminarNivel, this));
	pasarNivel->setPosition(posXarchs3, posYarchs3 - 230);
	pasarNivel->setVisible(false);
	
	//Menu con botones
	auto menu = Menu::create(pause_button, musica, pasarNivel, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 3);

	//Virus
	allCarpetas.insert(0, carpeta1);
	allCarpetas.insert(1, noticias);
	allCarpetas.insert(2, mail);

	virus1 = new Virus(allCarpetas, 1, 3);
	virus1->imagen->setPosition(posXarchs2, posYarchs2);
	addChild(virus1->boton, 5);

	allVirus.insert(0, virus1);

	addChild(virus1->spritebatch, 5);
	addChild(virus1->imagenAturdido, 5);

	//Sprites falsos
	auto tinto1 = TintTo::create(0.0f, 130.0f, 130.0f, 130.0f);
	auto tinto2 = TintTo::create(0.0f, 130.0f, 130.0f, 130.0f);
	auto tinto3 = TintTo::create(0.0f, 130.0f, 130.0f, 130.0f);
	auto tinto4 = TintTo::create(0.0f, 130.0f, 130.0f, 130.0f);
	auto tinto5 = TintTo::create(0.0f, 130.0f, 130.0f, 130.0f);
	auto tinto6 = TintTo::create(0.0f, 130.0f, 130.0f, 130.0f);
	auto tinto7 = TintTo::create(0.0f, 130.0f, 130.0f, 130.0f);
	auto tinto8 = TintTo::create(0.0f, 130.0f, 130.0f, 130.0f);

	falso1 = Sprite::create("carpeta1.png");
	falso1->setPosition(carpeta1->imagen->getPosition().x, carpeta1->imagen->getPosition().y);
	addChild(falso1, 3);
	falso1->runAction(tinto1);
	falso2 = Sprite::create("carpeta1.png");
	falso2->setPosition(carpeta3->imagen->getPosition().x, carpeta3->imagen->getPosition().y);
	addChild(falso2, 3);
	falso2->runAction(tinto2);
	falso3 = Sprite::create("carpeta1.png");
	falso3->setPosition(carpeta4->imagen->getPosition().x, carpeta4->imagen->getPosition().y);
	addChild(falso3, 3);
	falso3->runAction(tinto3);
	falso4 = Sprite::create("musica.png");
	falso4->setPosition(musica->getPosition().x, musica->getPosition().y);
	addChild(falso4, 3);
	falso4->runAction(tinto4);
	falso5 = Sprite::create("pensamientos.png");
	falso5->setPosition(pensamientos->imagen->getPosition().x, pensamientos->imagen->getPosition().y);
	addChild(falso5, 3);
	falso5->runAction(tinto5);
	falso6 = Sprite::create("mail.png");
	falso6->setPosition(mail->imagen->getPosition().x, mail->imagen->getPosition().y);
	addChild(falso6, 3);
	falso6->runAction(tinto6);
	falso7 = Sprite::create("News2.png");
	falso7->setPosition(noticias->imagen->getPosition().x, noticias->imagen->getPosition().y);
	addChild(falso7, 3);
	falso7->runAction(tinto7);
	falso8 = Sprite::create("carpeta1.png");
	falso8->setColor(ccc3(200, 0, 0));
	falso8->setPosition(carpeta2->imagen->getPosition().x, carpeta2->imagen->getPosition().y);
	addChild(falso8, 3);
	falso8->runAction(tinto8);

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

void Tutorial::changeTutorial1(void) {
	tuto1->setVisible(true);
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("/music/notificacion_estado.mp3");

	auto secuencia3 = Sequence::create(DelayTime::create(5.0f), CallFunc::create(CC_CALLBACK_0(Tutorial::wait1, this)), NULL);
	this->runAction(secuencia3);
}

void Tutorial::wait1(void) {
	tuto1->setVisible(false);

	auto secuencia4 = Sequence::create(DelayTime::create(2.0f), CallFunc::create(CC_CALLBACK_0(Tutorial::changeTutorial2, this)), NULL);
	this->runAction(secuencia4);
}

void Tutorial::changeTutorial2(void) {
	tuto2->setVisible(true);
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("/music/notificacion_estado.mp3");

	falso8->setVisible(false);
	carpeta2->imagen->setVisible(true);
}

void Tutorial::wait2(void) {
	tuto2->setVisible(false);

	auto secuencia6 = Sequence::create(DelayTime::create(0.5f), CallFunc::create(CC_CALLBACK_0(Tutorial::changeTutorial3, this)), NULL);
	this->runAction(secuencia6);
}

void Tutorial::changeTutorial3(void) {
	tuto3->setVisible(true);
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("/music/notificacion_estado.mp3");

	auto secuencia7 = Sequence::create(DelayTime::create(3.0f), CallFunc::create(CC_CALLBACK_0(Tutorial::wait3, this)), NULL);
	this->runAction(secuencia7);
}

void Tutorial::wait3(void) {
	tuto3->setVisible(false);

	auto secuencia8 = Sequence::create(DelayTime::create(0.5f), CallFunc::create(CC_CALLBACK_0(Tutorial::changeTutorial4, this)), NULL);
	this->runAction(secuencia8);
}

void Tutorial::changeTutorial4(void) {
	tuto4->setVisible(true);
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("/music/notificacion_estado.mp3");
}

void Tutorial::wait4(void) {
	tuto4->setVisible(false);

	auto secuencia10 = Sequence::create(DelayTime::create(7.1f), CallFunc::create(CC_CALLBACK_0(Tutorial::changeTutorial5, this)), NULL);
	this->runAction(secuencia10);
}

void Tutorial::changeTutorial5(void) {
	tuto5->setVisible(true);
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("/music/notificacion_estado.mp3");
}

void Tutorial::wait5(void) {
	tuto5->setVisible(false);

	auto secuencia12 = Sequence::create(DelayTime::create(2.0f), CallFunc::create(CC_CALLBACK_0(Tutorial::changeTutorial6, this)), NULL);
	this->runAction(secuencia12);
}

void Tutorial::changeTutorial6(void) {
	tuto6->setVisible(true);
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("/music/notificacion_estado.mp3");
}

void Tutorial::wait6(void) {
	tuto6->setVisible(false);

	auto secuencia14 = Sequence::create(DelayTime::create(0.5f), CallFunc::create(CC_CALLBACK_0(Tutorial::changeTutorial7, this)), NULL);
	this->runAction(secuencia14);
}

void Tutorial::changeTutorial7(void) {
	tuto7->setVisible(true);
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("/music/notificacion_estado.mp3");
}

void Tutorial::wait7(void) {
	tuto7->setVisible(false);

	auto secuencia16 = Sequence::create(DelayTime::create(0.5f), CallFunc::create(CC_CALLBACK_0(Tutorial::changeTutorial8, this)), NULL);
	this->runAction(secuencia16);
}

void Tutorial::changeTutorial8(void) {
	tuto8->setVisible(true);
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("/music/notificacion_estado.mp3");
}

void Tutorial::wait8(void) {
	tuto8->setVisible(false);

	auto secuencia18 = Sequence::create(DelayTime::create(0.5f), CallFunc::create(CC_CALLBACK_0(Tutorial::changeTutorial9, this)), NULL);
	this->runAction(secuencia18);
}

void Tutorial::changeTutorial9(void) {
	tuto9->setVisible(true);
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("/music/notificacion_estado.mp3");
}


void Tutorial::playMusic(Ref *pSender) {
	/*if (!musicaWebster->isBackgroundMusicPlaying()) {
		musicaWebster->resumeBackgroundMusic();
	}
	else {
		musicaWebster->pauseBackgroundMusic();
	}*/
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
	_cursorSprite2->setPosition(e->getCursorX() + 16, e->getCursorY() - 16);
	_cursorSprite->setPosition(_cursorSprite2->getPosition().x - 14, _cursorSprite2->getPosition().y + 14);
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
	if(tuto5->isVisible() && virus1->enPapelera){
		papeleraSprite->setColor(ccc3(255, 0, 0));
		animFuego->setVisible(true);
		auto secuencia = Sequence::create(DelayTime::create(1.0f), CallFunc::create(CC_CALLBACK_0(Tutorial::changeColor, this)), NULL);
		papeleraSprite->runAction(secuencia);

		for (const auto& virus : allVirus)
		{
			if (virus->enPapelera && !virus->muerto)
			{
				virus->muerto = true;
				Dosis->setString("0");
				auto secuencia11 = Sequence::create(DelayTime::create(0.0f), CallFunc::create(CC_CALLBACK_0(Tutorial::wait5, this)), NULL);
				this->runAction(secuencia11);
			}
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
	if (virus1->imagen->isVisible() && bool_aux) {
		auto secuencia5 = Sequence::create(DelayTime::create(0.0f), CallFunc::create(CC_CALLBACK_0(Tutorial::wait2, this)), NULL);
		this->runAction(secuencia5);
		bool_aux = false;
	}

	if (mail->contenido.at(2)->isVisible() && bool_aux2) {
		auto secuencia13 = Sequence::create(DelayTime::create(3.0f), CallFunc::create(CC_CALLBACK_0(Tutorial::wait6, this)), NULL);
		this->runAction(secuencia13);
		bool_aux2 = false;
	}

	if (tuto6->isVisible()) {
		//Habilitar botones
		falso3->setVisible(false);
		carpeta4->imagen->setVisible(true);
		falso4->setVisible(false);
		musica->setVisible(true);
		falso5->setVisible(false);
		pensamientos->imagen->setVisible(true);
		falso6->setVisible(false);
		mail->imagen->setVisible(true);
		falso7->setVisible(false);
		noticias->imagen->setVisible(true);
	}

	if (tuto9->isVisible()) {
		falso2->setVisible(false);
		carpeta3->imagen->setVisible(true);
		if(carpeta3->contenido.at(0)->isVisible())
			pasarNivel->setVisible(true);
		else
			pasarNivel->setVisible(false);
	}

	if (tuto7->isVisible()) {
		falso1->setVisible(false);
		carpeta1->imagen->setVisible(true);
	}

	if (carpeta1->contenido.at(1)->isVisible() && bool_aux3) {
		auto secuencia15 = Sequence::create(DelayTime::create(1.5f), CallFunc::create(CC_CALLBACK_0(Tutorial::wait7, this)), NULL);
		this->runAction(secuencia15);
		bool_aux3 = false;
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

	if (carpeta1->validoEscaneado == 1 && bool_aux4) {
		Checked1->setVisible(true);
		auto secuencia17 = Sequence::create(DelayTime::create(5.0f), CallFunc::create(CC_CALLBACK_0(Tutorial::wait8, this)), NULL);
		this->runAction(secuencia17);
		bool_aux4 = false;
	}

	if (carpeta2->abierta->isVisible()) {
		virus1->iniciado = true;
		Alarma->setVisible(false);
	}

	if (virusElegido != nullptr) {
		virusElegido->imagen->setPosition(_cursorSprite->getPosition().x, _cursorSprite->getPosition().y);
	}

	if (virus1->enPapelera && tuto4->isVisible()) {
		auto secuencia9 = Sequence::create(DelayTime::create(0.0f), CallFunc::create(CC_CALLBACK_0(Tutorial::wait4, this)), NULL);
		this->runAction(secuencia9);
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

void Tutorial::terminarNivel(Ref *pSender) {
	PauseScene::TutorialPantalla = 1;
	auto scene = Alice::createScene();
	Director::getInstance()->pushScene(scene);
	auto scene2 = AnimacionScene::createScene();
	Director::getInstance()->pushScene(scene2);
}