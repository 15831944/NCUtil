#include "StdAfx.h"
#include "ConeProjector.h"


ConeProjector::ConeProjector(void)
{
	//Բ׶����
	m_bottomRadius = 100.0;	//����뾶
	m_height = 100.0;	//��
}


ConeProjector::~ConeProjector(void)
{
}

/*
*	���ͶӰ
*/
glm::dvec3 ConeProjector::onProject(glm::dvec3& vertex){
	
	glm::dvec3 vertexResult;

	//�㵽���ĵľ���
	double arcLength;
	//��λ��������
	glm::dvec3 directionVector;

	arcLength = glm::length( vertex - glm::dvec3(0) );
	directionVector = (vertex-glm::dvec3(0)) / arcLength;

	//ĸ�߳���
	double generatrixLength = sqrt( m_bottomRadius*m_bottomRadius + m_height*m_height );
	//Բ׶��ǵ�sinֵ��cosֵ
	double sinHalfAngle = m_bottomRadius / generatrixLength;
	double cosHalfAngle = m_height / generatrixLength;

	vertexResult.x = arcLength * sinHalfAngle * directionVector.x;
	vertexResult.y = arcLength * sinHalfAngle * directionVector.y;
	vertexResult.z = m_height - arcLength * cosHalfAngle;

	return vertexResult;
}