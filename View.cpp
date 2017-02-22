#include "StdAfx.h"
#include "View.h"


View::View(void){
	
	//����
	PI = acos(-1.0f);
	//һ�鿪�ر���
	m_bLightPositionWithEye = true;

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
*	��ȡglOrtho��6�ķ�Χ����
*   fromX, toX, fromY, toY, fromZ, toZ
*/
GLfloat View::getFromX(void){
	return m_fromX;
}
GLfloat View::getToX(void){
	return m_toX;
}
GLfloat View::getFromY(void){
	return m_fromY;
}
GLfloat View::getToY(void){
	return m_toY;
}
GLfloat View::getFromZ(void){
	return m_fromZ;
}
GLfloat View::getToZ(void){
	return m_toZ;
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

	if(width<100){
		width = 100;
	}
	if(height<100){
		height = 100;
	}

	m_viewportXBegin = xBegin;
	m_viewportYBegin = yBegin;
	m_viewportWidth = width;
	m_viewportHeight = height;

	GLfloat windowWidth = width;
	GLfloat windowHeight = height;

	setWindowRatio(windowWidth/windowHeight);

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
	glGetIntegerv(GL_VIEWPORT,viewport);

	GLfloat rangeX = m_toX-m_fromX;
	GLfloat rangeY = m_toY-m_fromY;
	GLfloat rangeWindowX = viewport[2];
	GLfloat rangeWindowY = viewport[3];

	GLfloat windowX = pt.x + 0.5;
	GLfloat windowY = pt.y + 0.5;

	m_fromX = m_fromX - rangeX * (scaleRatio-1.0) * (windowX-0) / rangeWindowX;
	m_toX = m_toX + rangeX * (scaleRatio-1.0) * (rangeWindowX-windowX) / rangeWindowX;
	m_fromY = m_fromY - rangeY * (scaleRatio-1.0) * (rangeWindowY-windowY) / rangeWindowY;
	m_toY = m_toY + rangeY * (scaleRatio-1.0) * (windowY) / rangeWindowY;
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

	if( m_bLightPositionWithEye ){
		glLightfv(GL_LIGHT0,GL_POSITION,glm::value_ptr(glm::vec4(m_eye,0.0f)) );
	}
}

/*
*	���ű�������Ĳ���
*/
void View::fitScale(void){
	GLfloat factor = 0.02f*(m_toY - m_fromY);
	glScalef(factor,factor,factor);
}