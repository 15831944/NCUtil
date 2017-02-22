
#ifndef _LINEUTIL_H_
#define _LINEUTIL_H_

#include <glm/glm.hpp>
#include <vector>
using namespace std;

class LineUtil
{
public:
	~LineUtil(void);
	//����
	static LineUtil& getInstance(void);
	//��һ���߶ν��в�ֵ
	void interpolateLine(const glm::dvec3 vertex, const glm::dvec3 vertexNext, vector<glm::dvec3>& verticesResult, bool hasEnd = true);

	// �������Ĵ�С
	double cross(const double p1, double p2, const double p3, double p4);
	double cross(const glm::dvec2& vector1, const glm::dvec2& vector2);
	double cross(const glm::dvec3& vector1, const glm::dvec3& vector2, bool isTwoDimension = true);

	// �ж������߶��Ƿ��ཻ
	bool isIntersect(const glm::dvec3& p1, const glm::dvec3& p2, const glm::dvec3& p3, const glm::dvec3& p4);
	// ����ڶ���ֱ�� ���һ��ֱ��������ֱƽ�� �Ľ���
	glm::dvec3 getIntersectPoint( glm::dvec3& p1, glm::dvec3& p2, glm::dvec3& p3, glm::dvec3& p4 );
	// �жϵ��Ƿ�����������
	bool isPointInTriangle(glm::dvec3& point, glm::dvec3& vextex1, glm::dvec3& vertex2, glm::dvec3& vertex3);

protected:
	LineUtil(void);

private:

	// ��ֵ���
	double m_interval;
};

#endif