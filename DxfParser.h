
#ifndef _DXFPARSER_H_
#define _DXFPARSER_H_

#include <glm/glm.hpp>
#include "Model.h"

#include <string>
#include <vector>
using namespace std;

class DxfParser
{

public:
	DxfParser(void);
	~DxfParser(void);

	//dxf�ļ�����
	DxfParser& parse(string filePath);
	//������ĵ��ŵ�ģ������
	void to(Model& model);
	void to(Model* pModel);

	//�������
	//�Ƿ�ͼ���ƶ�����ԭ��Ϊ����
	DxfParser& configCenter(bool bCenter);

protected:

private:
	//������ �Ƿ����ڶ�ȡ�ö���
	bool m_bHeader;
	bool m_bClasses;
	bool m_bTables;
	bool m_bBlocks;
	bool m_bEntities;
	bool m_bObjects;
	//ʵ���־ �Ƿ����ڶ���ʵ�������
	bool m_bPOINT;
	bool m_bLWPOLYLINE;
	bool m_bSPLINE;
	bool m_bPOLYLINE;

	//���ڶ�ȡ����
	string m_sLine;
	//���ڶ�ȡ������
	int m_iGroupCode;

	vector<glm::dvec3> m_vertices;
	// ����������Сֵ
	GLdouble m_xMin;
	GLdouble m_xMax;
	GLdouble m_yMin;
	GLdouble m_yMax;
	GLdouble m_zMin;
	GLdouble m_zMax;
	glm::dvec3 m_center;
	//�趨�����Сֵ
	void setMinMax(glm::dvec3& vertex);
	//��ʶ���ڶ�ȡ��ʵ��
	void setParsingEntity(bool& bEntity);

	//��Ĵ���  ���ÿ���
	bool m_bCenter;
};

#endif