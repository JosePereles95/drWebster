#ifndef __CARPETA_H__
#define __CARPETA_H__

#include "cocos2d.h"

USING_NS_CC;

class Carpeta
{
public:
	Carpeta::Carpeta(Sprite*);

	//int numero;
	//Sprite* _imagen;
	MenuItemImage* imagen;
	Sprite* contenido;
	Sprite* abierta;
	Menu* botonCarpeta;

	void abreCierraCarpeta(cocos2d::Ref* pSender);

	void eliminaCarpeta(void);
};

#endif // __CARPETA_H__