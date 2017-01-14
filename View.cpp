#include "StdAfx.h"
#include "View.h"


View::View(void){
	
	//常数
	PI = acos(-1.0f);

	//初始化 水平角度、垂直角度、视点半径
	m_angleH = -45.0f;
	m_angleV = 45.0f;
	m_radius = 10000.0f;
	//初始化 眼睛焦点位置
	m_center = glm::vec3(0.0f,0.0f,0.0f);
	//根据上面三个参数计算gluLookAt参数
	updateViewParameters();

	//初始化 屏幕宽高比
	m_windowRatio = 4.0f/3.0f;
	m_fromY = -100.0f;
	m_toY = 100.0f;
	//根据 宽高比 和 y范围 更新glOrtho参数
	updateRangeParameters();
}


View::~View(void){

}

/*
*	设置屏幕宽高比
*	同时更新glOrtho的参数
*/
void View::setWindowRatio(GLfloat windowRatio){
	m_windowRatio = windowRatio;
	updateRangeParameters();
}


/*
*	根据水平角度、垂直角度和视点半径
*	计算gluLookAt参数
*	即计算 m_eye m_up
*/
void View::updateViewParameters(void){
	GLfloat radianH = glm::radians(m_angleH);
	GLfloat radianV = glm::radians(m_angleV);

	m_eye.x = m_radius * cos(radianV) * cos(radianH);
	m_eye.y = m_radius * cos(radianV) * sin(radianH);
	m_eye.z = m_radius * sin(radianV);

	m_up.x = - sin(radianV) * cos(radianH);
	m_up.y = - sin(radianV) * sin(radianH);
	m_up.z = cos(radianV);
}

/*
*	调整屏幕窗口大小时更新glOrtho的x范围和y范围
*	根据 屏幕窗口 y范围 计算
*	x范围
*/
void View::updateRangeParameters(void){
	//更新后的X范围
	GLfloat rangeX = (m_toY - m_fromY) * m_windowRatio;
	GLfloat centerX = (m_toX + m_fromX) * 0.5f; //x范围的中心

	m_fromX = centerX - rangeX * 0.5f;
	m_toX = centerX + rangeX * 0.5;
}

/*
*	视图平移
*	@dxRate 鼠标x在窗口横向移动比例
*	@dyRate 鼠标y在窗口纵向移动比例
*/
void View::translate(GLfloat dxRate, GLfloat dyRate){
	GLfloat dx = (m_toX - m_fromX) * dxRate;
	GLfloat dy = -(m_toY - m_fromY) * dyRate;

	m_fromX = m_fromX - dx;
	m_toX = m_toX - dx;
	m_fromY = m_fromY - dy;
	m_toY = m_toY - dy;
}

/*
*	视图旋转
*	@dxRate 鼠标x在窗口横向移动比例
*	@dyRate 鼠标y在窗口纵向移动比例
*/
void View::rotate(GLfloat dxRate, GLfloat dyRate){
	m_angleH = m_angleH - glm::degrees(dxRate*PI*2.0f);
	m_angleV = m_angleV + glm::degrees(dyRate*PI*2.0f);

	updateViewParameters();
}

/*
*	视图缩放
*	@pt 鼠标位置，即缩放中心
*	@zDelta 鼠标滚轮的移动量
*/
void View::scale(CPoint pt, GLshort zDelta){

	GLdouble scaleRatio; //缩放比例
	if( zDelta > 0 ){
		scaleRatio = 1.1;	//放大
	}else{
		scaleRatio = 0.9;	//缩小
	}

	GLint viewport[4];		//视图窗口
	GLdouble modelview[16];	//模型视图矩阵
	GLdouble projection[16];	//投影矩阵
	GLfloat winX, winY, winZ;
	GLdouble posX, posY, posZ;

	glGetDoublev(GL_MODELVIEW_MATRIX,modelview);
	glGetDoublev(GL_PROJECTION_MATRIX,projection);
	glGetIntegerv(GL_VIEWPORT,viewport);

	winX = (float)pt.x;
	winY = (float)(viewport[3]-(float)pt.y);
	glReadPixels(int(winX),int(winY),1,1,GL_DEPTH_COMPONENT,GL_FLOAT,&winZ);
	gluUnProject(winX,winY,winZ,modelview,projection,viewport,&posX,&posY,&posZ);

	GLfloat rangeX = m_toX-m_fromX;
	GLfloat rangeY = m_toY-m_fromY;

	m_fromX = m_fromX - rangeX * (scaleRatio-1.0) * (posX-(-1.0)) * 0.5;
	m_toX = m_toX + rangeX * (scaleRatio-1.0) * (1.0-posX) * 0.5;
	m_fromY = m_fromY - rangeY * (scaleRatio-1.0) * (posY-(-1.0)) * 0.5;
	m_toY = m_toY + rangeY * (scaleRatio-1.0) * (1.0-posY) * 0.5;
}