#include "Virus.h"
#include "Carpeta.h"
#include "Alice.h"
#include "Tutorial.h"

USING_NS_CC;

Virus::Virus(Vector<Carpeta*> folders, int id, int tipo)
{
	tipoVirus = tipo;

	if (tipoVirus == 1)
	{
		spritebatch = SpriteBatchNode::create("Virus_sheet.png");
		SpriteFrameCache* cache = SpriteFrameCache::getInstance();
		cache->addSpriteFramesWithFile("Virus_sheet.plist");

		animVirus = Sprite::createWithSpriteFrameName("Virus01.png");
		spritebatch->addChild(animVirus, 5);

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
	}

	else if (tipoVirus == 2)
	{
		spritebatch = SpriteBatchNode::create("VirusCuernos_sheet.png");
		SpriteFrameCache* cache = SpriteFrameCache::getInstance();
		cache->addSpriteFramesWithFile("VirusCuernos_sheet.plist");

		animVirus = Sprite::createWithSpriteFrameName("VirusCuernos01.png");
		spritebatch->addChild(animVirus, 5);

		animVirus->setVisible(false);

		Vector<SpriteFrame*> animFrames(3);

		char str[100] = { 0 };
		for (int i = 1; i < 3; i++)
		{
			sprintf(str, "VirusCuernos%02d.png", i);
			SpriteFrame* frame = cache->getSpriteFrameByName(str);
			animFrames.pushBack(frame);
		}

		Animation* animation = Animation::createWithSpriteFrames(animFrames, 0.1f);
		animVirus->runAction(RepeatForever::create(Animate::create(animation)));

		imagenAturdido = Sprite::create("VirusCuernosAturdido.png");

		imagen = MenuItemImage::create("virusCuernos.png", "virusCuernos.png",
			CC_CALLBACK_1(Virus::aturdir, this));
	}
	else if (tipoVirus == 3)
	{
		spritebatch = SpriteBatchNode::create("VirusMadre_sheet.png");
		SpriteFrameCache* cache = SpriteFrameCache::getInstance();
		cache->addSpriteFramesWithFile("VirusMadre_sheet.plist");

		animVirus = Sprite::createWithSpriteFrameName("VirusMadre01.png");
		spritebatch->addChild(animVirus, 5);

		animVirus->setVisible(false);

		Vector<SpriteFrame*> animFrames(3);

		char str[100] = { 0 };
		for (int i = 1; i < 3; i++)
		{
			sprintf(str, "VirusMadre%02d.png", i);
			SpriteFrame* frame = cache->getSpriteFrameByName(str);
			animFrames.pushBack(frame);
		}

		Animation* animation = Animation::createWithSpriteFrames(animFrames, 0.1f);
		animVirus->runAction(RepeatForever::create(Animate::create(animation)));

		imagenAturdido = Sprite::create("VirusMadreAturdido.png");

		imagen = MenuItemImage::create("virusCuernos.png", "virusCuernos.png", //Mismo png (tamaño) que Cuernos
			CC_CALLBACK_1(Virus::aturdir, this));
	}

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
	if (tipoVirus == 1)
		ataque = 1;
	else if (tipoVirus == 2)
		ataque = 2;
	else if (tipoVirus == 3)
		ataque = 0;
}

void Virus::aturdir(Ref* pSender)
{
	if (!aturdido) {
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("/music/aturde2.mp3");
		imagen->stopAction(moverse);
		aturdido = true;
		animVirus->setVisible(false);
		imagenAturdido->setVisible(true);
		imagenAturdido->setColor(ccc3(230, 0, 0));
		auto secuencia = Sequence::create(DelayTime::create(0.5f), CallFunc::create(CC_CALLBACK_0(Virus::cambiaColor, this)), NULL);
		imagenAturdido->runAction(secuencia);
		if(tipoVirus == 1 || tipoVirus == 3)
			secuencia1 = Sequence::create(DelayTime::create(4.0f), CallFunc::create(CC_CALLBACK_0(Virus::cambiar, this)), NULL);
		if(tipoVirus == 2)
			secuencia1 = Sequence::create(DelayTime::create(6.0f), CallFunc::create(CC_CALLBACK_0(Virus::cambiar, this)), NULL);
		imagen->runAction(secuencia1);
	}
}

void Virus::cambiaColor(void)
{
	imagenAturdido->setColor(ccc3(255, 255, 255));
}

void Virus::cambiar(void)
{
	if (imagenAturdido->isVisible()) {
		imagen->stopAction(moverse);
		aturdido = false;
		imagenAturdido->setVisible(false);
		animVirus->setVisible(true);
		if (tipoVirus == 1 || tipoVirus == 3)
			moverse = MoveTo::create(6, carpetaObjetivo->abierta->getPosition());
		if (tipoVirus == 2)
			moverse = MoveTo::create(8, carpetaObjetivo->abierta->getPosition());
		imagen->runAction(moverse);
	}
}

void Virus::movimiento(void)
{
	animVirus->setPosition(imagen->getPosition().x, imagen->getPosition().y);
	imagenAturdido->setPosition(imagen->getPosition().x, imagen->getPosition().y);

	if (iniciado && continua) 
	{
		continua = false;
		animVirus->setVisible(true);
		imagen->setVisible(true);
		if(tipoVirus == 1 || tipoVirus == 3)
			moverse = MoveTo::create(5, carpetaObjetivo->abierta->getPosition());
		if(tipoVirus == 2)
			moverse = MoveTo::create(7, carpetaObjetivo->abierta->getPosition());
		imagen->runAction(moverse);
		
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
	aturdido = false;
}