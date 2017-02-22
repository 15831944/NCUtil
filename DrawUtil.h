#pragma once

#include "BaseCompatGL.h"

#include "Model.h"

class DrawUtil: public BaseCompatGL
{
private:

public:
	DrawUtil(void);
	~DrawUtil(void);

	//Model m_model;
	//Model m_projectModel;

public:
	virtual void onDraw(void);
};

