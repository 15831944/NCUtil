
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

	// ģ�͵Ļ���
	// �̳и���ķ���
	virtual void draw(View& view);

	// ���ö������ݡ����������ݡ�������������������������ɫ
	void setNormals( vector<glm::vec3>& normals );
	void setTriangleIndexes( vector<glm::uvec3>& triangleIndexes );
	void setNormalIndexes( vector<glm::uvec3>& normalIndexes );
	void setColors( vector<glm::vec3>& colors );
	// ��ȡ�������ݡ����������ݡ�������������������������ɫ
	vector<glm::vec3>& getNormals(void);
	vector<glm::uvec3>& getTriangleIndexes(void);
	vector<glm::uvec3>& getNormalIndexes(void);
protected:

private:
	
	//�������������������
	vector<glm::uvec3> m_triangleIndexes;
	//����������
	vector<glm::vec3> m_normals;
	//���������� (��������������)
	vector<glm::uvec3> m_normalIndexes;
	//��ɫ
	vector<glm::vec3> m_colors;
};

#endif