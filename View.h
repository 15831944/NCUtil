/**
*	created on 2017-1-13
*	author 张岳文
*
*	opengl 视图类
*	用于视图交互
*	1. 视图平移
*	2. 视图旋转
*	3. 视图缩放
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

	//设置屏幕宽高比
	void setWindowRatio(GLfloat windowRatio);

	//视图平移、旋转、缩放
	void translate(GLfloat dxRate, GLfloat dyRate);
	void rotate(GLfloat dxRate, GLfloat dyRate);
	void scale(CPoint pt, GLshort zDelta);
protected:

private:
	//常数
	GLfloat PI;

	GLfloat m_angleH;		//水平角度
	GLfloat m_angleV;		//垂直角度
	GLfloat m_radius;		//视点距离，半径

	glm::vec3 m_eye;		//眼睛的位置
	glm::vec3 m_center;		//眼睛焦点的位置
	glm::vec3 m_up;			//向上的向量

	//屏幕窗口的宽高比 w/h
	GLfloat m_windowRatio;
	//glOrtho函数的6个参数
	GLfloat m_fromX;	
	GLfloat m_toX;
	GLfloat m_fromY;
	GLfloat m_toY;
	GLfloat m_fromZ;
	GLfloat m_toZ;

	//根据水平角度、垂直角度和视点半径
	//计算gluLookAt()的三组参数
	void updateViewParameters(void);
	void updateRangeParameters(void);
};

#endif