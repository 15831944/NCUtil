#include "StdAfx.h"
#include "Model.h"


Model::Model(void)
{
}


Model::~Model(void)
{
}

/*
*	获取模型中的点
*/
vector<glm::dvec3>& Model::getVertices(void){
	return m_vertices;
}

/*
*	设置模型当中的点数据
*/
void Model::setVertices(vector<glm::dvec3>& vertices){
	if( vertices.empty() ){
		return;
	}
	m_vertices.clear();
	m_vertices.resize( vertices.size() );
	memcpy( &m_vertices[0], &vertices[0], vertices.size()*sizeof(glm::dvec3) );
}