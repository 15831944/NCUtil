
#ifndef _OBJPARSER_H_
#define _OBJPARSER_H_

#include "TriangleModel.h"

#include <string>
#include <map>
using namespace std;


class ObjParser
{
public:
	ObjParser(void);
	~ObjParser(void);

	ObjParser& parse(string filePath);
	void to(TriangleModel& model);
	void to(TriangleModel* model);

protected:


private:
	//���������ݻ���
	vector<glm::vec3> m_normals;
	//�������ݻ���
	vector<glm::dvec3> m_vertices;
	//����������
	vector<glm::uvec3> m_normalIndexes;
	//��������
	vector<glm::uvec3> m_triangleIndexes;
	//��ɫ
	vector<glm::vec3> m_colors;
};

#endif