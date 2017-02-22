
#ifndef _FREEFORMPROJECTOR_H_
#define _FREEFORMPROJECTOR_H_

#include "Projector.h"
#include "TriangleModel.h"

#include <vector>
using namespace std;

struct LineSegment {
	double length;
	glm::dvec3 vertex;
};

class FreeFormProjector : public Projector
{
public:
	FreeFormProjector(void);
	virtual ~FreeFormProjector(void);

	FreeFormProjector& setBaseModel( TriangleModel* );

protected:
	//ͶӰǰ�� Ԥ����	(�̳и���ķ���)
	virtual void beforeProject( vector<glm::dvec3>& vertices );
	// ͶӰÿһ����		(�̳и���ķ���)
	virtual glm::dvec3 onProject( glm::dvec3& vertex );

private:
	// �������� (ͶӰ��������������
	TriangleModel* m_baseModel;

	//���㻺��
	vector<glm::dvec3> m_vertices;

	//���ĵ��������Ƿ��Ѿ�����
	bool isBaseTriangleVertexCal;
	//���ĵ�������λ���
	glm::dvec3 m_baseTriangleVertex1;
	glm::dvec3 m_baseTriangleVertex2;
	glm::dvec3 m_baseTriangleVertex3;
	//���ĵ�������η�����
	glm::dvec3 m_baseTriangleNormal;

	glm::dvec3 m_baseTriangleVertex;
	glm::dvec3 m_baseVertex;

	//bool compare( const LineSegment& line1, const LineSegment& line2 ); 
};

#endif
