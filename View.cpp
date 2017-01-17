#include "StdAfx.h"
#include "View.h"


View::View(void){
	
	//����
	PI = acos(-1.0f);

	//��ʼ�� ˮƽ�Ƕȡ���ֱ�Ƕȡ��ӵ�뾶
	m_hAngle = -45.0f;
	m_vAngle = 45.0f;
	m_radius = 10000.0f;
	//��ʼ�� �۾�����λ��
	m_center = glm::vec3(0.0f,0.0f,0.0f);
	//��������������������gluLookAt����
	updateViewParameters();

	//��ʼ�� ��Ļ��߱�
	m_windowRatio = 4.0f/3.0f;
	m_fromY = -100.0f;
	m_toY = 100.0f;
	//���� ��߱� �� y��Χ ����glOrtho����
	updateRangeParameters();
}


View::~View(void){

}

/*
*	������Ļ��߱�
*	ͬʱ����glOrtho�Ĳ���
*/
void View::setWindowRatio(GLfloat windowRatio){
	m_windowRatio = windowRatio;
	updateRangeParameters();
}

/*
*	������ͼ����λ�úʹ�С
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
*	����ˮƽ�Ƕȡ���ֱ�ǶȺ��ӵ�뾶
*	����gluLookAt����
*	������ m_eye m_up
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
*	������Ļ���ڴ�Сʱ����glOrtho��x��Χ��y��Χ
*	���� ��Ļ���� y��Χ ����
*	x��Χ
*/
void View::updateRangeParameters(void){
	//���º��X��Χ
	GLfloat rangeX = (m_toY - m_fromY) * m_windowRatio;
	GLfloat centerX = (m_toX + m_fromX) * 0.5f; //x��Χ������

	m_fromX = centerX - rangeX * 0.5f;
	m_toX = centerX + rangeX * 0.5;
}

/*
*	����glOrtho�Ĳ���
*	@fromX @toX ͶӰʱ������X����ķ�Χ
*	@fromY @toY ͶӰʱ������Y����ķ�Χ
*	@fromZ @toZ ͶӰʱ������Z����ķ�Χ
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
*	����gluLookAt�ļ�Ӳ���
*	@radius �۾����ӵ�ľ���
*	@hAngle	�۾���λ��ˮƽ�Ƕȣ�X��Ϊ0�ȣ���ʱ��Ϊ������λ ��
*	@vAngle �۾���λ�Ĵ�ֱ�Ƕȣ�ˮƽ��Ϊ0�ȣ�����Ϊ������λ ��
*/
void View::setLookAt(GLfloat radius, GLfloat hAngle, GLfloat vAngle){
	m_radius = radius;
	m_hAngle = hAngle;
	m_vAngle = vAngle;

	updateViewParameters();
}

/*
*	��ͼƽ��
*	@dxRate ���x�ڴ��ں����ƶ�����
*	@dyRate ���y�ڴ��������ƶ�����
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
*	��ͼ��ת
*	@dxRate ���x�ڴ��ں����ƶ�����
*	@dyRate ���y�ڴ��������ƶ�����
*/
void View::rotate(GLfloat dxRate, GLfloat dyRate){
	m_hAngle = m_hAngle - glm::degrees(dxRate*PI*2.0f);
	m_vAngle = m_vAngle + glm::degrees(dyRate*PI*2.0f);

	updateViewParameters();
}

/*
*	��ͼ����
*	@pt ���λ�ã�����������
*	@zDelta �����ֵ��ƶ���
*/
void View::scale(CPoint pt, GLshort zDelta){

	GLdouble scaleRatio; //���ű���
	if( zDelta > 0 ){
		scaleRatio = 1.1;	//�Ŵ�
	}else{
		scaleRatio = 0.9;	//��С
	}


	GLint viewport[4];		//��ͼ����
	GLdouble modelview[16];	//ģ����ͼ����
	GLdouble projection[16];	//ͶӰ����
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
*	��glOrtho�����ķ�װ
*/
void View::viewToProjection(void){
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(m_fromX,m_toX,m_fromY,m_toY,m_fromZ,m_toZ);
}

/*
*	��gluLookAt�����ķ�װ
*/
void View::modelToView(void){
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(m_eye.x,m_eye.y,m_eye.z,m_center.x,m_center.y,m_center.z,m_up.x,m_up.y,m_up.z);
}