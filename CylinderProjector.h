
#ifndef _CYLINDERPROJECTOR_H_
#define _CYLINDERPROJECTOR_H_

#include "Projector.h"

class CylinderProjector : public Projector
{
public:
	CylinderProjector(void);
	virtual ~CylinderProjector(void);

protected:
	//�̳и��෽��������ͶӰ��Բ������
	virtual glm::dvec3 onProject(glm::dvec3& vertex);
private:
	
	GLdouble m_cylinderRadius;
};

#endif
