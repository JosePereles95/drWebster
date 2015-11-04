#include "Carpeta.h"
#include "Webster.h"

USING_NS_CC;

Carpeta::Carpeta(Sprite *cont)
{
	imagen = MenuItemImage::create("carpeta1.png", "carpeta1.png",
		CC_CALLBACK_1(Carpeta::abreCierraCarpeta, this));

	botonCarpeta = Menu::create(imagen, NULL);
	botonCarpeta->setPosition(Vec2::ZERO);

	abierta = Sprite::create("carpeta2.png");

	contenido = cont;

	contenido->setVisible(false);
	abierta->setVisible(false);
}

void Carpeta::abreCierraCarpeta(Ref* pSender)
{
	if (!contenido->isVisible()) {
		contenido->setVisible(true);
		abierta->setVisible(true);
	}
	else {
		contenido->setVisible(false);
		abierta->setVisible(false);
	}
}

void Carpeta::eliminaCarpeta(void)
{
}


/*Carpeta::~Carpeta()
{

}*/