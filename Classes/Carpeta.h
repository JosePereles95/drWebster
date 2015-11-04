#ifndef __CARPETA_H__
#define __CARPETA_H__

#include "cocos2d.h"

USING_NS_CC;

class Carpeta
{
public:
	Carpeta::Carpeta(Vector<Sprite*>);

	MenuItemImage* imagen;
	Menu* botones;

	MenuItemImage* pasar;
	//Menu* botonNext;

	int elegido;
	Vector<Sprite*> contenido;
	Sprite* abierta;
	//CCSprite* abierta;
	//CCSprite* cerrada;

	void abreCierraCarpeta(cocos2d::Ref* pSender);

	void eliminaCarpeta(void);

	void pasaSiguiente(Ref* pSender);
};

#endif // __CARPETA_H__