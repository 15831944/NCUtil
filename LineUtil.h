
#ifndef _LINEUTIL_H_
#define _LINEUTIL_H_

#include <glm/glm.hpp>
#include <vector>
using namespace std;

class LineUtil
{
public:
	~LineUtil(void);
	//单例
	static LineUtil& getInstance(void);
	//对一条线段进行插值
	void interpolateLine(const glm::dvec3 vertex, const glm::dvec3 vertexNext, vector<glm::dvec3>& verticesResult, bool hasEnd = true);

	// 计算叉积的大小
	double cross(const double p1, double p2, const double p3, double p4);
	double cross(const glm::dvec2& vector1, const glm::dvec2& vector2);
	double cross(const glm::dvec3& vector1, const glm::dvec3& vector2, bool isTwoDimension = true);

	// 判断两条线段是否相交
	bool isIntersect(const glm::dvec3& p1, const glm::dvec3& p2, const glm::dvec3& p3, const glm::dvec3& p4);
	// 计算第二条直线 与第一条直线所在竖直平面 的交点
	glm::dvec3 getIntersectPoint( glm::dvec3& p1, glm::dvec3& p2, glm::dvec3& p3, glm::dvec3& p4 );
	// 判断点是否在三角形内
	bool isPointInTriangle(glm::dvec3& point, glm::dvec3& vextex1, glm::dvec3& vertex2, glm::dvec3& vertex3);

protected:
	LineUtil(void);

private:

	// 插值间隔
	double m_interval;
};

#endif