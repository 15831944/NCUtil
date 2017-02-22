#include "StdAfx.h"
#include "TriangleModel.h"


TriangleModel::TriangleModel(void)
{
}


TriangleModel::~TriangleModel(void)
{

}

/*
*	设置顶点数据、法向量数据、顶点索引、法向量索引、颜色
*/
void TriangleModel::setNormals( vector<glm::vec3>& normals ){
	if( normals.empty() ){
		return;
	}
	m_normals.clear();
	m_normals.resize( normals.size() );
	memcpy( &m_normals[0], &normals[0], normals.size()*sizeof(glm::vec3) );
}

void TriangleModel::setTriangleIndexes( vector<glm::uvec3>& triangleIndexes ){
	if( triangleIndexes.empty() ){
		return;
	}
	m_triangleIndexes.clear();
	m_triangleIndexes.resize( triangleIndexes.size() );
	memcpy( &m_triangleIndexes[0], &triangleIndexes[0], triangleIndexes.size()*sizeof(glm::uvec3) );
}

void TriangleModel::setNormalIndexes( vector<glm::uvec3>& normalIndexes ){
	if( normalIndexes.empty() ){
		return;
	}
	m_normalIndexes.clear();
	m_normalIndexes.resize( normalIndexes.size() );
	memcpy( &m_normalIndexes[0], &normalIndexes[0], normalIndexes.size()*sizeof(glm::uvec3) );
}

void TriangleModel::setColors( vector<glm::vec3>& colors ){
	if( colors.empty() ){
		return;
	}
	m_colors.clear();
	m_colors.resize( colors.size() );
	memcpy( &m_colors[0], &colors[0], colors.size()*sizeof(glm::vec3) );
}

/*
*	获取顶点数据、法向量数据、顶点索引、法向量索引、颜色
*/
vector<glm::vec3>& TriangleModel::getNormals(void){
	return m_normals;
}

vector<glm::uvec3>& TriangleModel::getTriangleIndexes(void){
	return m_triangleIndexes;
}

vector<glm::uvec3>& TriangleModel::getNormalIndexes(void){
	return m_normalIndexes;
}

/*
*	绘制函数
*	继承父类的方法
*/
void TriangleModel::draw( View& view ){
	
	glEnable(GL_LIGHTING);

	view.viewToProjection();
	view.modelToView();

	glm::dvec3 vertex;
	glm::vec3 normal;
	glm::uvec3 triangleIndex;
	glm::uvec3 normalIndex;
	glm::vec3 color;

	glBegin(GL_TRIANGLES);
	for( unsigned int i=0; i<m_triangleIndexes.size(); ++i ){
		triangleIndex = m_triangleIndexes[i];
		normalIndex = m_normalIndexes[i];

		vertex = m_vertices[ triangleIndex.x ];
		normal = m_normals[ normalIndex.x ];
		color = m_colors[ i ];

		glColor3fv( glm::value_ptr(color) );
		glNormal3fv( glm::value_ptr(normal) );
		glVertex3dv( glm::value_ptr(vertex) );

		vertex = m_vertices[ triangleIndex.y ];
		normal = m_normals[ normalIndex.y ];

		glNormal3fv( glm::value_ptr(normal) );
		glVertex3dv( glm::value_ptr(vertex) );

		vertex = m_vertices[ triangleIndex.z ];
		normal = m_normals[ normalIndex.z ];

		glNormal3fv( glm::value_ptr(normal) );
		glVertex3dv( glm::value_ptr(vertex) );

	}
	glEnd();
}