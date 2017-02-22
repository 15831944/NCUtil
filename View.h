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


	// 设置屏幕宽高比
	void setWindowRatio(GLfloat windowRatio);
	// 设置屏幕窗口的显示
	void setViewport(int xBegin, int yBegin, int width, int height);

	// 设置 glOrtho的参数
	void setOrtho(GLfloat fromX, GLfloat toX, GLfloat fromY, GLfloat toY, GLfloat fromZ, GLfloat toZ);
	// 设置 gluLookAt的参数
	void setLookAt(GLfloat radius, GLfloat hAngle, GLfloat vAngle);

	// 视图平移、旋转、缩放
	void translate(GLfloat dxRate, GLfloat dyRate);
	void rotate(GLfloat dxRate, GLfloat dyRate);
	void scale(CPoint pt, GLshort zDelta);
	
	// 点空间的转化，相当于glOrtho函数和gluLookAt函数 
	void viewToProjection(void);
	void modelToView(void);

	void fitScale();
	void fitScale(GLfloat yRange);
protected:

private:
	//常数
	GLfloat PI;
	//一组开关变量
	bool m_bLightPositionWithEye;	//光照的位置是否是眼睛的位置

	GLfloat m_hAngle;		//水平角度
	GLfloat m_vAngle;		//垂直角度
	GLfloat m_radius;		//视点距离，半径

	glm::vec3 m_eye;		//眼睛的位置
	glm::vec3 m_center;		//眼睛焦点的位置
	glm::vec3 m_up;			//向上的向量

	//屏幕窗口的宽高比 w/h
	GLfloat m_windowRatio;
	//视图窗口的位置和大小
	GLint m_viewportXBegin;
	GLint m_viewportYBegin;
	GLint m_viewportWidth;
	GLint m_viewportHeight;
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