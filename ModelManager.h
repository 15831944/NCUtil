
#ifndef _MODELMANAGER_H_
#define _MODELMANAGER_H_

#include <map>
#include <string>
#include "Model.h"
#include "View.h"

using namespace std;

class ModelManager
{
public:
	ModelManager(void);
	~ModelManager(void);

	//添加模型
	void addModel(string modelName, Model* model);
	//删除指定名字的模型
	void removeModel(string modelName);
	//删除所有模型
	void clear(void);
	//绘制所有模型
	void drawModels(View& view);
protected:
	
private:
	map<string,Model*> m_models;
};

#endif