
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

	// ��model�ĵ�ͶӰ��vertex����
	Projector& project(Model& model);
	Projector& project(Model* pModel);
	// ��vertex�����еĵ㱣�浽��һ��ģ����
	void to(Model& model);
	void to(Model* pModel);
	// ����ƫ����
	void setOffset(double dx, double dy);
protected:
	Projector(void);

	// ���ͶӰ ����ʵ��
	virtual glm::dvec3 onProject(glm::dvec3& vertex)=0;
	virtual void beforeProject(vector<glm::dvec3>& vertices);
	virtual void afterProject(vector<glm::dvec3>& vertices); 

private:
	
	//������
	bool m_bInterpolation;

	//vertex�ݴ�
	vector<glm::dvec3> m_vertices;

	//ƫ����
	glm::dvec3 m_offset;
};

#endif