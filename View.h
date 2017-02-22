/**
*	created on 2017-1-13
*	author ������
*
*	opengl ��ͼ��
*	������ͼ����
*	1. ��ͼƽ��
*	2. ��ͼ��ת
*	3. ��ͼ����
*/
#pragma once
#ifndef _VIEW_H_
#define _VIEW_H_

#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

class View
{
public:
	View(void);
	~View(void);

	GLfloat getFromX(void);
	GLfloat getToX(void);
	GLfloat getFromY(void);
	GLfloat getToY(void);
	GLfloat getFromZ(void);
	GLfloat getToZ(void);


	// ������Ļ��߱�
	void setWindowRatio(GLfloat windowRatio);
	// ������Ļ���ڵ���ʾ
	void setViewport(int xBegin, int yBegin, int width, int height);

	// ���� glOrtho�Ĳ���
	void setOrtho(GLfloat fromX, GLfloat toX, GLfloat fromY, GLfloat toY, GLfloat fromZ, GLfloat toZ);
	// ���� gluLookAt�Ĳ���
	void setLookAt(GLfloat radius, GLfloat hAngle, GLfloat vAngle);

	// ��ͼƽ�ơ���ת������
	void translate(GLfloat dxRate, GLfloat dyRate);
	void rotate(GLfloat dxRate, GLfloat dyRate);
	void scale(CPoint pt, GLshort zDelta);
	
	// ��ռ��ת�����൱��glOrtho������gluLookAt���� 
	void viewToProjection(void);
	void modelToView(void);

	void fitScale();
	void fitScale(GLfloat yRange);
protected:

private:
	//����
	GLfloat PI;
	//һ�鿪�ر���
	bool m_bLightPositionWithEye;	//���յ�λ���Ƿ����۾���λ��

	GLfloat m_hAngle;		//ˮƽ�Ƕ�
	GLfloat m_vAngle;		//��ֱ�Ƕ�
	GLfloat m_radius;		//�ӵ���룬�뾶

	glm::vec3 m_eye;		//�۾���λ��
	glm::vec3 m_center;		//�۾������λ��
	glm::vec3 m_up;			//���ϵ�����

	//��Ļ���ڵĿ�߱� w/h
	GLfloat m_windowRatio;
	//��ͼ���ڵ�λ�úʹ�С
	GLint m_viewportXBegin;
	GLint m_viewportYBegin;
	GLint m_viewportWidth;
	GLint m_viewportHeight;
	//glOrtho������6������
	GLfloat m_fromX;	
	GLfloat m_toX;
	GLfloat m_fromY;
	GLfloat m_toY;
	GLfloat m_fromZ;
	GLfloat m_toZ;

	//����ˮƽ�Ƕȡ���ֱ�ǶȺ��ӵ�뾶
	//����gluLookAt()���������
	void updateViewParameters(void);
	void updateRangeParameters(void);
};

#endif