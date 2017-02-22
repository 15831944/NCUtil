
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
	//法向量数据缓存
	vector<glm::vec3> m_normals;
	//顶点数据缓存
	vector<glm::dvec3> m_vertices;
	//法向量索引
	vector<glm::uvec3> m_normalIndexes;
	//顶点索引
	vector<glm::uvec3> m_triangleIndexes;
	//颜色
	vector<glm::vec3> m_colors;
};

#endif