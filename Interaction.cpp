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
*  ����������
*/
void Interaction::onLButtonDown(UINT nFlags, CPoint point){
	m_pointOld.x = point.x;
	m_pointOld.y = point.y;
}

/*
*	����ƶ�
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
*	����м�����
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