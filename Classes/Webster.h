#ifndef __Webster_H__
#define __Webster_H__

#include "cocos2d.h"
#include "Carpeta.h"
#include "Virus.h"

USING_NS_CC;

class Webster : public cocos2d::Layer
{
public:
	Sprite* arch1_1;
	Sprite* arch1_2;
	Sprite* arch1_3;
	Sprite* arch1_4;
	int posXarchs1;
	int posYarchs1;

	Sprite* arch2_1;
	Sprite* arch2_2;
	Sprite* arch2_3;
	Sprite* arch2_4;
	int posXarchs2;
	int posYarchs2;

	Sprite* noChecked1;
	Sprite* Checked1;
	Sprite* noChecked2;
	Sprite* Checked2;

	Vector<Sprite*> archivos1;
	Vector<Sprite*> archivos2;

	Carpeta* carpeta1;
	Carpeta* carpeta2;
	
	Virus* virus1;
	Virus* virus2;

	Vector<Carpeta*> allCarpetas;

	Vector<Virus*> allVirus;
	Virus* virusElegido;
	Rect cursorRect;
	Rect virusRect;
	Rect papeleraRect;
	Rect carpRect;
	
	Carpeta* carpetaElegida;


	
	Sprite* _cursorSprite;
	Sprite* papeleraSprite;

	void onMouseMove(Event *event);
	void onMouseUp(Event *event);
	void onMouseDown(Event *event);
	void onMouseScroll(Event *event);

	static cocos2d::Scene* createScene();

	virtual bool init();

	void escaneando(void);
	void goToPauseScene(Ref *pSender);
	void changeColor(void);

	/*
	int validosEscaneados;
	int validosTotales;
	Label* archivosEncontrados;
	*/

	//void clickado(Event*);

	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);

	void update(float dt);

	// implement the "static create()" method manually
	CREATE_FUNC(Webster);
};
#endif // __Webster_H__