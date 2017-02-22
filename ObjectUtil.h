
#ifndef _OBJECTUTIL_H_
#define _OBJECTUTIL_H_

#include <string>
using namespace std;


#define MAX_CHAR  128

class ObjectUtil
{
public:
	~ObjectUtil(void);

	//����
	static ObjectUtil& getCanvas(void);

	void initCharList(HDC hdc);
	//����Բ׶ 
	void drawCone(GLfloat radius, GLfloat height, GLboolean hasBottom=true);
	//��ָ��λ�û����ı�
	void drawText(const char* str, GLfloat winPosX, GLfloat winPosY, GLfloat winPosZ);
protected:

private:
	ObjectUtil(void);

	
	//������
	bool m_bCharListInitialized;

	GLuint m_charList;
};

#endif