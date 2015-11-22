#include "Virus.h"
#include "Carpeta.h"

USING_NS_CC;

Virus::Virus(Vector<Carpeta*> folders, int id)
{
	imagen = MenuItemImage::create("virus.png", "virus.png",
		CC_CALLBACK_1(Virus::aturdir, this));

	boton = Menu::create(imagen, NULL);
	boton->setPosition(Vec2::ZERO);

	listaAtaque = folders;
	identificador = id;

	int tam = listaAtaque.size();
	carpetaObjetivo = listaAtaque.at(random(0, tam-1));
	aturdido = false;
	imagen->setVisible(false);
	iniciado = false;
	continua = true;
	reciclado = false;
}

void Virus::aturdir(Ref* pSender)
{
	if (!aturdido) {
		imagen->stopAction(moverse);
		aturdido = true;
		auto secuencia1 = Sequence::create(DelayTime::create(3.0f), CallFunc::create(CC_CALLBACK_0(Virus::cambiar, this)), NULL);
		imagen->runAction(secuencia1);
	}
}

void Virus::cambiar(void)
{
	if (imagen->isVisible()) {
		imagen->stopAction(moverse);
		aturdido = false;
		moverse = MoveTo::create(3 / 1.5, carpetaObjetivo->abierta->getPosition());
		imagen->runAction(moverse);
	}
}

void Virus::movimiento(void)
{
	if (iniciado && continua) 
	{
		imagen->setVisible(true);
		moverse = MoveTo::create(3, carpetaObjetivo->abierta->getPosition());
		imagen->runAction(moverse);
		continua = false;
	}
}

void Virus::reciclar(void)
{
	imagen->stopAction(moverse);
	imagen->setVisible(false);
	auto secuencia2 = Sequence::create(DelayTime::create(7.0f), CallFunc::create(CC_CALLBACK_0(Virus::reanimar, this)), NULL);
	imagen->runAction(secuencia2);
	CCLOG("llega no mas");
}

void Virus::reanimar(void)
{
	continua = true;
}