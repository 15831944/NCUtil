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

class View
{
public:
	View(void);
	~View(void);

	//������Ļ��߱�
	void setWindowRatio(GLfloat windowRatio);

	//��ͼƽ�ơ���ת������
	void translate(GLfloat dxRate, GLfloat dyRate);
	void rotate(GLfloat dxRate, GLfloat dyRate);
	void scale(CPoint pt, GLshort zDelta);
protected:

private:
	//����
	GLfloat PI;

	GLfloat m_angleH;		//ˮƽ�Ƕ�
	GLfloat m_angleV;		//��ֱ�Ƕ�
	GLfloat m_radius;		//�ӵ���룬�뾶

	glm::vec3 m_eye;		//�۾���λ��
	glm::vec3 m_center;		//�۾������λ��
	glm::vec3 m_up;			//���ϵ�����

	//��Ļ���ڵĿ�߱� w/h
	GLfloat m_windowRatio;
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