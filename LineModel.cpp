#include "stdafx.h"

#include "LineModel.h"

LineModel::LineModel(void)
{
	m_color = glm::vec3(1.0f,1.0f,1.0f);
}


LineModel::~LineModel(void)
{
}

/*
*	绘制模型
*/
void LineModel::draw(View& view){

	glDisable(GL_LIGHTING);

	view.viewToProjection();
	view.modelToView();

	glm::dvec3 vertex;
	
	glColor3fv(glm::value_ptr(m_color));
	glBegin(GL_LINE_STRIP);
		for(int i=0; i<m_vertices.size(); i++){
			vertex = m_vertices[i];
			glVertex3dv(glm::value_ptr(vertex));
		}
	glEnd();

	glEnable(GL_LIGHTING);
}

/*
*	设置颜色
*/
void LineModel::setColor(GLfloat red, GLfloat green, GLfloat blue){
	m_color = glm::vec3(red,green,blue);
}