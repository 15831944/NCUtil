#include "stdafx.h"
#include "DxfParser.h"

#include <fstream>

DxfParser::DxfParser(void)
{
	//������ �Ƿ����ڶ�ȡ�ö���
	m_bHeader = false;
	m_bClasses = false;
	m_bTables = false;
	m_bBlocks = false;
	m_bEntities = false;
	m_bObjects = false;
	//ʵ���־ �Ƿ����ڶ���ʵ�������
	m_bPOINT = false;
	m_bLWPOLYLINE = false;
	m_bSPLINE = false;
	m_bPOLYLINE = false;

	m_sLine = "";
	m_iGroupCode = 0;

	//���ÿ���
	m_bCenter = false;
}


DxfParser::~DxfParser(void)
{
}

DxfParser& DxfParser::parse(string filePath){

	//���vertex����
	m_vertices.clear();

	double x;	//x����
	double y;	//y����

	ifstream inputFileStream;
	inputFileStream.open(filePath, ifstream::in);

	while( getline(inputFileStream,m_sLine) ){
		//����
		m_iGroupCode = atoi(m_sLine.c_str());
		getline(inputFileStream,m_sLine);
		switch(m_iGroupCode){
			case 0:
				//Section�Ŀ�ʼ �� ʵ�����͵Ŀ�ʼ
				if( m_sLine.compare("SECTION") == 0 ){
					//Section��ʼ
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
					//Section����
					m_bHeader = false;
					m_bClasses = false;
					m_bTables = false;
					m_bBlocks = false;
					m_bEntities = false;
					m_bObjects = false;
				}else if( m_sLine.compare("POINT") == 0 ){
					//POINTʵ�忪ʼ
					setParsingEntity(m_bPOINT);
				}else if(m_sLine.compare("LWPOLYLINE") == 0 ){
					//LWPOLYLINEʵ�忪ʼ
					setParsingEntity(m_bLWPOLYLINE);
				}else if(m_sLine.compare("SPLINE") == 0 ){
					//SPLINEʵ�忪ʼ
					setParsingEntity(m_bSPLINE);
				}else if(m_sLine.compare("POLYLINE") == 0 ){
					setParsingEntity(m_bPOLYLINE);
				}
				break;
			case 10:
				if( m_bEntities ){
					//��ʵ�����
					if( m_bPOINT ){
						//POINTʵ��ĵ�����
						x = atof(m_sLine.c_str());
						getline(inputFileStream,m_sLine);
						getline(inputFileStream,m_sLine);
						y = atof(m_sLine.c_str());
						m_vertices.push_back( glm::dvec3(x,y,0.0) );

						setMinMax( glm::dvec3(x,y,0.0) );
					}else if( m_bLWPOLYLINE ){
						//LWPOLYLINEʵ��ĵ�����
						x = atof(m_sLine.c_str());
						getline(inputFileStream,m_sLine);
						getline(inputFileStream,m_sLine);
						y = atof(m_sLine.c_str());
						m_vertices.push_back( glm::dvec3(x,y,0.0) );

						setMinMax( glm::dvec3(x,y,0.0) );
					}else if( m_bSPLINE ){
						//SPLINEʵ��ĵ�����
						x = atof(m_sLine.c_str());
						getline(inputFileStream,m_sLine);
						getline(inputFileStream,m_sLine);
						y = atof(m_sLine.c_str());
						m_vertices.push_back( glm::dvec3(x,y,0.0) );

						setMinMax( glm::dvec3(x,y,0.0) );
					}else if( m_bPOLYLINE ){
						//POLYLINEʵ��ĵ�����
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

	//ͼ������
	m_center = glm::dvec3( 0.5*(m_xMin+m_xMax), 0.5*(m_yMin+m_yMax), 0.5*(m_zMin+m_zMax) );

	if( m_bCenter ){
		//ƽ�Ƶ���ԭ��Ϊ����
		for(int i=0; i<m_vertices.size(); i++){
			m_vertices[i] -= m_center;
		}
	}

	return *this;
}

/*
*	��������ĵ��ŵ�ģ������
*/
void DxfParser::to(Model& model){
	model.setVertices(m_vertices);
}
void DxfParser::to(Model* pModel){
	pModel->setVertices(m_vertices);
}
/*
*	�ӽ������ĵ��л�ȡ������Сֵ�����ֵ
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
*	�Ƿ�ͼ���ƶ�����ԭ��Ϊ����
*/
DxfParser& DxfParser::configCenter(bool bCenter){
	m_bCenter = bCenter;
	return *this;
}

/*
*	��ʶ���ڶ�ȡ��ʵ��
*/
void DxfParser::setParsingEntity(bool& bEntity){
	m_bPOINT = false;
	m_bLWPOLYLINE = false;
	m_bSPLINE = false;
	m_bPOLYLINE = false;

	bEntity = true;
}