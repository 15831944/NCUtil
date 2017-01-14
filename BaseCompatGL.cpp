#include "stdafx.h"
#include "BaseCompatGL.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


BaseCompatGL::BaseCompatGL(void){
	m_backgroundColorTop = glm::vec3(0.0f,0.0f,0.0f);
	m_backgroundColorBottom = glm::vec3(0.0f,0.0f,0.0f);
}
BaseCompatGL::~BaseCompatGL(void){

}

/*
*	��MFC��CView���д���OpenGL��Ⱦ����
*	��CView��OnCreate�е��ô�����Դ
*/
BOOL BaseCompatGL::createContext(CView* pView){

	m_pView = pView;

	//�ڿͻ�����ͼ������豸������DC;
	m_pDC = new CClientDC(pView);

	int pixelformat;
		
	static PIXELFORMATDESCRIPTOR pfd = {
		sizeof(PIXELFORMATDESCRIPTOR),
		1,										
		PFD_DRAW_TO_WINDOW |	
		PFD_SUPPORT_OPENGL|
		PFD_DOUBLEBUFFER,
		PFD_TYPE_RGBA,
		32,					//��ɫ�����λ��
		0,0,0,0,0,0,		//
		0,
		0,
		0,
		0,0,0,0,
		32,					//z����λ������Ȼ��棩
		0,					//stencil����λ����ģ�建�棩
		0,					//auxiliary����
		PFD_MAIN_PLANE,
		0,
		0,0,0
	};

	if((pixelformat = ChoosePixelFormat(m_pDC->GetSafeHdc(), &pfd )) == 0 ){
		AfxMessageBox(_T("�ڸ�DC���Ҳ�����PFD�ӽ���λͼ�ṹ"));
		return FALSE;
	}
	
	int nRet = SetPixelFormat(m_pDC->GetSafeHdc(), pixelformat, &pfd);
	if ( nRet == FALSE)//����Ӳ���Ƿ�֧�ָ�pdf
    {
        AfxMessageBox(_T("�޷��ڸ�DC������λͼ�ṹ"));
        return FALSE;
    }

	//����openGL�豸����
	m_hRC = wglCreateContext(m_pDC->GetSafeHdc());
	//��openGL�豸�������óɵ�ǰ
	wglMakeCurrent(m_pDC->GetSafeHdc(),m_hRC);

	return TRUE;
}



/*
*	ɾ��MFC��Ⱦ����
*	��CView��OnDestroy()�е����ͷ���Դ
*/
BOOL BaseCompatGL::deleteContext(void){
	//�ͷ�RC�Լ�DC
	if(wglGetCurrentContext()!=NULL) 
		::wglMakeCurrent(NULL,  NULL);
	if (m_hRC)
        ::wglDeleteContext(m_hRC);
	if (m_pDC)
        delete m_pDC;

	return TRUE;
}

/*
*	��ȡ�豸���
*/
CClientDC* BaseCompatGL::getClientDC(void){
	assert(m_pDC!=nullptr);
	return m_pDC;
}

/*
*	����ȫ����ɫ
*/
void BaseCompatGL::setBackgroundColor(GLfloat red, GLfloat green, GLfloat blue){
	m_backgroundColorTop = glm::vec3(red,green,blue);
	m_backgroundColorBottom = glm::vec3(red,green,blue);
}
/*
*	�����Ϸ�����ɫ
*/
void BaseCompatGL::setBackgroundColorTop(GLfloat red, GLfloat green, GLfloat blue){
	m_backgroundColorTop = glm::vec3(red,green,blue);
}
/*
*	�����·�����ɫ
*/
void BaseCompatGL::setBackgroundColorBottom(GLfloat red, GLfloat green, GLfloat blue){
	m_backgroundColorBottom = glm::vec3(red,green,blue);
}

/*
*	���Ʊ���
*/
void BaseCompatGL::drawBackground(void){
	//������ɫ�������Ȼ���
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	const int VERTICES_COUNT = 6;

	GLfloat vertices[VERTICES_COUNT][3] = {
		{-1.0f, -1.0f, 1.0f},
		{1.0f, 1.0f, 1.0f},
		{-1.0f, 1.0f, 1.0f},
		{-1.0f, -1.0f, 1.0f},
		{1.0f, -1.0f, 1.0f},
		{1.0f, 1.0f, 1.0f}
	};

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glDisable(GL_LIGHTING);
	glDepthFunc(GL_LEQUAL);
	glBegin(GL_TRIANGLES);
		glColor3fv( glm::value_ptr(m_backgroundColorBottom) );
		glVertex3fv( vertices[0] );
		glColor3fv( glm::value_ptr(m_backgroundColorTop) );
		glVertex3fv( vertices[1] );
		glColor3fv( glm::value_ptr(m_backgroundColorTop) );
		glVertex3fv( vertices[2] );

		glColor3fv( glm::value_ptr(m_backgroundColorBottom) );
		glVertex3fv( vertices[3] );
		glColor3fv( glm::value_ptr(m_backgroundColorBottom) );
		glVertex3fv( vertices[4] );
		glColor3fv( glm::value_ptr(m_backgroundColorTop) );
		glVertex3fv( vertices[5] );
	glEnd();
	glDepthFunc(GL_LESS);
	glEnable(GL_LIGHTING);
}

/*
*	OpenGL�ĳ�ʼ��
*/
void BaseCompatGL::init(void){
	glClearColor(0.0f,0.0f,0.0f,1.0f);
	glEnable(GL_DEPTH_TEST);
	glClearDepth(1.0f);

	//��ʼ������
	initLighting();
}

/*
*	�û�˫�㻺�� 
*	SwapBuffers�ķ�װ
*/
void BaseCompatGL::show(void){
	if( !m_pDC ){
		return;
	}
	SwapBuffers( m_pDC->GetSafeHdc() );
}

/*
*	��ʼ��OpenGL�Ĺ���
*/
void BaseCompatGL::initLighting(void){
	GLfloat light_ambient[] = {0.0f,0.0f,0.0f,1.0f};	//ambient ������ 
	GLfloat light_diffuse[] = {1.0f,1.0f,1.0f,1.0f};	//diffuse �������
	GLfloat light_specular[] = {1.0f,1.0f,1.0f,1.0f};	//specular ���淴���
	GLfloat light_shininess = 16;	//����ϵ��

	glLightfv(GL_LIGHT0,GL_AMBIENT,light_ambient);
	glLightfv(GL_LIGHT0,GL_DIFFUSE,light_diffuse);
	glLightfv(GL_LIGHT0,GL_SPECULAR,light_specular);
	glLightf(GL_LIGHT0,GL_SHININESS,light_shininess);	

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);
	glShadeModel(GL_SMOOTH);
}