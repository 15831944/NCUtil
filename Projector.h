
#ifndef _PROJECTOR_H_
#define _PROJECTOR_H_

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include "Model.h"

class Projector
{
public:
	virtual ~Projector(void);

	// 将model的点投影到vertex缓存
	Projector& project(Model& model);
	Projector& project(Model* pModel);
	// 将vertex缓存中的点保存到另一个模型中
	void to(Model& model);
	void to(Model* pModel);
	// 设置偏移量
	void setOffset(double dx, double dy);
protected:
	Projector(void);

	// 点的投影 子类实现
	virtual glm::dvec3 onProject(glm::dvec3& vertex)=0;
	virtual void beforeProject(vector<glm::dvec3>& vertices);
	virtual void afterProject(vector<glm::dvec3>& vertices); 

private:
	
	//开关量
	bool m_bInterpolation;

	//vertex暂存
	vector<glm::dvec3> m_vertices;

	//偏移量
	glm::dvec3 m_offset;
};

#endif