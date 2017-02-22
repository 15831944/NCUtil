
#ifndef _CONEPROJECTOR_H_
#define _CONEPROJECTOR_H_

#include "Projector.h"

class ConeProjector : public Projector
{
public:
	ConeProjector(void);
	virtual ~ConeProjector(void);

protected:
	//���ͶӰ
	virtual glm::dvec3 onProject(glm::dvec3& vertex);

private:

	//Բ׶�ĵ���뾶
	double m_bottomRadius;
	//Բ׶�ĸ߶�
	double m_height;
};

#endif
