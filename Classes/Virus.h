#ifndef __VIRUS_H__
#define __VIRUS_H__

#include "cocos2d.h"
#include "Carpeta.h"

USING_NS_CC;

class Virus : public cocos2d::Object
{
public:
	Virus(Vector<Carpeta*>);

	MenuItemImage* imagen;
	Menu* boton;
	
	Vector<Carpeta*> listaAtaque;
	Carpeta* carpetaObjetivo;

	bool aturdido;
	bool destruido;
	bool llegado;
	MoveTo* moverse;

	int tiempoPapelera;
	bool enPapelera;

	float velocidad;

	void aturdir(Ref* pSender);
	void movimiento(void);
};

#endif // __VIRUS_H__