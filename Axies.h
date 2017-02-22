

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
	//绘制箭头
	static void drawAxisX(GLfloat radius,GLfloat height,GLfloat length); //X方向
	static void drawAxisY(GLfloat radius,GLfloat height,GLfloat length); //Y方向
	static void drawAxisZ(GLfloat radius,GLfloat height,GLfloat length); //Z方向
};

#endif