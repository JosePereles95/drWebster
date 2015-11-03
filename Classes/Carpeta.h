#ifndef __CARPETA_H__
#define __CARPETA_H__

#include "cocos2d.h"

USING_NS_CC;

class Carpeta
{
public:
	Carpeta::Carpeta(int);

	int numero;

	void abreCarpeta(void);
	void cierraCarpeta(void);
	void eliminaCarpeta(void);
};

#endif // __CARPETA_H__