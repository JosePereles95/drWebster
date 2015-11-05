#include "Carpeta.h"
#include "Webster.h"

USING_NS_CC;

Carpeta::Carpeta(Vector<Sprite*> archivos)
{
	imagen = MenuItemImage::create("carpeta1.png", "carpeta1.png",
		CC_CALLBACK_1(Carpeta::abreCierraCarpeta, this));

	pasar = MenuItemImage::create("flecha.png", "flecha.png",
		CC_CALLBACK_1(Carpeta::pasaSiguiente, this));

	botones = Menu::create(imagen, pasar, NULL);
	botones->setPosition(Vec2::ZERO);
	
	contenido = archivos; //copia global
	//a
	//b
	//c
	//d

	for (int i = 0; i < contenido.size(); i++)
	{
		contenido.at(i)->setVisible(false);
	}

	abierta = Sprite::create("carpeta2.png");

	elegido = 0;
	abierta->setVisible(false);
	pasar->setVisible(false);
}

void Carpeta::abreCierraCarpeta(Ref* pSender)
{
	//abierta = Sprite::create("carpeta2.png");
	//cerrada = Sprite::create("carpeta1.png");

	if (!contenido.at(elegido)->isVisible())
	{
		contenido.at(elegido)->setVisible(true);
		abierta->setVisible(true);
		pasar->setVisible(true);
		//imagen->setNormalImage(abierta);
	}
	else
	{
		contenido.at(elegido)->setVisible(false);
		abierta->setVisible(false);
		pasar->setVisible(false);
		//imagen->setNormalImage(cerrada);
		//elegido = 0;
	}
}

void Carpeta::eliminaCarpeta(void)
{
}

void Carpeta::pasaSiguiente(Ref* pSender)
{
	if (abierta->isVisible())
	{
		contenido.at(elegido)->setVisible(false);
		if (elegido < contenido.size() - 1)
			elegido++;
		else
			elegido = 0;
		contenido.at(elegido)->setVisible(true);
	}
}