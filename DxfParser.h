
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

	//dxf文件解析
	DxfParser& parse(string filePath);
	//解析后的点存放到模型类中
	void to(Model& model);
	void to(Model* pModel);

	//配置相关
	//是否将图形移动到以原点为中心
	DxfParser& configCenter(bool bCenter);

protected:

private:
	//段落标记 是否正在读取该段落
	bool m_bHeader;
	bool m_bClasses;
	bool m_bTables;
	bool m_bBlocks;
	bool m_bEntities;
	bool m_bObjects;
	//实体标志 是否正在读该实体的坐标
	bool m_bPOINT;
	bool m_bLWPOLYLINE;
	bool m_bSPLINE;
	bool m_bPOLYLINE;

	//正在读取的行
	string m_sLine;
	//正在读取的组码
	int m_iGroupCode;

	vector<glm::dvec3> m_vertices;
	// 坐标的最大最小值
	GLdouble m_xMin;
	GLdouble m_xMax;
	GLdouble m_yMin;
	GLdouble m_yMax;
	GLdouble m_zMin;
	GLdouble m_zMax;
	glm::dvec3 m_center;
	//设定最大最小值
	void setMinMax(glm::dvec3& vertex);
	//标识正在读取的实体
	void setParsingEntity(bool& bEntity);

	//点的处理  配置开关
	bool m_bCenter;
};

#endif