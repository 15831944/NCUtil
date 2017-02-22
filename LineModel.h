
#ifndef _LINEMODEL_H_
#define _LINEMODEL_H_

#include "View.h"
#include "Model.h"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>
using namespace std;

class LineModel : public Model
{
public:
	LineModel(void);
	virtual ~LineModel(void);

	//ģ�͵Ļ���
	//�̳и���ķ���
	virtual void draw(View& view);
	//����������ɫ
	void setColor(GLfloat red,GLfloat green, GLfloat blue);
protected:

private:
	//ģ�͵�������ɫ
	glm::vec3 m_color;
};

#endif
