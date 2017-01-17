#include "StdAfx.h"
#include "View.h"


View::View(void){
	
	//常数
	PI = acos(-1.0f);

	//初始化 水平角度、垂直角度、视点半径
	m_hAngle = -45.0f;
	m_vAngle = 45.0f;
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
*	设置视图窗口位置和大小
*/
void View::setViewport(int xBegin, int yBegin, int width, int height){
	m_viewportXBegin = xBegin;
	m_viewportYBegin = yBegin;
	m_viewportWidth = width;
	m_viewportHeight = height;

	GLfloat windowWidth = width;
	GLfloat windowHeight = height;

	setWindowRatio(width/height);

	glViewport(xBegin,yBegin,width,height);
}

/*
*	根据水平角度、垂直角度和视点半径
*	计算gluLookAt参数
*	即计算 m_eye m_up
*/
void View::updateViewParameters(void){
	GLfloat radianH = glm::radians(m_hAngle);
	GLfloat radianV = glm::radians(m_vAngle);

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
*	设置glOrtho的参数
*	@fromX @toX 投影时坐标轴X方向的范围
*	@fromY @toY 投影时坐标轴Y方向的范围
*	@fromZ @toZ 投影时坐标轴Z方向的范围
*/
void View::setOrtho(GLfloat fromX, GLfloat toX, GLfloat fromY, GLfloat toY, GLfloat fromZ, GLfloat toZ){
	m_fromX = fromX;
	m_toX = toX;
	m_fromY = fromY;
	m_toY = toY;
	m_fromZ = fromZ;
	m_toZ = toZ;
}

/*
*	设置gluLookAt的间接参数
*	@radius 眼睛与视点的距离
*	@hAngle	眼睛方位的水平角度，X轴为0度，逆时针为正，单位 度
*	@vAngle 眼睛方位的垂直角度，水平面为0度，向上为正，单位 度
*/
void View::setLookAt(GLfloat radius, GLfloat hAngle, GLfloat vAngle){
	m_radius = radius;
	m_hAngle = hAngle;
	m_vAngle = vAngle;

	updateViewParameters();
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
	m_hAngle = m_hAngle - glm::degrees(dxRate*PI*2.0f);
	m_vAngle = m_vAngle + glm::degrees(dyRate*PI*2.0f);

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
	/*
	GLfloat rangeX = m_toX-m_fromX;
	GLfloat rangeY = m_toY-m_fromY;

	m_fromX = m_fromX - rangeX * (scaleRatio-1.0) * (posX-(-1.0)) * 0.5;
	m_toX = m_toX + rangeX * (scaleRatio-1.0) * (1.0-posX) * 0.5;
	m_fromY = m_fromY - rangeY * (scaleRatio-1.0) * (posY-(-1.0)) * 0.5;
	m_toY = m_toY + rangeY * (scaleRatio-1.0) * (1.0-posY) * 0.5;
	*/

	GLfloat fromX = m_fromX - (m_toX-m_fromX)*(scaleRatio-1.0)*(posX-(-1.0))*0.5;
	GLfloat toX = m_toX + (m_toX-m_fromX)*(scaleRatio-1.0)*(1.0-posX)*0.5;
	GLfloat fromY = m_fromY - (m_toY-m_fromY)*(scaleRatio-1.0)*(posY-(-1.0))*0.5;
	GLfloat toY = m_toY + (m_toY-m_fromY)*(scaleRatio-1.0)*(1.0-posY)*0.5;


	if( (toY - fromY)< 1.0f ){
		return;
	}

	m_fromX = fromX;
	m_toX = toX;
	m_fromY = fromY;
	m_toY = toY;
}

/*
*	对glOrtho函数的封装
*/
void View::viewToProjection(void){
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(m_fromX,m_toX,m_fromY,m_toY,m_fromZ,m_toZ);
}

/*
*	对gluLookAt函数的封装
*/
void View::modelToView(void){
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(m_eye.x,m_eye.y,m_eye.z,m_center.x,m_center.y,m_center.z,m_up.x,m_up.y,m_up.z);
}