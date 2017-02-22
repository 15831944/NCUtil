
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

	//��ȡ������ģ���еĵ�����
	vector<glm::dvec3>& getVertices(void);
	void setVertices(vector<glm::dvec3>& vertices);
	//ģ�͵Ļ���
	//����ʵ��
	virtual void draw(View& view)=0;

protected:

	//ģ���еĵ�����
	vector<glm::dvec3> m_vertices;
	
private:
};

#endif