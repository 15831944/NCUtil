#include "StdAfx.h"
#include "Projector.h"

#include "LineUtil.h"

Projector::Projector(void)
{
	//������Ĭ��ֵ
	m_bInterpolation = true; //Ĭ�Ͻ��в�ֵ
	//ƫ����
	m_offset = glm::dvec3(0.0,0.0,0.0);
}


Projector::~Projector(void)
{
}

/*
*	��model�ĵ�
*	ϸ�� -> ͶӰ(����ʵ��) -> ���浽vertex����
*	@model ԭʼģ��
*/
Projector& Projector::project(Model& model){
	//���vertex�Ļ���
	m_vertices.clear();

	//ͶӰǰ��Ԥ����
	beforeProject(model.getVertices());

	long vertexCount = model.getVertices().size();
	glm::dvec3 vertex;
	glm::dvec3 vertexResult;

	if( m_bInterpolation ){
		vector<glm::dvec3> vertexList; //һ���߶ε����в�ֵ��
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
				//�����Projector����ʵ��
				vertexResult = onProject(vertex + m_offset);

				m_vertices.push_back(vertexResult);
			}
		}
	}else{
		for( long i=0; i<vertexCount; i++ ){
			vertex = model.getVertices()[i];
			//�����Projector����ʵ��
			vertexResult = onProject(vertex + m_offset);

			m_vertices.push_back(vertexResult);
		}
	}

	//ͶӰ��Ĵ���
	afterProject(model.getVertices());

	return *this;
}
Projector& Projector::project(Model* pModel){
	return project(*pModel);
}

/*
*	��vertex����ĵ㱣�浽����һ��ģ��model��
*/
void Projector::to(Model& model){
	model.setVertices(m_vertices);
}
void Projector::to(Model* pModel){
	pModel->setVertices(m_vertices);
}

/*
*	����ƫ����
*/
void Projector::setOffset(double dx, double dy){
	m_offset.x = dx;
	m_offset.y = dy;
}

/*
*	��ͶӰ֮ǰ��Ԥ����
*	����ʵ��
*/
void Projector::beforeProject(vector<glm::dvec3>& vertices){

}

/*
*	��ͶӰ֮��Ĵ���
*	����ʵ��
*/
void Projector::afterProject(vector<glm::dvec3>& vertices){
	
}