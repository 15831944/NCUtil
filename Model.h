
#ifndef _MODEL_H_
#define _MODEL_H_

#include "View.h"

#include <vector>
#include <glm/glm.hpp>
using namespace std;

class Model
{
public:
	Model(void);
	virtual ~Model(void);

	//获取和设置模型中的点数据
	vector<glm::dvec3>& getVertices(void);
	void setVertices(vector<glm::dvec3>& vertices);
	//模型的绘制
	//子类实现
	virtual void draw(View& view)=0;

protected:

	//模型中的点数据
	vector<glm::dvec3> m_vertices;
	
private:
};

#endif