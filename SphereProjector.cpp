#include "StdAfx.h"
#include "SphereProjector.h"


SphereProjector::SphereProjector(void)
{
	m_sphereRadius = 100.0;
}


SphereProjector::~SphereProjector(void)
{
}

/*
*	将平面图形投影(贴图)到球表面
*	@vertex 输入的点
*	return 转换后的点
*/
glm::dvec3 SphereProjector::onProject(glm::dvec3& vertex){

	glm::dvec3 vertexResult;
	//弧长
	double arcLength;
	//单位方向向量
	glm::dvec3 directionVector;

	arcLength = glm::length( vertex - glm::dvec3(0) );
	directionVector = (vertex-glm::dvec3(0)) / arcLength;
		
	vertexResult.x = m_sphereRadius * sin( arcLength/m_sphereRadius ) * directionVector.x;
	vertexResult.y = m_sphereRadius * sin( arcLength/m_sphereRadius ) * directionVector.y;
	vertexResult.z = m_sphereRadius * cos( arcLength/m_sphereRadius );

	return vertexResult;
}