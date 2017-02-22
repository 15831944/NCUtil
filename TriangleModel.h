
#ifndef _TRIANGLEMODEL_H_
#define _TRIANGLEMODEL_H_

#include "Model.h"

#include "View.h"

#include <glm/glm.hpp>
#include <vector>
using namespace std;

class TriangleModel : public Model
{
public:
	TriangleModel(void);
	virtual ~TriangleModel(void);

	// 模型的绘制
	// 继承父类的方法
	virtual void draw(View& view);

	// 设置顶点数据、法向量数据、顶点索引、法向量索引、颜色
	void setNormals( vector<glm::vec3>& normals );
	void setTriangleIndexes( vector<glm::uvec3>& triangleIndexes );
	void setNormalIndexes( vector<glm::uvec3>& normalIndexes );
	void setColors( vector<glm::vec3>& colors );
	// 获取顶点数据、法向量数据、顶点索引、法向量索引、颜色
	vector<glm::vec3>& getNormals(void);
	vector<glm::uvec3>& getTriangleIndexes(void);
	vector<glm::uvec3>& getNormalIndexes(void);
protected:

private:
	
	//三角形三个顶点的索引
	vector<glm::uvec3> m_triangleIndexes;
	//法向量数据
	vector<glm::vec3> m_normals;
	//法向量索引 (三角形三个顶点)
	vector<glm::uvec3> m_normalIndexes;
	//颜色
	vector<glm::vec3> m_colors;
};

#endif