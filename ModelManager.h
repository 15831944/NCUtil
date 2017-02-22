
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

	//���ģ��
	void addModel(string modelName, Model* model);
	//ɾ��ָ�����ֵ�ģ��
	void removeModel(string modelName);
	//ɾ������ģ��
	void clear(void);
	//��������ģ��
	void drawModels(View& view);
protected:
	
private:
	map<string,Model*> m_models;
};

#endif