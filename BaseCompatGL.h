
/*
*	导入MFC相关库
*/

/**
*	created on 2017-1-1
*	author 张岳文
*
*	opengl 辅助类	
*	应用于MFC
*/


#ifndef _BASECOMPATGL_H_
#define _BASECOMPATGL_H_

#include <windef.h>
#include <afxwin.h>
#include <glm/glm.hpp>

#include "View.h"
#include "ModelManager.h"

class BaseCompatGL{

public:

	BaseCompatGL(void);
	~BaseCompatGL(void);

	/*
	*	在MFC的CView类中创建OpenGL渲染环境	
	*
	*	在MFC中的View类必须定义
	*	HGLRC	m_hRC;	 
	*	CClientDC*	m_pDC;
	*	并作为参数传入
	*/
	BOOL createContext(CView* pView);
	BOOL deleteContext(void);

	// 获取设备句柄进行绘制
	CClientDC* getClientDC(void);
	// 获取视图交互类
	View& getView(void);

	//设置背景颜色
	void setBackgroundColor(GLfloat red, GLfloat green, GLfloat blue);
	void setBackgroundColorTop(GLfloat red, GLfloat green, GLfloat blue);
	void setBackgroundColorBottom(GLfloat red, GLfloat green, GLfloat blue);

	//OpenGL的相关初始化
	void init(void);

	// 绘制方法， 由子类具体实现
	void draw(void);
	virtual void onDraw(void) = 0;
protected:

	//视图，管理模型的坐标变换
	View m_view;
	//模型管理容器
	ModelManager modelManager;

	//绘制背景
	void drawBackground(void);
	//置换双缓存 SwapBuffers()
	void show(void);

private:

	//OpenGL绘制的视图窗口类
	CView* m_pView;

	HGLRC m_hRC;
	CClientDC* m_pDC;

	glm::vec3 m_backgroundColorTop;
	glm::vec3 m_backgroundColorBottom;

	//初始化光照
	void initLighting(void);
};




#endif