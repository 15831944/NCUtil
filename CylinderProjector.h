
#ifndef _CYLINDERPROJECTOR_H_
#define _CYLINDERPROJECTOR_H_

#include "Projector.h"

class CylinderProjector : public Projector
{
public:
	CylinderProjector(void);
	virtual ~CylinderProjector(void);

protected:
	//继承父类方法，将点投影到圆柱表面
	virtual glm::dvec3 onProject(glm::dvec3& vertex);
private:
	
	GLdouble m_cylinderRadius;
};

#endif
