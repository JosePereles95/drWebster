#include "Virus.h"
#include "Carpeta.h"

USING_NS_CC;

Virus::Virus(Vector<Carpeta*> folders, int id)
{
	spritebatch = SpriteBatchNode::create("Virus_sheet.png");
	SpriteFrameCache* cache = SpriteFrameCache::getInstance();
	cache->addSpriteFramesWithFile("Virus_sheet.plist");

	animVirus = Sprite::createWithSpriteFrameName("Virus01.png");
	spritebatch->addChild(animVirus, 3);

	animVirus->setVisible(false);

	Vector<SpriteFrame*> animFrames(3);

	char str[100] = { 0 };
	for (int i = 1; i < 3; i++)
	{
		sprintf(str, "Virus%02d.png", i);
		SpriteFrame* frame = cache->getSpriteFrameByName(str);
		animFrames.pushBack(frame);
	}

	Animation* animation = Animation::createWithSpriteFrames(animFrames, 0.1f);
	animVirus->runAction(RepeatForever::create(Animate::create(animation)));

	imagenAturdido = Sprite::create("VirusAturdido.png");

	imagen = MenuItemImage::create("virus.png", "virus.png",
		CC_CALLBACK_1(Virus::aturdir, this));

	boton = Menu::create(imagen, NULL);
	boton->setPosition(Vec2::ZERO);

	listaAtaque = folders;
	identificador = id;

	tam = listaAtaque.size();
	carpetaObjetivo = listaAtaque.at(random(0, tam-1));
	aturdido = false;
	imagen->setVisible(false);
	imagenAturdido->setVisible(false);
	iniciado = false;
	continua = true;
	reciclado = false;
	mordedura = false;
	enPapelera = false;
	muerto = false;
	ataque = 1;
}

void Virus::aturdir(Ref* pSender)
{
	if (!aturdido) {
		imagen->stopAction(moverse);
		aturdido = true;
		animVirus->setVisible(false);
		imagenAturdido->setVisible(true);
		auto secuencia1 = Sequence::create(DelayTime::create(3.0f), CallFunc::create(CC_CALLBACK_0(Virus::cambiar, this)), NULL);
		imagen->runAction(secuencia1);
	}
}

void Virus::cambiar(void)
{
	if (imagenAturdido->isVisible()) {
		imagen->stopAction(moverse);
		aturdido = false;
		imagenAturdido->setVisible(false);
		animVirus->setVisible(true);
		moverse = MoveTo::create(3 / 1.5, carpetaObjetivo->abierta->getPosition());
		imagen->runAction(moverse);
	}
}

void Virus::movimiento(void)
{
	animVirus->setPosition(imagen->getPosition().x, imagen->getPosition().y);
	imagenAturdido->setPosition(imagen->getPosition().x, imagen->getPosition().y);

	if (iniciado && continua) 
	{
		animVirus->setVisible(true);
		imagen->setVisible(true);
		moverse = MoveTo::create(3, carpetaObjetivo->abierta->getPosition());
		imagen->runAction(moverse);
		continua = false;
	}

	virusRect = imagen->getBoundingBox();
	carpetaRect = carpetaObjetivo->imagen->getBoundingBox();

	if (virusRect.intersectsRect(carpetaRect) && !mordedura)
	{
		auto secuencia3 = Sequence::create(DelayTime::create(1.0f), CallFunc::create(CC_CALLBACK_0(Virus::morder, this)), NULL);
		imagen->runAction(secuencia3);
		carpetaObjetivo->imagen->setColor(ccc3(255, 0, 0));
		carpetaObjetivo->abierta->setColor(ccc3(255, 0, 0));
		mordedura = true;
	}

	if (carpetaObjetivo->vida <= 0) {
		carpetaObjetivo->eliminaCarpeta();
		while (carpetaObjetivo->vida <= 0)
		{
			carpetaObjetivo = listaAtaque.at(random(0, tam - 1));
			continua = true;
		}
	}
}

void Virus::morder(void)
{
	carpetaObjetivo->vida -= ataque;
	carpetaObjetivo->imagen->setColor(ccc3(255, 255, 255));
	carpetaObjetivo->abierta->setColor(ccc3(255, 2550, 255));
	mordedura = false;}

void Virus::reciclar(void)
{
	imagen->stopAction(moverse);
	animVirus->setVisible(false);
	imagen->setVisible(false);
	imagenAturdido->setVisible(false);
	this->enPapelera = true;
	auto secuencia2 = Sequence::create(DelayTime::create(7.0f), CallFunc::create(CC_CALLBACK_0(Virus::reanimar, this)), NULL);
	imagen->runAction(secuencia2);
	CCLOG("llega no mas");
}

void Virus::reanimar(void)
{
	continua = true;
	this->enPapelera = false;
}