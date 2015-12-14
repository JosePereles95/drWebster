#ifndef __Inicio_H__
#define __Inicio_H__

#include "cocos2d.h"

USING_NS_CC;
class Inicio : public cocos2d::Layer
{
public:
	Label* cargando;
	int carga;

	int contador;
	Sprite* titulo;
	Sprite* background;
	Sprite*  background2;
	Sprite* Logo;
	Sprite* cargando01;
	Sprite* cargando02;
	Sprite* cargandomover;
	Sprite* Dr;
	void Mover(void);
	void Cargar(void);
	void resumeGameScreen(Ref *pSender);


	static cocos2d::Scene* createScene();
	virtual bool init();
	void changeOpacity0(void);
	void changeOpacity1(void);
	void changeOpacity2(void);
	void changeOpacity3(void);
	void changeOpacity4(void);
	void cambiarpantalla(void);

	// implement the "static create()" method manually
	CREATE_FUNC(Inicio);
};

#endif // __Inicio_H__