#include "Virus.h"
#include "Carpeta.h"

USING_NS_CC;

Virus::Virus(Vector<Carpeta*> folders)
{
	imagen = MenuItemImage::create("virus.png", "virus.png",
		CC_CALLBACK_1(Virus::aturdir, this));

	boton = Menu::create(imagen, NULL);
	boton->setPosition(Vec2::ZERO);

	listaAtaque = folders;
	int tam = listaAtaque.size();
	carpetaObjetivo = listaAtaque.at(random(0, tam-1));
	aturdido = false;
	imagen->setVisible(false);
	llegado = false;
}

void Virus::aturdir(Ref* pSender)
{
	if (!aturdido) {
		imagen->stopAction(moverse);
		aturdido = true;
	}
	else {
		/*moverse = MoveTo::create(3/2, carpetaObjetivo->abierta->getPosition());
		imagen->runAction(moverse);
		aturdido = false;*/

	}
}

void Virus::movimiento(void)
{
	if (imagen->isVisible() && !llegado) 
	{
		imagen->setVisible(true);
		moverse = MoveTo::create(3, carpetaObjetivo->abierta->getPosition());
		imagen->runAction(moverse);
		llegado = true;
	}
}