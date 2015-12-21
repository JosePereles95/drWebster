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
	//Label
	Label* Dosis;
	Label* Alarma;
	Sprite* arch1_1;
	Sprite* arch1_2;
	Sprite* arch1_3;
	Sprite* arch1_4;
	int posXarchs1;
	int posYarchs1;

	Sprite* arch2_1;
	int posXarchs2;
	int posYarchs2;

	Sprite* arch3_1;
	int posXarchs3;
	int posYarchs3;

	Sprite* arch4_1;
	int posXarchs4;
	int posYarchs4;

	Sprite* noChecked1;
	Sprite* Checked1;

	int posXChecked1;
	int posYChecked1;

	Vector<Sprite*> archivos1;
	Vector<Sprite*> archivos2;
	Vector<Sprite*> archivos3;
	Vector<Sprite*> archivos4;

	Carpeta* carpeta1;
	Carpeta* carpeta2;
	Carpeta* carpeta3;
	Carpeta* carpeta4;
	int posXCarpeta1;
	int posYCarpeta1;
	int posXCarpeta2;
	int posYCarpeta2;
	int posXCarpeta3;
	int posYCarpeta3;
	int posXCarpeta4;
	int posYCarpeta4;

	Virus* virus1;

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
	Sprite* victorySprite;

	Sprite* cargando1;
	Sprite* animFuego;
	Sprite* barra;
	MenuItemImage* musica;
	MenuItemImage* pasarNivel;

	Sprite* falso1; //Carpeta1
	Sprite* falso2; //Carpeta3
	Sprite* falso3; //Carpeta4
	Sprite* falso4; //Musica
	Sprite* falso5; //Pensamiento
	Sprite* falso6; //Mail
	Sprite* falso7; //Noticias
	Sprite* falso8; //Carpeta2

	Sprite* tuto1;
	Sprite* tuto2;
	Sprite* tuto3;
	Sprite* tuto4;
	Sprite* tuto5;
	Sprite* tuto6;
	Sprite* tuto7;
	Sprite* tuto8;
	Sprite* tuto9;
	bool bool_aux;
	bool bool_aux2;
	bool bool_aux3;
	bool bool_aux4;
	bool bool_aux5;

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
	Sprite* archMail_4;
	Vector<Sprite*> allMails;
	int posXarchsMail;
	int posYarchsMail;

	Carpeta* pensamientos;
	int posXThoughs;
	int posYThoughs;
	Sprite* archThoughs_1;
	Vector<Sprite*> allStatus;
	int posXarchsThoughs;
	int posYarchsThoughs;

	Sprite* estado;

	CocosDenshion::SimpleAudioEngine* musicaWebster;
	unsigned int scanEffect;

	Sequence* secuenciaEscaneo;

	void onMouseMove(Event *event);
	void onMouseUp(Event *event);
	void onMouseDown(Event *event);
	void onMouseScroll(Event *event);

	static cocos2d::Scene* createScene();

	virtual bool init();

	void victoria(void);
	void escaneando(void);
	void goToPauseScene(Ref *pSender);
	void changeColor(void);
	void goToGameOver(Ref *pSender);
	void playMusic(Ref *pSender);
	void terminarNivel(Ref *pSender);

	void changeTutorial1(void);
	void wait1(void);
	void changeTutorial2(void);
	void wait2(void);
	void changeTutorial3(void);
	void wait3(void);
	void changeTutorial4(void);
	void wait4(void);
	void changeTutorial5(void);
	void wait5(void);
	void changeTutorial6(void);
	void wait6(void);
	void changeTutorial7(void);
	void wait7(void);
	void changeTutorial8(void);
	void wait8(void);
	void changeTutorial9(void);


	//Shake
	bool bool_auxshake;
	void Detenershake(void);
	void shakeScreen(float dt);
	float rangeRandom(float, float);
	Vec2 punto;

	void update(float dt);

	// implement the "static create()" method manually
	CREATE_FUNC(Tutorial);
};
#endif // __Tutorial_H__