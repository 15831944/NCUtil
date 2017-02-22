
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
	//投影前的 预处理	(继承父类的方法)
	virtual void beforeProject( vector<glm::dvec3>& vertices );
	// 投影每一个点		(继承父类的方法)
	virtual glm::dvec3 onProject( glm::dvec3& vertex );

private:
	// 自由曲面 (投影到该自由曲面上
	TriangleModel* m_baseModel;

	//顶点缓存
	vector<glm::dvec3> m_vertices;

	//中心点三角形是否已经缓存
	bool isBaseTriangleVertexCal;
	//中心点的三角形缓存
	glm::dvec3 m_baseTriangleVertex1;
	glm::dvec3 m_baseTriangleVertex2;
	glm::dvec3 m_baseTriangleVertex3;
	//中心点的三角形法向量
	glm::dvec3 m_baseTriangleNormal;

	glm::dvec3 m_baseTriangleVertex;
	glm::dvec3 m_baseVertex;

	//bool compare( const LineSegment& line1, const LineSegment& line2 ); 
};

#endif
