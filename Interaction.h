/*
*	应用于MFC的OpenGL视图交互类
*/

#ifndef _INTERACTION_H_
#define _INTERACTION_H_

#include "BaseCompatGL.h"

class Interaction
{
public:
	Interaction(void);
	~Interaction(void);

	static void onLButtonDown(UINT nFlags, CPoint point);
	static void onMouseMove(UINT nFlags, CPoint point, CWnd* pWnd, BaseCompatGL& baseGL,UINT translateFlags=(MK_LBUTTON|MK_SHIFT),UINT rotateFlags=MK_LBUTTON|MK_CONTROL );
	static void onMouseWheel(UINT nFlags, short zDelta, CPoint point,  CWnd* pWnd, BaseCompatGL& baseGL);
	
protected:


private:
	static CPoint m_pointOld;
};


#endif

