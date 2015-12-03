#ifndef __VIRUS_H__
#define __VIRUS_H__

#include "cocos2d.h"
#include "Carpeta.h"

USING_NS_CC;

class Virus : public cocos2d::Object
{
public:
	Virus(Vector<Carpeta*>, int, int);

	int tipoVirus;

	MenuItemImage* imagen;
	Menu* boton;
	
	Rect virusRect;
	Rect carpetaRect;
	Sequence* secuencia1;

	Sprite* animVirus;
	SpriteBatchNode* spritebatch;
	Sprite* imagenAturdido;
	
	Vector<Carpeta*> listaAtaque;
	Carpeta* carpetaObjetivo;

	int tam;
	int ataque;

	bool aturdido;
	bool destruido;
	bool iniciado;
	bool reciclado;
	bool continua;
	bool mordedura;
	bool muerto;

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
	void morder(void);
};

#endif // __VIRUS_H__