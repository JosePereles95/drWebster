#include "Carpeta.h"
#include "Webster.h"
#include "Tutorial.h"
#include "Alice.h"


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
			CC_CALLBACK_1(Carpeta::abreCarpeta, this));
	}
	else if (tipo == 2) { // Musica
		imagen = MenuItemImage::create("musica.png", "musica.png",
			CC_CALLBACK_1(Carpeta::abreCarpeta, this));
	}
	else if (tipo == 3) { // Correo
		imagen = MenuItemImage::create("mail.png", "mail.png",
			CC_CALLBACK_1(Carpeta::abreCarpeta, this));
	}
	else if (tipo == 4) { // Estado
		imagen = MenuItemImage::create("estado.png", "estado.png",
			CC_CALLBACK_1(Carpeta::abreCarpeta, this));
	}
	else if (tipo == 5) { // Pensamiento
		imagen = MenuItemImage::create("pensamientos.png", "pensamientos.png",
			CC_CALLBACK_1(Carpeta::abreCarpeta, this));
	}
	else if (tipo == 6) { // Noticias
		imagen = MenuItemImage::create("News2.png", "News2.png",
			CC_CALLBACK_1(Carpeta::abreCarpeta, this));
	}

	pasar = MenuItemImage::create("flecha.png", "flecha1.png",
		CC_CALLBACK_1(Carpeta::pasaSiguiente, this));
	escanear = MenuItemImage::create("scan.png", "scan1.png",
		CC_CALLBACK_1(Carpeta::escanearArchivo, this));
	cerrar = MenuItemImage::create("cerrar.png", "cerrar1.png",
		CC_CALLBACK_1(Carpeta::cierraCarpeta, this));

	botones = Menu::create(imagen, pasar, escanear, cerrar, NULL);
	botones->setPosition(Vec2::ZERO);
	
	
	for (int i = 0; i < contenido.size(); i++)
		contenido.at(i)->setVisible(false);

	if (tipo == 1)
		abierta = Sprite::create("carpeta2.png");
	else if (tipo == 2)
		abierta = Sprite::create("musica.png");
	else if (tipo == 3)
		abierta = Sprite::create("mail1.png");
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
	cerrar->setVisible(false);
	validoEscaneado = 0;
	vida = 10;
	tiempoEscanear = false;
}

void Carpeta::abreCarpeta(Ref* pSender)
{
	if (!contenido.at(elegido)->isVisible())
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("/music/abre1.mp3");
		contenido.at(elegido)->setVisible(true);
		abierta->setVisible(true);
		pasar->setVisible(true);
		escanear->setVisible(true);
		cerrar->setVisible(true);
	}
}

void Carpeta::cierraCarpeta(Ref* pSender)
{
		if(contenido.at(elegido)->isVisible())
		{
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("/music/cierra1.mp3");
			contenido.at(elegido)->setVisible(false);
			abierta->setVisible(false);
			pasar->setVisible(false);
			escanear->setVisible(false);
			cerrar->setVisible(false);
		}
}

void Carpeta::eliminaCarpeta(void)
{
	imagen->setVisible(false);
	abierta->setVisible(false);
	contenido.at(elegido)->setVisible(false);
	pasar->setVisible(false);
	escanear->setVisible(false);
	cerrar->setVisible(false);
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
		if (elegido == archivoValido && validoEscaneado != 1) {
			validoEscaneado++;
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("/music/acierto_escaneo.mp3");
		}
		else {
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("/music/fallo_escaneo.mp3");
		}

		tiempoEscanear = false;
	}
}