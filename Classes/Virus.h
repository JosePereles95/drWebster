#ifndef __VIRUS_H__
#define __VIRUS_H__

#include "cocos2d.h"
#include "Carpeta.h"

USING_NS_CC;

class Virus : public cocos2d::Object
{
public:
	Virus(Vector<Carpeta*>, int);

	MenuItemImage* imagen;
	Menu* boton;
	
	Vector<Carpeta*> listaAtaque;
	Carpeta* carpetaObjetivo;

	bool aturdido;
	bool destruido;
	bool iniciado;
	bool reciclado;
	bool continua;

	MoveTo* moverse;

	int tiempoPapelera;
	bool enPapelera;
	
	int identificador;

	float velocidad;

	void aturdir(Ref* pSender);
	void movimiento(void);
	void cambiar(void);

	void reciclar(void);
	void reanimar(void);
};

#endif // __VIRUS_H__