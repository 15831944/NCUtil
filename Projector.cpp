#include "StdAfx.h"
#include "Projector.h"

#include "LineUtil.h"

Projector::Projector(void)
{
	//开关量默认值
	m_bInterpolation = true; //默认进行插值
	//偏移量
	m_offset = glm::dvec3(0.0,0.0,0.0);
}


Projector::~Projector(void)
{
}

/*
*	将model的点
*	细分 -> 投影(子类实现) -> 保存到vertex缓存
*	@model 原始模型
*/
Projector& Projector::project(Model& model){
	//清空vertex的缓存
	m_vertices.clear();

	//投影前的预处理
	beforeProject(model.getVertices());

	long vertexCount = model.getVertices().size();
	glm::dvec3 vertex;
	glm::dvec3 vertexResult;

	if( m_bInterpolation ){
		vector<glm::dvec3> vertexList; //一条线段的所有插值点
		glm::dvec3 vertexBegin;
		glm::dvec3 vertexEnd;

		for( long i=0; i<vertexCount-1; ++i ){
			vertexBegin = model.getVertices()[i];
			vertexEnd = model.getVertices()[i+1];
			if( i<vertexCount-2 ){
				LineUtil::getInstance().interpolateLine(vertexBegin,vertexEnd,vertexList,false);
			}else{
				LineUtil::getInstance().interpolateLine(vertexBegin,vertexEnd,vertexList);
			}
			for( int j=0; j<vertexList.size(); j++ ){
				vertex = vertexList[j];
				//具体的Projector子类实现
				vertexResult = onProject(vertex + m_offset);

				m_vertices.push_back(vertexResult);
			}
		}
	}else{
		for( long i=0; i<vertexCount; i++ ){
			vertex = model.getVertices()[i];
			//具体的Projector子类实现
			vertexResult = onProject(vertex + m_offset);

			m_vertices.push_back(vertexResult);
		}
	}

	//投影后的处理
	afterProject(model.getVertices());

	return *this;
}
Projector& Projector::project(Model* pModel){
	return project(*pModel);
}

/*
*	将vertex缓存的点保存到另外一个模型model中
*/
void Projector::to(Model& model){
	model.setVertices(m_vertices);
}
void Projector::to(Model* pModel){
	pModel->setVertices(m_vertices);
}

/*
*	设置偏移量
*/
void Projector::setOffset(double dx, double dy){
	m_offset.x = dx;
	m_offset.y = dy;
}

/*
*	在投影之前的预处理
*	子类实现
*/
void Projector::beforeProject(vector<glm::dvec3>& vertices){

}

/*
*	在投影之后的处理
*	子类实现
*/
void Projector::afterProject(vector<glm::dvec3>& vertices){
	
}