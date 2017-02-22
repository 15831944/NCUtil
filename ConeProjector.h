
#ifndef _CONEPROJECTOR_H_
#define _CONEPROJECTOR_H_

#include "Projector.h"

class ConeProjector : public Projector
{
public:
	ConeProjector(void);
	virtual ~ConeProjector(void);

protected:
	//点的投影
	virtual glm::dvec3 onProject(glm::dvec3& vertex);

private:

	//圆锥的底面半径
	double m_bottomRadius;
	//圆锥的高度
	double m_height;
};

#endif
