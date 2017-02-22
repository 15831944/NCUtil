#include "StdAfx.h"
#include "Interaction.h"

CPoint Interaction::m_pointOld;

Interaction::Interaction(void)
{
}


Interaction::~Interaction(void)
{
}

/*
*  鼠标左键按下
*/
void Interaction::onLButtonDown(UINT nFlags, CPoint point){
	m_pointOld.x = point.x;
	m_pointOld.y = point.y;
}

/*
*	鼠标移动
*/
void Interaction::onMouseMove(UINT nFlags, CPoint point, CWnd* pWnd, BaseCompatGL& baseGL, UINT translateFlags, UINT rotateFlags){
	if( nFlags == translateFlags ){
		GLfloat dx = point.x - m_pointOld.x;
		GLfloat dy = point.y - m_pointOld.y;
		CRect rect;
		pWnd->GetClientRect(&rect);
		baseGL.getView().translate(dx/rect.Width(),dy/rect.Height());

		m_pointOld = point;
	}else if( nFlags == rotateFlags ){
		GLfloat dx = point.x - m_pointOld.x;
		GLfloat dy = point.y - m_pointOld.y;
		CRect rect;
		pWnd->GetClientRect(&rect);
		baseGL.getView().rotate(dx/rect.Width(),dy/rect.Height());

		m_pointOld = point;
	}
}

/*
*	鼠标中键滚动
*/
void Interaction::onMouseWheel(UINT nFlags, short zDelta, CPoint point, CWnd* pWnd, BaseCompatGL& baseGL){
	CPoint clientPoint = point;
	pWnd->ScreenToClient(&clientPoint);
	CRect rect;
	pWnd->GetClientRect(&rect);
	if( rect.PtInRect(clientPoint) ){
		baseGL.getView().scale(clientPoint,zDelta);
	}
}