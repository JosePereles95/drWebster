#include "Carpeta.h"
#include "Webster.h"
#include "Tutorial.h"


USING_NS_CC;

Carpeta::Carpeta(void)
{

}

Carpeta::Carpeta(Vector<Sprite*> archivos, int valido, int t)
{
	contenido = archivos;
	archivoValido = valido;
	tipo = t;

	if (tipo == 1) { // Carpeta
		imagen = MenuItemImage::create("carpeta1.png", "carpeta1.png",
			CC_CALLBACK_1(Carpeta::abreCierraCarpeta, this));
		pasar = MenuItemImage::create("flecha.png", "flecha1.png",
			CC_CALLBACK_1(Carpeta::pasaSiguiente, this));
		escanear = MenuItemImage::create("scan.png", "scan1.png",
			CC_CALLBACK_1(Carpeta::escanearArchivo, this));
	}
	else if (tipo == 2) { // Musica
		imagen = MenuItemImage::create("musica.png", "musica.png",
			CC_CALLBACK_1(Carpeta::abreCierraCarpeta, this));
		pasar = MenuItemImage::create("flecha.png", "flecha1.png",
			CC_CALLBACK_1(Carpeta::pasaSiguiente, this));
		escanear = MenuItemImage::create("scan.png", "scan1.png",
			CC_CALLBACK_1(Carpeta::escanearArchivo, this));
	}
	else if (tipo == 3) { // Correo
		imagen = MenuItemImage::create("mail.png", "mail.png",
			CC_CALLBACK_1(Carpeta::abreCierraCarpeta, this));
		pasar = MenuItemImage::create("flechacorreo1.png", "flechacorreo2.png",
			CC_CALLBACK_1(Carpeta::pasaSiguiente, this));
		escanear = MenuItemImage::create("scancorreo1.png", "scancorreo2.png",
			CC_CALLBACK_1(Carpeta::escanearArchivo, this));
	}
	else if (tipo == 4) { // Estado
		imagen = MenuItemImage::create("estado.png", "estado.png",
			CC_CALLBACK_1(Carpeta::abreCierraCarpeta, this));
		pasar = MenuItemImage::create("flecha.png", "flecha1.png",
			CC_CALLBACK_1(Carpeta::pasaSiguiente, this));
		escanear = MenuItemImage::create("scan.png", "scan1.png",
			CC_CALLBACK_1(Carpeta::escanearArchivo, this));
	}
	else if (tipo == 5) { // Pensamiento
		imagen = MenuItemImage::create("pensamientos.png", "pensamientos.png",
			CC_CALLBACK_1(Carpeta::abreCierraCarpeta, this));
		pasar = MenuItemImage::create("flecha.png", "flecha1.png",
			CC_CALLBACK_1(Carpeta::pasaSiguiente, this));
		escanear = MenuItemImage::create("scan.png", "scan1.png",
			CC_CALLBACK_1(Carpeta::escanearArchivo, this));
	}
	else if (tipo == 6) { // Noticias
		imagen = MenuItemImage::create("News2.png", "News2.png",
			CC_CALLBACK_1(Carpeta::abreCierraCarpeta, this));
		pasar = MenuItemImage::create("flechanoticias1.png", "flechanoticias2.png",
			CC_CALLBACK_1(Carpeta::pasaSiguiente, this));
		escanear = MenuItemImage::create("scannoticias1.png", "scannoticias2.png",
			CC_CALLBACK_1(Carpeta::escanearArchivo, this));
	}

	botones = Menu::create(imagen, pasar, escanear, NULL);
	botones->setPosition(Vec2::ZERO);
	
	
	for (int i = 0; i < contenido.size(); i++)
		contenido.at(i)->setVisible(false);

	if (tipo == 1)
		abierta = Sprite::create("carpeta2.png");
	else if (tipo == 2)
		abierta = Sprite::create("musica.png");
	else if (tipo == 3)
		abierta = Sprite::create("mail.png");
	else if (tipo == 4)
		abierta = Sprite::create("estado.png");
	else if (tipo == 5)
		abierta = Sprite::create("pensamientos.png");
	else if (tipo == 6)
		abierta = Sprite::create("News2Abierta.png");

	elegido = 0;
	abierta->setVisible(false);
	pasar->setVisible(false);
	escanear->setVisible(false);
	validoEscaneado = 0;
	vida = 10;
	tiempoEscanear = false;
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
		escanear->setVisible(true);

		//imagen->setNormalImage(abierta);
	}
	else
	{
		contenido.at(elegido)->setVisible(false);
		abierta->setVisible(false);
		pasar->setVisible(false);
		escanear->setVisible(false);

		//imagen->setNormalImage(cerrada);
		//elegido = 0;
	}
}

void Carpeta::eliminaCarpeta(void)
{
	imagen->setVisible(false);
	abierta->setVisible(false);
	contenido.at(elegido)->setVisible(false);
	pasar->setVisible(false);
	escanear->setVisible(false);
}

void Carpeta::pasaSiguiente(Ref* pSender)
{
	if (abierta->isVisible())
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("/music/carpeta.mp3");
		contenido.at(elegido)->setVisible(false);
		if (elegido < contenido.size() - 1)
			elegido++;
		else
			elegido = 0;
		contenido.at(elegido)->setVisible(true);
	}
}

void Carpeta::escanearArchivo(Ref * pSender)
{
	if (tiempoEscanear) {
		if (elegido == archivoValido && validoEscaneado != 1)
			validoEscaneado++;
		tiempoEscanear = false;
	}
}