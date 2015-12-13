#ifndef __Tutorial_H__
#define __Tutorial_H__

#include "cocos2d.h"
#include "Carpeta.h"
#include "Virus.h"
#include "SimpleAudioEngine.h"  

USING_NS_CC;

class Tutorial : public cocos2d::Layer
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

	int posXChecked1;
	int posYChecked1;

	Vector<Sprite*> archivos1;
	Vector<Sprite*> archivos2;

	Carpeta* carpeta1;
	Carpeta* carpeta2;
	int posXCarpeta1;
	int posYCarpeta1;
	int posXCarpeta2;
	int posYCarpeta2;

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
	Sprite* interfazSprite;

	Sprite* cargando1;
	Sprite* animFuego;
	Sprite* tuto1;
	Sprite* barra;

	Carpeta* noticias;
	int posXNoticias;
	int posYNoticias;
	Sprite* archNews_1;
	Vector<Sprite*> allNoticias;
	int posXarchsNews;
	int posYarchsNews;

	Carpeta* mail;
	int posXMail;
	int posYMail;
	Sprite* archMail_1;
	Sprite* archMail_2;
	Sprite* archMail_3;
	Vector<Sprite*> allMails;
	int posXarchsMail;
	int posYarchsMail;

	Sprite* estado;

	CocosDenshion::SimpleAudioEngine* musicaWebster;

	Sequence* secuenciaEscaneo;

	void onMouseMove(Event *event);
	void onMouseUp(Event *event);
	void onMouseDown(Event *event);
	void onMouseScroll(Event *event);

	static cocos2d::Scene* createScene();

	virtual bool init();

	void escaneando(void);
	void goToPauseScene(Ref *pSender);
	void changeColor(void);
	void goToGameOver(Ref *pSender);
	void playMusic(Ref *pSender);

	//void menuCloseCallback(cocos2d::Ref* pSender);

	void update(float dt);

	// implement the "static create()" method manually
	CREATE_FUNC(Tutorial);
};
#endif // __Tutorial_H__
