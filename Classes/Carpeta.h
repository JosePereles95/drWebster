#ifndef __CARPETA_H__
#define __CARPETA_H__

#include "cocos2d.h"

USING_NS_CC;

class Carpeta
{
public:
	Carpeta::Carpeta(Vector<Sprite*>, int);

	MenuItemImage* imagen;
	MenuItemImage* pasar;
	MenuItemImage* escanear;

	Menu* botones;
	//Menu* botonNext;

	int elegido;
	int archivoValido;
	Vector<Sprite*> contenido;
	Sprite* abierta;
	int validoEscaneado;
	//CCSprite* abierta;
	//CCSprite* cerrada;

	void abreCierraCarpeta(cocos2d::Ref* pSender);

	void eliminaCarpeta(void);

	void pasaSiguiente(Ref* pSender);

	void escanearArchivo(Ref* pSender);
};

#endif // __CARPETA_H__