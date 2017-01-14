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
*	在MFC的CView类中创建OpenGL渲染环境
*	在CView的OnCreate中调用创建资源
*/
BOOL BaseCompatGL::createContext(CView* pView){

	m_pView = pView;

	//在客户区作图，获得设备描述符DC;
	m_pDC = new CClientDC(pView);

	int pixelformat;
		
	static PIXELFORMATDESCRIPTOR pfd = {
		sizeof(PIXELFORMATDESCRIPTOR),
		1,										
		PFD_DRAW_TO_WINDOW |	
		PFD_SUPPORT_OPENGL|
		PFD_DOUBLEBUFFER,
		PFD_TYPE_RGBA,
		32,					//颜色缓存的位数
		0,0,0,0,0,0,		//
		0,
		0,
		0,
		0,0,0,0,
		32,					//z缓存位数（深度缓存）
		0,					//stencil缓存位数（模板缓存）
		0,					//auxiliary缓存
		PFD_MAIN_PLANE,
		0,
		0,0,0
	};

	if((pixelformat = ChoosePixelFormat(m_pDC->GetSafeHdc(), &pfd )) == 0 ){
		AfxMessageBox(_T("在该DC上找不到于PFD接近的位图结构"));
		return FALSE;
	}
	
	int nRet = SetPixelFormat(m_pDC->GetSafeHdc(), pixelformat, &pfd);
	if ( nRet == FALSE)//测试硬件是否支持该pdf
    {
        AfxMessageBox(_T("无法在该DC上设置位图结构"));
        return FALSE;
    }

	//创建openGL设备环境
	m_hRC = wglCreateContext(m_pDC->GetSafeHdc());
	//将openGL设备环境设置成当前
	wglMakeCurrent(m_pDC->GetSafeHdc(),m_hRC);

	return TRUE;
}



/*
*	删除MFC渲染环境
*	在CView的OnDestroy()中调用释放资源
*/
BOOL BaseCompatGL::deleteContext(void){
	//释放RC以及DC
	if(wglGetCurrentContext()!=NULL) 
		::wglMakeCurrent(NULL,  NULL);
	if (m_hRC)
        ::wglDeleteContext(m_hRC);
	if (m_pDC)
        delete m_pDC;

	return TRUE;
}

/*
*	获取设备句柄
*/
CClientDC* BaseCompatGL::getClientDC(void){
	assert(m_pDC!=nullptr);
	return m_pDC;
}

/*
*	设置全背景色
*/
void BaseCompatGL::setBackgroundColor(GLfloat red, GLfloat green, GLfloat blue){
	m_backgroundColorTop = glm::vec3(red,green,blue);
	m_backgroundColorBottom = glm::vec3(red,green,blue);
}
/*
*	设置上方背景色
*/
void BaseCompatGL::setBackgroundColorTop(GLfloat red, GLfloat green, GLfloat blue){
	m_backgroundColorTop = glm::vec3(red,green,blue);
}
/*
*	设置下方背景色
*/
void BaseCompatGL::setBackgroundColorBottom(GLfloat red, GLfloat green, GLfloat blue){
	m_backgroundColorBottom = glm::vec3(red,green,blue);
}

/*
*	绘制背景
*/
void BaseCompatGL::drawBackground(void){
	//重置颜色缓存和深度缓存
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
*	OpenGL的初始化
*/
void BaseCompatGL::init(void){
	glClearColor(0.0f,0.0f,0.0f,1.0f);
	glEnable(GL_DEPTH_TEST);
	glClearDepth(1.0f);

	//初始化光照
	initLighting();
}

/*
*	置换双层缓存 
*	SwapBuffers的封装
*/
void BaseCompatGL::show(void){
	if( !m_pDC ){
		return;
	}
	SwapBuffers( m_pDC->GetSafeHdc() );
}

/*
*	初始化OpenGL的光照
*/
void BaseCompatGL::initLighting(void){
	GLfloat light_ambient[] = {0.0f,0.0f,0.0f,1.0f};	//ambient 环境光 
	GLfloat light_diffuse[] = {1.0f,1.0f,1.0f,1.0f};	//diffuse 漫反射光
	GLfloat light_specular[] = {1.0f,1.0f,1.0f,1.0f};	//specular 镜面反射光
	GLfloat light_shininess = 16;	//镜面系数

	glLightfv(GL_LIGHT0,GL_AMBIENT,light_ambient);
	glLightfv(GL_LIGHT0,GL_DIFFUSE,light_diffuse);
	glLightfv(GL_LIGHT0,GL_SPECULAR,light_specular);
	glLightf(GL_LIGHT0,GL_SHININESS,light_shininess);	

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);
	glShadeModel(GL_SMOOTH);
}