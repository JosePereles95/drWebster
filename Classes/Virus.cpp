#include "Virus.h"
#include "Carpeta.h"

USING_NS_CC;

Virus::Virus(Vector<Carpeta*> folders)
{
	imagen = MenuItemImage::create("virus.png", "virus.png",
		CC_CALLBACK_1(Virus::aturdir, this));

	boton = Menu::create(imagen, NULL);
	boton->setPosition(Vec2::ZERO);

	//listaAtaque = folders;
	//carpetaObjetivo = listaAtaque.at(0);
}

void Virus::aturdir(void)
{
	aturdido = true;
}

void Virus::movimiento(void) 
{
	if (!aturdido) 
	{
		
	}
}