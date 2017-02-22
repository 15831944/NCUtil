#include "StdAfx.h"
#include "ModelManager.h"


ModelManager::ModelManager(void)
{
}


ModelManager::~ModelManager(void)
{
	clear();
}

/*
*	添加模型
*/
void ModelManager::addModel(string modelName,Model* model){
	m_models[modelName] = model;
}

/*
*	删除模型
*/
void ModelManager::removeModel(string modelName){
	map<string,Model*>::iterator iter = m_models.find(modelName);
	if( iter!= m_models.end() ){
		m_models.erase(modelName);
		delete iter->second;
	}
}

/*
*	删除所有模型 释放内存
*/
void ModelManager::clear(void){
	for(map<string,Model*>::iterator iter = m_models.begin();  iter!=m_models.end(); ++iter){
		delete iter->second;
	}
	m_models.clear();
}

/*
*	绘制所有模型
*/
void ModelManager::drawModels(View& view){
	
	Model* pModel;

	for(map<string,Model*>::iterator iter = m_models.begin();  iter!=m_models.end(); ++iter){
		pModel = iter->second;
		pModel->draw(view);
	}
}