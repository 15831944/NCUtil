#include "StdAfx.h"
#include "Axies.h"

#include "ObjectUtil.h"

Axies::Axies(void)
{
}


Axies::~Axies(void)
{
}

/*
*	���Ƽ�ͷ����X������
*/
void Axies::drawAxisX(GLfloat radius,GLfloat height,GLfloat length){
	glDisable(GL_LIGHTING);
	//glDepthFunc(GL_ALWAYS);
	glPushMatrix();

	glRotatef(90.0f,0.0f,1.0f,0.0f);
	// Z����ɫ
	glColor3f(1.0f,0.0f,0.0f);
	
	glBegin(GL_LINES);
	glVertex3f(0.0f,0.0f,0.0f);
	glVertex3f(0.0f,0.0f,length);
	glEnd();
	glTranslatef(0.0f,0.0f,length);
	ObjectUtil::getCanvas().drawCone(radius,height,false);
	
	glPopMatrix();
	//glDepthFunc(GL_LESS);
	glEnable(GL_LIGHTING);
}

/*
*	���Ƽ�ͷ����Y������
*/
void Axies::drawAxisY(GLfloat radius,GLfloat height,GLfloat length){
	glDisable(GL_LIGHTING);
	//glDepthFunc(GL_ALWAYS);
	glPushMatrix();

	glRotatef(-90.0f,1.0f,0.0f,0.0f);
	// Z����ɫ
	glColor3f(0.0f,1.0f,0.0f);
	
	glBegin(GL_LINES);
	glVertex3f(0.0f,0.0f,0.0f);
	glVertex3f(0.0f,0.0f,length);
	glEnd();
	glTranslatef(0.0f,0.0f,length);
	ObjectUtil::getCanvas().drawCone(radius,height,false);
	
	glPopMatrix();
	//glDepthFunc(GL_LESS);
	glEnable(GL_LIGHTING);
}

/*
*	���Ƽ�ͷ����Z������
*/
void Axies::drawAxisZ(GLfloat radius,GLfloat height,GLfloat length){
	glDisable(GL_LIGHTING);
	//glDepthFunc(GL_ALWAYS);
	glPushMatrix();

	// Z����ɫ
	glColor3f(0.0f,0.0f,1.0f);

	glBegin(GL_LINES);
	glVertex3f(0.0f,0.0f,0.0f);
	glVertex3f(0.0f,0.0f,length);
	glEnd();
	glTranslatef(0.0f,0.0f,length);
	ObjectUtil::getCanvas().drawCone(radius,height,false);
	
	glPopMatrix();
	//glDepthFunc(GL_LESS);
	glEnable(GL_LIGHTING);
	
}

/*
*	����������ϵ��X Y Z�ᣬ��С������Ļ�仯
*/
void Axies::drawAxies(View& view){
	//glClear(GL_DEPTH_BUFFER_BIT);
	view.viewToProjection();
	view.modelToView();

	glPushMatrix();
	view.fitScale();
	drawAxisX(1.0f,4.0f,10.0f);
	drawAxisY(1.0f,4.0f,10.0f);
	drawAxisZ(1.0f,4.0f,10.0f);
	glPopMatrix();
}

/*
* ����Ļ���½ǻ���С�ĸ���������
*/
void Axies::drawSmallAxies(View& view){

	

	GLint viewport[4];		//��ͼ����
	glGetIntegerv(GL_VIEWPORT,viewport);

	glViewport(0,0,100,100);
	glClear(GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-15.0,15.0,-15,15,1.0,1000000.0);
	view.modelToView();
	drawAxisX(1.0f,4.0f,10.0f);
	ObjectUtil::getCanvas().drawText("X",15.0f,0.0f,0.0f);
	drawAxisY(1.0f,4.0f,10.0f);
	ObjectUtil::getCanvas().drawText("Y",0.0f,15.0f,0.0f);
	drawAxisZ(1.0f,4.0f,10.0f);
	ObjectUtil::getCanvas().drawText("Z",0.0f,0.0f,15.0f);

	glViewport(viewport[0],viewport[1],viewport[2],viewport[3]);
}