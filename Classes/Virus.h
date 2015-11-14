#ifndef __VIRUS_H__
#define __VIRUS_H__

#include "cocos2d.h"
#include "Carpeta.h"

USING_NS_CC;

class Virus
{
public:
	Virus(Vector<Carpeta*>);

	MenuItemImage* imagen;
	Menu* boton;
	
	Vector<Carpeta*> listaAtaque;
	Carpeta* carpetaObjetivo;

	bool aturdido;
	bool destruido;

	int tiempoPapelera;
	bool enPapelera;

	float velocidad;

	void aturdir(void);
	void movimiento(void);
};

#endif // __VIRUS_H__