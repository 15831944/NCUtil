#include "StdAfx.h"
#include "ConeProjector.h"


ConeProjector::ConeProjector(void)
{
	//圆锥参数
	m_bottomRadius = 100.0;	//底面半径
	m_height = 100.0;	//高
}


ConeProjector::~ConeProjector(void)
{
}

/*
*	点的投影
*/
glm::dvec3 ConeProjector::onProject(glm::dvec3& vertex){
	
	glm::dvec3 vertexResult;

	//点到中心的距离
	double arcLength;
	//单位方向向量
	glm::dvec3 directionVector;

	arcLength = glm::length( vertex - glm::dvec3(0) );
	directionVector = (vertex-glm::dvec3(0)) / arcLength;

	//母线长度
	double generatrixLength = sqrt( m_bottomRadius*m_bottomRadius + m_height*m_height );
	//圆锥半角的sin值和cos值
	double sinHalfAngle = m_bottomRadius / generatrixLength;
	double cosHalfAngle = m_height / generatrixLength;

	vertexResult.x = arcLength * sinHalfAngle * directionVector.x;
	vertexResult.y = arcLength * sinHalfAngle * directionVector.y;
	vertexResult.z = m_height - arcLength * cosHalfAngle;

	return vertexResult;
}