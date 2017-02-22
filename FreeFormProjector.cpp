#include "StdAfx.h"
#include "FreeFormProjector.h"

#include "LineUtil.h"

#include <algorithm>

FreeFormProjector::FreeFormProjector(void)
{
}


FreeFormProjector::~FreeFormProjector(void)
{
}

/*
*	�Խ��㼯��������ĺ�������sort��������
*/
bool compare(const LineSegment& line1, const LineSegment& line2 ){
	return line1.length < line2.length;
}

/*
*	ͶӰǰ��Ԥ����
*	�̳и���ķ���
*/
void FreeFormProjector::beforeProject( vector<glm::dvec3>& vertices ){
	isBaseTriangleVertexCal = false;

	m_baseVertex = glm::dvec3( 0.0, 0.0, 0.0 );
}

/*
*	������������
*/
FreeFormProjector& FreeFormProjector::setBaseModel(TriangleModel* model){
	m_baseModel = model;
	return *this;
}

/*
*	ͶӰÿһ����
*	�̳и���ķ���
*/
glm::dvec3 FreeFormProjector::onProject( glm::dvec3& vertex ){

	glm::dvec3 vertexResult;

	//�㵽���ĵľ���
	double arcLength;
	// ԭ�㵽�õ������
	glm::dvec3 baseVector = vertex - glm::dvec3(0);
	//��λ��������
	glm::dvec3 directionVector;

	//���㼯
	vector<glm::dvec3> intersectPoints;
	//���㼯��Ӧ�ķ�����
	vector<glm::vec3> intersectNormals;

	arcLength = glm::length( baseVector );
	directionVector = glm::normalize( baseVector );
	
	vector<glm::dvec3> vertices = m_baseModel->getVertices();
	vector<glm::vec3> normals = m_baseModel->getNormals();
	vector<glm::uvec3> normalIndexes = m_baseModel->getNormalIndexes();
	vector<glm::uvec3> triangleIndexes = m_baseModel->getTriangleIndexes();
	unsigned int triangleCount = triangleIndexes.size();

	glm::uvec3 triangleIndex;
	glm::uvec3 normalIndex;
	glm::dvec3 vertex1;
	glm::dvec3 vertex2;
	glm::dvec3 vertex3;

	LineUtil lineUtil = LineUtil::getInstance();

	if( !isBaseTriangleVertexCal ){
		//�������ĵ��ͶӰ
		for( unsigned int i=0; i<triangleCount; ++i ){
			triangleIndex = triangleIndexes[i];
			vertex1 = vertices[ triangleIndex.x ];
			vertex2 = vertices[ triangleIndex.y ];
			vertex3 = vertices[ triangleIndex.z ];

			if( lineUtil.isPointInTriangle(m_baseVertex, vertex1, vertex2, vertex3) ){
					//�������ĵ�(ԭ��)���ڵ�������
				m_baseTriangleVertex1 = vertex1;
				m_baseTriangleVertex2 = vertex2;
				m_baseTriangleVertex3 = vertex3;
				m_baseTriangleNormal = normals[ normalIndexes[i].x ];
				isBaseTriangleVertexCal = true;

				m_baseTriangleVertex.x = m_baseVertex.x;
				m_baseTriangleVertex.y = m_baseVertex.y;
				m_baseTriangleVertex.z = ( m_baseTriangleNormal.x*(vertex1.x-m_baseVertex.x) + m_baseTriangleNormal.y*(vertex1.y-m_baseVertex.y) )/m_baseTriangleNormal.z+vertex1.z;
				break;
			}
		}
	}

	// ���㽻�㼯
	for(unsigned int i=0; i<triangleCount; ++i){
		triangleIndex = triangleIndexes[i];
		vertex1 = vertices[ triangleIndex.x ];
		vertex2 = vertices[ triangleIndex.y ];
		vertex3 = vertices[ triangleIndex.z ];

		
		if( lineUtil.isIntersect(m_baseVertex, vertex, vertex1,vertex2) ){
			intersectPoints.push_back( lineUtil.getIntersectPoint(m_baseVertex, vertex, vertex1,vertex2) );
			intersectNormals.push_back( normals[ normalIndexes[i].x ] );
		}
		if( lineUtil.isIntersect(m_baseVertex, vertex, vertex2,vertex3) ){
			intersectPoints.push_back( lineUtil.getIntersectPoint(m_baseVertex, vertex, vertex2,vertex3) );
			intersectNormals.push_back( normals[ normalIndexes[i].y ] );
		}
		if( lineUtil.isIntersect(m_baseVertex, vertex, vertex3,vertex1) ){
			intersectPoints.push_back( lineUtil.getIntersectPoint(m_baseVertex, vertex, vertex3,vertex1) );
			intersectNormals.push_back( normals[ normalIndexes[i].z ] );
		}
		
	}


	double arcLengthLeft = arcLength;
	vector<double> lengths;
	vector<double> tempLengths;
	vector<LineSegment> intersectVertex;
	LineSegment segment;
	//�����ĵ����ڵ�������
	if( intersectPoints.empty() ){
		
		glm::dvec3 tempVector = glm::dvec3( directionVector.y, -directionVector.x, 0.0 );
			double tempProjLength = glm::dot( m_baseTriangleNormal, tempVector );
			tempVector = m_baseTriangleNormal - tempProjLength * tempVector;
			tempVector = glm::normalize( tempVector );
			// ���
			vertexResult = m_baseTriangleVertex + baseVector - glm::dot( baseVector, tempVector ) * tempVector;
	}else{
		
		lengths.resize( intersectPoints.size() );
		tempLengths.resize( intersectPoints.size() );
		intersectVertex.resize( intersectPoints.size() );
		for( unsigned int i=0; i<intersectPoints.size(); ++i ){
			lengths[i] =  glm::length(intersectPoints[i] - m_baseTriangleVertex);
			tempLengths[i] = glm::length(intersectPoints[i] - m_baseTriangleVertex);
			segment.length = lengths[i];
			segment.vertex = intersectPoints[i];
			intersectVertex[i] = segment;
		}

		sort( intersectVertex.begin(), intersectVertex.end(), compare); 
		
		for( unsigned int i=0; i<lengths.size(); ++i ){
			if( i==0 ){
				arcLengthLeft = arcLengthLeft - glm::length( intersectVertex[0].vertex - m_baseTriangleVertex );
			}else{
				arcLengthLeft = arcLengthLeft - glm::length( intersectVertex[i].vertex - intersectVertex[i-1].vertex );
			}
			if( arcLengthLeft<=0.0 ){
				double t;
				if( i==0 ){
					arcLengthLeft = arcLengthLeft +  glm::length( intersectVertex[0].vertex - m_baseTriangleVertex );
					t = arcLengthLeft / glm::length( intersectVertex[0].vertex - m_baseTriangleVertex );
					vertexResult = m_baseTriangleVertex + (intersectVertex[0].vertex - m_baseTriangleVertex) * t;
				}else {
					arcLengthLeft = arcLengthLeft +  glm::length( intersectVertex[i].vertex - intersectVertex[i-1].vertex );
					t = arcLengthLeft / glm::length( intersectVertex[i].vertex - intersectVertex[i-1].vertex );
					vertexResult = intersectVertex[i-1].vertex + (intersectVertex[i].vertex - intersectVertex[i-1].vertex) * t;
				} 
				break;
			}
		}
	}

	return vertexResult;
}