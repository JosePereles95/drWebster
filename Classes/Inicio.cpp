#include "Inicio.h"
#include "Tutorial.h"
#include "Webster.h"
#include "Alice.h"


USING_NS_CC;

Scene* Inicio::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = Inicio::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool Inicio::init()
{
	//////////////////////////////GameScreen
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();



	//Label
	carga = 0;
	cargando = Label::createWithSystemFont("hello", "Arial.ttf", 100);
	std::string letra = std::to_string(carga);
	cargando->setString(letra + "%");
	cargando->setColor(Color3B(255, 255, 255));
	cargando->setPosition(Point((visibleSize.width / 2),
		(visibleSize.height / 2 + cargando->getContentSize().height)));
	addChild(cargando, 5);


	Logo = Sprite::create("Logo.png");
	Logo->setPosition(Point((visibleSize.width / 2),
		(visibleSize.height / 2)));

	addChild(Logo, 1);


	titulo = Sprite::create("MadeBy.png");
	titulo->setPosition(Point((visibleSize.width / 2),
		(visibleSize.height / 2)));

	addChild(titulo, 1);
	background = Sprite::create("FondoCargando.png");
	background->setPosition(Point((visibleSize.width / 2 + 10),
		(visibleSize.height / 2)));
	addChild(background, 0);

	background2 = Sprite::create("FondoInicio.png");
	background2->setPosition(Point((visibleSize.width / 2),
		(visibleSize.height / 2)));
	addChild(background2, 0);


	//FadeIn
	cargando01 = Sprite::create("Cargando01.png");
	cargando01->setPosition(Point((visibleSize.width / 2),
		(visibleSize.height / 2)));
	addChild(cargando01, 2);

	cargandomover = Sprite::create("CargandoMover.png");
	cargandomover->setPosition(Point((visibleSize.width / 2),
		(visibleSize.height / 2)));
	addChild(cargandomover, 3);

	cargando02 = Sprite::create("Cargando02.png");
	cargando02->setPosition(Point((visibleSize.width / 2),
		(visibleSize.height / 2)));
	addChild(cargando02, 4);

	Dr = Sprite::create("titulo.png");
	Dr->setPosition(Point((visibleSize.width / 2),
		(visibleSize.height / 2 + 20)));
	addChild(Dr, 2);
	//Cargar sonidos
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("/music/Inicio.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("/music/inicio2.mp3");

	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("/music/Inicio.mp3");
	auto secuencia1 = Sequence::create(DelayTime::create(3.0f), CallFunc::create(CC_CALLBACK_0(Inicio::Mover, this)), NULL);
	this->runAction(secuencia1);
	for (int i = 0; i < 100; i++)
	{
		float delay = (3.00 + (0.077*i));
		auto action = Sequence::create(DelayTime::create(delay), CallFunc::create(CC_CALLBACK_0(Inicio::Cargar, this)), NULL);
		this->runAction(action);
	}
	Dr->setOpacity(0);
	titulo->setOpacity(0);
	Logo->setOpacity(0);
	background2->setOpacity(0);
	

	auto secuencia2 = Sequence::create(DelayTime::create(12.0f), CallFunc::create(CC_CALLBACK_0(Inicio::changeOpacity0, this)), NULL);
	this->runAction(secuencia2);
	auto secuencia3 = Sequence::create(DelayTime::create(15.0f), CallFunc::create(CC_CALLBACK_0(Inicio::changeOpacity1, this)), NULL);
	this->runAction(secuencia3);
	auto secuencia4 = Sequence::create(DelayTime::create(18.0f), CallFunc::create(CC_CALLBACK_0(Inicio::changeOpacity2, this)), NULL);
	this->runAction(secuencia4);
	auto secuencia5 = Sequence::create(DelayTime::create(21.0f), CallFunc::create(CC_CALLBACK_0(Inicio::changeOpacity3, this)), NULL);
	this->runAction(secuencia5);
	auto secuencia6 = Sequence::create(DelayTime::create(25.0f), CallFunc::create(CC_CALLBACK_0(Inicio::changeOpacity4, this)), NULL);
	this->runAction(secuencia6);
	auto secuencia7 = Sequence::create(DelayTime::create(28.0f), CallFunc::create(CC_CALLBACK_0(Inicio::cambiarpantalla, this)), NULL);
	this->runAction(secuencia7);


}
void Inicio::Mover(void)
{
	auto vect = cargando01->getPosition();
	vect.x += 800;
	auto moverse = MoveTo::create(8, vect);
	cargandomover->runAction(moverse);
}
void Inicio::resumeGameScreen(Ref *pSender) {
	auto scene = Tutorial::createScene();
	Director::getInstance()->pushScene(scene);
}

void Inicio::changeOpacity0(void)
{
	auto action3 = FadeOut::create(3);
	auto action4 = FadeOut::create(3);
	auto action5 = FadeOut::create(3);
	auto action6 = FadeOut::create(3);
	auto action7 = FadeOut::create(3);
	cargando01->runAction(action3);
	cargando02->runAction(action4);
	background->runAction(action5);
	cargandomover->runAction(action6);
	cargando->runAction(action7);
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("/music/inicio2.mp3");
}
void Inicio::changeOpacity1(void)
{
	auto action3 = FadeIn::create(3);
	auto action4 = FadeIn::create(3);
	auto action5 = FadeIn::create(3);
	titulo->runAction(action3);
	Logo->runAction(action4);
	background2->runAction(action5);
}
void Inicio::changeOpacity2(void)
{
	auto action3 = FadeOut::create(3);
	auto action4 = FadeOut::create(3);
	titulo->runAction(action3);
	Logo->runAction(action4);
}
void Inicio::changeOpacity3(void)
{
	auto action3 = FadeIn::create(3);
	Dr->runAction(action3);
}
void Inicio::changeOpacity4(void)
{
	auto action3 = FadeOut::create(3);
	Dr->runAction(action3);
}
void Inicio::cambiarpantalla(void)
{
	resumeGameScreen(this);
}
void Inicio::Cargar()
{
	carga++;
	std::string letra = std::to_string(carga);
	cargando->setString(letra + "%");
}

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
exit(0);
#endif