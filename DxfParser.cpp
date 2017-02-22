#include "stdafx.h"
#include "DxfParser.h"

#include <fstream>

DxfParser::DxfParser(void)
{
	//段落标记 是否正在读取该段落
	m_bHeader = false;
	m_bClasses = false;
	m_bTables = false;
	m_bBlocks = false;
	m_bEntities = false;
	m_bObjects = false;
	//实体标志 是否正在读该实体的坐标
	m_bPOINT = false;
	m_bLWPOLYLINE = false;
	m_bSPLINE = false;
	m_bPOLYLINE = false;

	m_sLine = "";
	m_iGroupCode = 0;

	//配置开关
	m_bCenter = false;
}


DxfParser::~DxfParser(void)
{
}

DxfParser& DxfParser::parse(string filePath){

	//清空vertex缓存
	m_vertices.clear();

	double x;	//x坐标
	double y;	//y坐标

	ifstream inputFileStream;
	inputFileStream.open(filePath, ifstream::in);

	while( getline(inputFileStream,m_sLine) ){
		//组码
		m_iGroupCode = atoi(m_sLine.c_str());
		getline(inputFileStream,m_sLine);
		switch(m_iGroupCode){
			case 0:
				//Section的开始 或 实体类型的开始
				if( m_sLine.compare("SECTION") == 0 ){
					//Section开始
					getline(inputFileStream,m_sLine);
					getline(inputFileStream,m_sLine);
					if( m_sLine.compare("HEADER") == 0 ){
						m_bHeader = true;
					}else if( m_sLine.compare("CLASSES") == 0 ){
						m_bClasses = true;
					}else if( m_sLine.compare("TABLES") == 0 ){
						m_bTables = true;
					}else if( m_sLine.compare("BLOCKS") == 0 ){
						m_bBlocks = true;
					}else if( m_sLine.compare("ENTITIES") == 0 ){
						m_bEntities = true;
					}else if( m_sLine.compare("OBJECTS") == 0 ){
						m_bObjects = true;
					}
				}else if( m_sLine.compare("ENDSEC") == 0 ){
					//Section结束
					m_bHeader = false;
					m_bClasses = false;
					m_bTables = false;
					m_bBlocks = false;
					m_bEntities = false;
					m_bObjects = false;
				}else if( m_sLine.compare("POINT") == 0 ){
					//POINT实体开始
					setParsingEntity(m_bPOINT);
				}else if(m_sLine.compare("LWPOLYLINE") == 0 ){
					//LWPOLYLINE实体开始
					setParsingEntity(m_bLWPOLYLINE);
				}else if(m_sLine.compare("SPLINE") == 0 ){
					//SPLINE实体开始
					setParsingEntity(m_bSPLINE);
				}else if(m_sLine.compare("POLYLINE") == 0 ){
					setParsingEntity(m_bPOLYLINE);
				}
				break;
			case 10:
				if( m_bEntities ){
					//在实体段中
					if( m_bPOINT ){
						//POINT实体的点坐标
						x = atof(m_sLine.c_str());
						getline(inputFileStream,m_sLine);
						getline(inputFileStream,m_sLine);
						y = atof(m_sLine.c_str());
						m_vertices.push_back( glm::dvec3(x,y,0.0) );

						setMinMax( glm::dvec3(x,y,0.0) );
					}else if( m_bLWPOLYLINE ){
						//LWPOLYLINE实体的点坐标
						x = atof(m_sLine.c_str());
						getline(inputFileStream,m_sLine);
						getline(inputFileStream,m_sLine);
						y = atof(m_sLine.c_str());
						m_vertices.push_back( glm::dvec3(x,y,0.0) );

						setMinMax( glm::dvec3(x,y,0.0) );
					}else if( m_bSPLINE ){
						//SPLINE实体的点坐标
						x = atof(m_sLine.c_str());
						getline(inputFileStream,m_sLine);
						getline(inputFileStream,m_sLine);
						y = atof(m_sLine.c_str());
						m_vertices.push_back( glm::dvec3(x,y,0.0) );

						setMinMax( glm::dvec3(x,y,0.0) );
					}else if( m_bPOLYLINE ){
						//POLYLINE实体的点坐标
						x = atof(m_sLine.c_str());
						getline(inputFileStream,m_sLine);
						getline(inputFileStream,m_sLine);
						y = atof(m_sLine.c_str());
						m_vertices.push_back( glm::dvec3(x,y,0.0) );

						setMinMax( glm::dvec3(x,y,0.0) );
					}
				}
				break;
			default:
				break;
		}
	}	

	//图形中心
	m_center = glm::dvec3( 0.5*(m_xMin+m_xMax), 0.5*(m_yMin+m_yMax), 0.5*(m_zMin+m_zMax) );

	if( m_bCenter ){
		//平移到以原点为中心
		for(int i=0; i<m_vertices.size(); i++){
			m_vertices[i] -= m_center;
		}
	}

	return *this;
}

/*
*	将解析后的点存放到模型类中
*/
void DxfParser::to(Model& model){
	model.setVertices(m_vertices);
}
void DxfParser::to(Model* pModel){
	pModel->setVertices(m_vertices);
}
/*
*	从解析到的点中获取坐标最小值和最大值
*/
void DxfParser::setMinMax(glm::dvec3& vertex){
	static bool bFirst = true; 
	if( bFirst ){
		m_xMin = vertex.x;
		m_xMax = vertex.x;
		m_yMin = vertex.y;
		m_yMax = vertex.y;
		m_zMin = vertex.z;
		m_zMax = vertex.z;
		bFirst = false;
	}else{
		m_xMin = min( m_xMin, vertex.x );
		m_xMax = max( m_xMax, vertex.x );
		m_yMin = min( m_yMin, vertex.y );
		m_yMax = max( m_yMax, vertex.y );
		m_zMin = min( m_zMin, vertex.z );
		m_zMax = max( m_zMax, vertex.z );
	}
}

/*
*	是否将图形移动到以原点为中心
*/
DxfParser& DxfParser::configCenter(bool bCenter){
	m_bCenter = bCenter;
	return *this;
}

/*
*	标识正在读取的实体
*/
void DxfParser::setParsingEntity(bool& bEntity){
	m_bPOINT = false;
	m_bLWPOLYLINE = false;
	m_bSPLINE = false;
	m_bPOLYLINE = false;

	bEntity = true;
}