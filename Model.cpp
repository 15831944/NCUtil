#include "StdAfx.h"
#include "Model.h"


Model::Model(void)
{
}


Model::~Model(void)
{
}

/*
*	��ȡģ���еĵ�
*/
vector<glm::dvec3>& Model::getVertices(void){
	return m_vertices;
}

/*
*	����ģ�͵��еĵ�����
*/
void Model::setVertices(vector<glm::dvec3>& vertices){
	if( vertices.empty() ){
		return;
	}
	m_vertices.clear();
	m_vertices.resize( vertices.size() );
	memcpy( &m_vertices[0], &vertices[0], vertices.size()*sizeof(glm::dvec3) );
}