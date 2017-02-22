#include "StdAfx.h"
#include "ObjectUtil.h"


ObjectUtil::ObjectUtil(void)
{
	m_bCharListInitialized = false;
}


ObjectUtil::~ObjectUtil(void)
{
}

/*
*	����������
*/
ObjectUtil& ObjectUtil::getCanvas(void){
	static ObjectUtil m_canvas;
	return m_canvas;
}

/*
*	����Բ׶
*	@radius Բ׶����뾶
*	@height Բ׶�߶�
*	@hasBottom �Ƿ���Ƶ���
*/
void ObjectUtil::drawCone(GLfloat radius,GLfloat height,GLboolean hasBottom){
	const int nVertices = 13;

	GLfloat arrowVertices[nVertices][3] = {
		{1.0f,0.0f,0.0f},
		{0.866f,0.5f,0.0f},
		{0.5f,0.866f,0.0f},
		{0.0f,1.0f,0.0f},
		{-0.5f,0.866f,0.0f},
		{-0.866f,0.5f,0.0f},
		{-1.0f,0.0f,0.0f},
		{-0.866f,-0.5f,0.0f},
		{-0.5f,-0.866f,0.0f},
		{0.0f,-1.0f,0.0f},
		{0.5f,-0.866f,0.0f},
		{0.866f,-0.5f,0.0f},
		{1.0f,0.0f,0.0f}	
	};
	
	glPushMatrix();
	glScalef(radius,radius,height);

	if( hasBottom ){
		glBegin(GL_TRIANGLE_FAN);
			glVertex3f(0.0f,0.0f,0.0f);
			for(int i=0; i<nVertices; i++){
				glVertex3fv(arrowVertices[i]);
			}
		glEnd();
	}

	glBegin(GL_TRIANGLE_FAN);
		glVertex3f(0.0f,0.0f,1.0f);
		for(int i=0; i<nVertices; i++){
			glVertex3fv(arrowVertices[i]);
		}
	glEnd();
	glPopMatrix();
}

/*
*	��ʼ���ַ������б� 0-127
*/
void ObjectUtil::initCharList(HDC hdc){
	
	
	if( !m_bCharListInitialized ){
		m_bCharListInitialized = true;
		m_charList = glGenLists(MAX_CHAR);
		wglUseFontBitmaps(wglGetCurrentDC(), 0, MAX_CHAR, m_charList);		
	}

}


/*
*	�����ı�
*	@winPosX �ı�������������ϵ������ X
*	@winPosY �ı�������������ϵ������ Y
*	@winPosZ �ı�������������ϵ������ Z
*/
void ObjectUtil::drawText(const char* str, GLfloat winPosX, GLfloat winPosY, GLfloat winPosZ){
	

	glDisable(GL_LIGHTING);
	glRasterPos3f(winPosX,winPosY,winPosZ);

	//glPushAttrib(GL_LIST_BIT);
	for(; *str!='\0'; ++str){
		glCallList(m_charList + *str);	
	}
	//glPopAttrib();
	glEnable(GL_LIGHTING);
}