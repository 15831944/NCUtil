
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

	//模型的绘制
	//继承父类的方法
	virtual void draw(View& view);
	//设置总体颜色
	void setColor(GLfloat red,GLfloat green, GLfloat blue);
protected:

private:
	//模型的总体颜色
	glm::vec3 m_color;
};

#endif
