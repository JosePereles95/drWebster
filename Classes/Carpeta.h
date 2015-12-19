#ifndef __CARPETA_H__
#define __CARPETA_H__

#include "cocos2d.h"

USING_NS_CC;

class Carpeta : public cocos2d::Object
{
public:
	Carpeta(void);
	Carpeta(Vector<Sprite*>, int, int);

	MenuItemImage* imagen;
	MenuItemImage* pasar;
	MenuItemImage* escanear;
	MenuItemImage* cerrar;

	Menu* botones;
	//Menu* botonNext;

	int elegido;
	int archivoValido;
	Vector<Sprite*> contenido;
	Sprite* abierta;
	int validoEscaneado;
	int vida;
	int tipo;
	bool tiempoEscanear;

	//CCSprite* abierta;
	//CCSprite* cerrada;

	void abreCarpeta(cocos2d::Ref* pSender);
	void cierraCarpeta(cocos2d::Ref* pSender);
	void eliminaCarpeta(void);
	void pasaSiguiente(Ref* pSender);
	void escanearArchivo(Ref* pSender);
};

#endif // __CARPETA_H__