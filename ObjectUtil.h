
#ifndef _OBJECTUTIL_H_
#define _OBJECTUTIL_H_

#include <string>
using namespace std;


#define MAX_CHAR  128

class ObjectUtil
{
public:
	~ObjectUtil(void);

	//单例
	static ObjectUtil& getCanvas(void);

	void initCharList(HDC hdc);
	//绘制圆锥 
	void drawCone(GLfloat radius, GLfloat height, GLboolean hasBottom=true);
	//在指定位置绘制文本
	void drawText(const char* str, GLfloat winPosX, GLfloat winPosY, GLfloat winPosZ);
protected:

private:
	ObjectUtil(void);

	
	//开关量
	bool m_bCharListInitialized;

	GLuint m_charList;
};

#endif