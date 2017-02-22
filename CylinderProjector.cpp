#include "StdAfx.h"
#include "CylinderProjector.h"


CylinderProjector::CylinderProjector(void)
{
	m_cylinderRadius = 80.0;
}


CylinderProjector::~CylinderProjector(void)
{
}

/*
*	继承父类的方法
*	将点投影到圆柱表面
*/
glm::dvec3 CylinderProjector::onProject(glm::dvec3& vertex){
	
	glm::dvec3 vertexResult;
	//弧长
	double arcLength;
	//单位方向向量
	glm::dvec3 directionVector;

	arcLength = glm::length( vertex - glm::dvec3(0) );
	directionVector = (vertex-glm::dvec3(0)) / arcLength;

	vertexResult.x = arcLength * directionVector.x;
	vertexResult.y = m_cylinderRadius * sin( arcLength * directionVector.y / m_cylinderRadius );
	vertexResult.z = m_cylinderRadius * cos( arcLength * directionVector.y / m_cylinderRadius );

	return vertexResult;
}