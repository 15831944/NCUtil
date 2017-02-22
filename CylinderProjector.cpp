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
*	�̳и���ķ���
*	����ͶӰ��Բ������
*/
glm::dvec3 CylinderProjector::onProject(glm::dvec3& vertex){
	
	glm::dvec3 vertexResult;
	//����
	double arcLength;
	//��λ��������
	glm::dvec3 directionVector;

	arcLength = glm::length( vertex - glm::dvec3(0) );
	directionVector = (vertex-glm::dvec3(0)) / arcLength;

	vertexResult.x = arcLength * directionVector.x;
	vertexResult.y = m_cylinderRadius * sin( arcLength * directionVector.y / m_cylinderRadius );
	vertexResult.z = m_cylinderRadius * cos( arcLength * directionVector.y / m_cylinderRadius );

	return vertexResult;
}