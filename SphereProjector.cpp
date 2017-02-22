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
*	��ƽ��ͼ��ͶӰ(��ͼ)�������
*	@vertex ����ĵ�
*	return ת����ĵ�
*/
glm::dvec3 SphereProjector::onProject(glm::dvec3& vertex){

	glm::dvec3 vertexResult;
	//����
	double arcLength;
	//��λ��������
	glm::dvec3 directionVector;

	arcLength = glm::length( vertex - glm::dvec3(0) );
	directionVector = (vertex-glm::dvec3(0)) / arcLength;
		
	vertexResult.x = m_sphereRadius * sin( arcLength/m_sphereRadius ) * directionVector.x;
	vertexResult.y = m_sphereRadius * sin( arcLength/m_sphereRadius ) * directionVector.y;
	vertexResult.z = m_sphereRadius * cos( arcLength/m_sphereRadius );

	return vertexResult;
}