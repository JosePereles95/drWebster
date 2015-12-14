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
	//Pasar Param


	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();


	//Enchufes
	V1 = Sprite::create("V1.png");
	V1->setPosition(Point((visibleSize.width / 2 - V1->getContentSize().width+35),
		(visibleSize.height)));
	addChild(V1, 1);
	V1Final = Sprite::create("V1Final.png");
	V1Final->setPosition(V1->getPosition());
	V1Final->setVisible(false);
	addChild(V1Final, 1);


	auto background = Sprite::create("PausaNina.png");
	background->setPosition(Point((visibleSize.width / 2),
		(visibleSize.height / 2)));
	addChild(background, 0);

	auto secuencia1 = Sequence::create(DelayTime::create(2.0f), CallFunc::create(CC_CALLBACK_0(AnimacionScene::Mover, this)), NULL);
	this->runAction(secuencia1);
	auto secuencia2 = Sequence::create(DelayTime::create(4.0f), CallFunc::create(CC_CALLBACK_0(AnimacionScene::Cambio, this)), NULL);
	this->runAction(secuencia2);
	auto secuencia3 = Sequence::create(DelayTime::create(6.0f), CallFunc::create(CC_CALLBACK_0(AnimacionScene::Pasar, this)), NULL);
	this->runAction(secuencia3);
	

	return true;
}

void AnimacionScene::resumeGameScreen(Ref *pSender) {
	Director::getInstance()->popScene();
}

void AnimacionScene::Mover()
{
	auto vect = V1->getPosition();
	vect.y -= 390;
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

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
exit(0);
#endif

