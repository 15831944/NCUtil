

#ifndef _AXIES_H_
#define _AXIES_H_

#include "View.h"

class Axies
{

public:	
	~Axies(void);

	static void drawAxies(View& view);
	static void drawSmallAxies(View& view);

protected:

private:
	Axies(void);
	//���Ƽ�ͷ
	static void drawAxisX(GLfloat radius,GLfloat height,GLfloat length); //X����
	static void drawAxisY(GLfloat radius,GLfloat height,GLfloat length); //Y����
	static void drawAxisZ(GLfloat radius,GLfloat height,GLfloat length); //Z����
};

#endif