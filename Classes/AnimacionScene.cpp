#include "PauseScene.h"
#include "Tutorial.h"
#include "AnimacionScene.h"

USING_NS_CC;

Scene* AnimacionScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = AnimacionScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool AnimacionScene::init()
{
	//////////////////////////////GameScreen
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//FadeIn
	cargando01 = Sprite::create("Cargando01Anim.png");
	cargando01->setPosition(Point((visibleSize.width / 4),
		(visibleSize.height / 4)));
	addChild(cargando01, 2);

	cargandomover = Sprite::create("CargandoMoverAnim.png");
	cargandomover->setPosition(Point((visibleSize.width / 4),
		(visibleSize.height / 4)));
	addChild(cargandomover, 3);

	pantalla = Sprite::create("PausaNinaFondo.png");
	pantalla->setPosition(Point((visibleSize.width / 2),
		(visibleSize.height / 2)));
	addChild(pantalla, 1);

	cargando02 = Sprite::create("Cargando02Anim.png");
	cargando02->setPosition(Point((visibleSize.width / 4),
		(visibleSize.height / 4)));
	addChild(cargando02, 4);

	//Enchufes
	V1 = Sprite::create("V1.png");
	V1->setPosition(Point((visibleSize.width / 2 - V1->getContentSize().width + 35),
		(visibleSize.height)));
	addChild(V1, 6);
	V1Final = Sprite::create("V1Final.png");
	V1Final->setPosition(V1->getPosition());
	V1Final->setVisible(false);
	addChild(V1Final, 6);

	//Barra
	//Label
	carga = 0;
	cargando = Label::createWithSystemFont("hello", "Arial.ttf", 50);
	std::string letra = std::to_string(carga);
	cargando->setString(letra + "%");
	cargando->setColor(Color3B(255, 255, 255));
	cargando->setPosition(Point((visibleSize.width / 2 - cargando->getContentSize().width*4.5),
		(visibleSize.height / 3)));
	addChild(cargando, 5);

	//Sonido
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("/music/inicio2.mp3");

	auto secuencia0 = Sequence::create(DelayTime::create(6.0f), CallFunc::create(CC_CALLBACK_0(AnimacionScene::Mover2, this)), NULL);
	this->runAction(secuencia0);

	for (int i = 0; i < 100; i++)
	{
		float delay = (6.00 + (0.035*i));
		auto action = Sequence::create(DelayTime::create(delay), CallFunc::create(CC_CALLBACK_0(AnimacionScene::Cargar, this)), NULL);
		this->runAction(action);
	}

	auto background = Sprite::create("PausaNina.png");
	background->setPosition(Point((visibleSize.width / 2),
		(visibleSize.height / 2)));
	addChild(background, 4);

	Tran = Sprite::create("Tran.png");
	Tran->setPosition(Point((visibleSize.width / 2),
		(visibleSize.height / 2)));
	Tran->setOpacity(0);
	addChild(Tran, 6);

	auto secuencia1 = Sequence::create(DelayTime::create(2.0f), CallFunc::create(CC_CALLBACK_0(AnimacionScene::Mover, this)), NULL);
	this->runAction(secuencia1);
	auto secuencia2 = Sequence::create(DelayTime::create(4.0f), CallFunc::create(CC_CALLBACK_0(AnimacionScene::Cambio, this)), NULL);
	this->runAction(secuencia2);
	auto secuencia3 = Sequence::create(DelayTime::create(11.5f), CallFunc::create(CC_CALLBACK_0(AnimacionScene::Imagen1, this)), NULL);
	this->runAction(secuencia3);
	auto secuencia5 = Sequence::create(DelayTime::create(16.5f), CallFunc::create(CC_CALLBACK_0(AnimacionScene::Pasar, this)), NULL);
	this->runAction(secuencia5);

	return true;
}

void AnimacionScene::resumeGameScreen(Ref *pSender) {
	Director::getInstance()->popScene();
}

void AnimacionScene::Mover()
{
	auto vect = V1->getPosition();
	vect.y -= 370;
	auto moverse = MoveTo::create(4, vect);
	V1->runAction(moverse);

}

void AnimacionScene::Cambio()
{
	V1Final->setPosition(V1->getPosition());
	V1->setVisible(false);
	V1Final->setVisible(true);
}

void AnimacionScene::Pasar()
{
	resumeGameScreen(this);
}

void AnimacionScene::Cargar()
{
	carga++;
	std::string letra = std::to_string(carga);
	cargando->setString(letra + "%");
}

void AnimacionScene::Mover2(void)
{
	auto vect = cargando01->getPosition();
	vect.x += 800;
	auto moverse = MoveTo::create(8, vect);
	cargandomover->runAction(moverse);
}

void AnimacionScene::Imagen1(void)
{
	auto action = FadeIn::create(3);
	Tran->runAction(action);
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("/music/inicio2.mp3");
}

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
exit(0);
#endif