#include "StdAfx.h"
#include "ObjParser.h"

#include <fstream>
#include "TextUtils.h"

ObjParser::ObjParser(void)
{
}


ObjParser::~ObjParser(void)
{
}


/*
*	解析.obj文件
*	数据保存在数据缓存中
*/
ObjParser& ObjParser::parse(string filePath){

	m_vertices.clear();
	m_normals.clear();
	m_triangleIndexes.clear();
	m_normalIndexes.clear();
	m_colors.clear();


	int fileNamePosition = filePath.find_last_of("/");
	int fileDotPosition = filePath.find_last_of(".");
	
	//文件名字
	string fileName = filePath.substr( fileNamePosition+1 );
	//文件路径
	string pathName = filePath.substr( 0, fileNamePosition );
	//文件扩展名
	string fileExtName = filePath.substr( fileDotPosition+1 );
	//文件除去扩展名的 名称
	string fileSelfName = filePath.substr( fileNamePosition+1, fileDotPosition-fileNamePosition-1 );

	if( fileExtName.compare("obj") != 0 ){
		return *this;
	}

	string mtlFilePath = pathName + "/" + fileSelfName + "." + "mtl";


	//打开mtl文件
	ifstream mtlIfstream(mtlFilePath,ios::in);
	//mtl文件不存在
	if( !mtlIfstream ){
		return *this;
	}

	string line;
	string colorName;
	float red, green ,blue;
	map<string, glm::vec3> colorMap;

	while( !mtlIfstream.eof() ){
		getline(mtlIfstream,line);
		
		if( line.substr(0,6).compare("newmtl") == 0 ){

			string strNoMtl = line.substr(6);
			//材质的名称
			colorName = TextUtils::trim( strNoMtl );
		}else if( line.substr(0,2).compare("Kd") == 0 ){
			sscanf(line.c_str(), "Kd %f %f %f", &red, &green, &blue );
			colorMap[colorName] = glm::vec3(red,green,blue);
		}
	}
	//关闭mtl文件
	mtlIfstream.close();


	string currentColorName;
	glm::dvec3 vertex;	//顶点数据
	glm::vec3 normal;	//法向量数据
	glm::uvec3 vertexIndex;
	glm::uvec3 normalIndex;

	bool hasVertexTexture = false;
	bool hasVertexNormal = false;

	//打开.obj文件
	ifstream objIfstream(filePath);
	if( !objIfstream ){
		return *this;
	}

	while( !objIfstream.eof() ){
		getline(objIfstream, line);

		if( line.substr(0,2).compare("vn") == 0 ){
			//法向量数据
			hasVertexNormal = true;
			sscanf( line.c_str(), "vn %f %f %f", &normal.x, &normal.y, &normal.z );
			m_normals.push_back( normal );
		}else if( line.substr(0,2).compare("vt") == 0 ){
			hasVertexTexture = true;
			//纹理坐标数据
		}else if( line.substr(0,1).compare("v") == 0 ){
			//顶点数据
			sscanf( line.c_str(), "v %lf %lf %lf", &vertex.x, &vertex.y, &vertex.z );
			m_vertices.push_back( vertex );
		}else if( line.substr(0,6).compare("usemtl") == 0 ){
			//颜色 应用
			currentColorName = line.substr(7);
		}else if( line.substr(0,1).compare("f") == 0 ){
			//面数据
			if( hasVertexTexture ){
				sscanf( line.c_str(), "f %u/%*u/%u %u/%*u/%u %u/%*u/%u",
					&vertexIndex.x, &normalIndex.x,
					&vertexIndex.y, &normalIndex.y,
					&vertexIndex.z, &normalIndex.z );
			}else{
				sscanf( line.c_str(), "f %u//%u %u//%u %u//%u",
					&vertexIndex.x, &normalIndex.x,
					&vertexIndex.y, &normalIndex.y,
					&vertexIndex.z, &normalIndex.z );
			}
			m_triangleIndexes.push_back( vertexIndex - glm::uvec3(1) );
			m_normalIndexes.push_back( normalIndex - glm::uvec3(1) );
			
			map<string,glm::vec3>::iterator currentColorIterator;
			currentColorIterator = colorMap.find( currentColorName );
			m_colors.push_back( currentColorIterator->second );
		}
	}

	objIfstream.close();

	return *this;
}

/*
*	将顶点数据、法向量数据、顶点索引、法向量索引、颜色 
*	保存在TriangleModel中
*/

void ObjParser::to(TriangleModel& model){
	model.setVertices( m_vertices );
	model.setTriangleIndexes( m_triangleIndexes );
	model.setNormals( m_normals );
	model.setNormalIndexes( m_normalIndexes );
	model.setColors( m_colors );
}

void ObjParser::to(TriangleModel* model){
	to(*model);
}
