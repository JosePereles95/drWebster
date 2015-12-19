#ifndef __ANIMCAIONSCENE_H__
#define __ANIMCAIONSCENE_H__

#include "cocos2d.h"

class AnimacionScene : public cocos2d::Layer
{
public:
	//Barra
	Label* cargando;
	int carga;


	Sprite* V1;
	Sprite* V1Final;
	Sprite* cargando01;
	Sprite* cargando02;
	Sprite* cargandomover;
	Sprite* pantalla;
	Sprite* Tran;

	void resumeGameScreen(Ref *pSender);

	static cocos2d::Scene* createScene();


	void Mover(void);
	void Cambio(void);
	void Pasar(void);
	void Mover2(void);
	void Imagen1(void);

	void Cargar(void);

	virtual bool init();

	// implement the "static create()" method manually
	CREATE_FUNC(AnimacionScene);
};

#endif // __ANIMCAIONSCENE_H__
