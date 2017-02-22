
#ifndef _SPHEREPORJECTOR_H_
#define _SPHEREPORJECTOR_H_

#include <glm/glm.hpp>
#include <vector>
#include "Model.h"
#include "Projector.h"

class SphereProjector : public Projector
{
public:
	SphereProjector(void);
	virtual ~SphereProjector(void);

protected:
	virtual glm::dvec3 onProject(glm::dvec3& vertex);
private:
	GLdouble m_sphereRadius;
};

#endif