#ifndef __Alice_H__
#define __Alice_H__

#include "cocos2d.h"
#include "Carpeta.h"
#include "Virus.h"
#include "SimpleAudioEngine.h"  

USING_NS_CC;

class Alice : public cocos2d::Layer
{
public:
	//Label
	Label* Dosis;
	Label* Alarma;
	int NDosis;
	Sprite* arch1_1;
	Sprite* arch1_2;
	Sprite* arch1_3;
	int posXarchs1;
	int posYarchs1;

	Sprite* arch2_1;
	Sprite* arch2_2;
	int posXarchs2;
	int posYarchs2;

	Sprite* arch3_1;
	int posXarchs3;
	int posYarchs3;

	Sprite* noChecked1;
	Sprite* Checked1;
	int posXChecked1;
	int posYChecked1;

	Sprite* noChecked2;
	Sprite* Checked2;
	int posXChecked2;
	int posYChecked2;

	Vector<Sprite*> archivos1;
	Vector<Sprite*> archivos2;
	Vector<Sprite*> archivos3;

	Carpeta* carpeta1;
	Carpeta* carpeta2;
	Carpeta* carpeta3;
	int posXCarpeta1;
	int posYCarpeta1;
	int posXCarpeta2;
	int posYCarpeta2;
	int posXCarpeta3;
	int posYCarpeta3;

	Virus* virus1;
	Virus* virus2;
	Virus* virus3;

	Vector<Carpeta*> allCarpetas;

	Vector<Virus*> allVirus;
	Virus* virusElegido;
	Rect cursorRect;
	Rect virusRect;
	Rect papeleraRect;
	Rect carpRect;

	Carpeta* carpetaElegida;

	Sprite* _cursorSprite;
	Sprite* _cursorSprite2;
	Sprite* papeleraSprite;
	Sprite* interfazSprite;

	Sprite* cargando1;
	Sprite* animFuego;
	Sprite* barra;
	MenuItemImage* musica;
	MenuItemImage* pasarNivel;

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
	
	Carpeta* estado;
	int posXStatus;
	int posYStatus;
	Sprite* archStatus_1;
	Vector<Sprite*> allStatus;
	int posXarchsStatus;
	int posYarchsStatus;

	Carpeta* pensamientos;
	int posXThoughs;
	int posYThoughs;
	Sprite* archThoughs_1;
	Vector<Sprite*> allPensamientos;
	int posXarchsThoughs;
	int posYarchsThoughs;

	bool bool_aux;

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
	void goToFinal(Ref *pSender);
	void changeColor(void);
	void goToGameOver(Ref *pSender);
	void playMusic(Ref *pSender);

	//void menuCloseCallback(cocos2d::Ref* pSender);

	void update(float dt);

	// implement the "static create()" method manually
	CREATE_FUNC(Alice);
};
#endif // __Alice_H__