#include "StdAfx.h"
#include "DrawUtil.h"

#include "ObjectUtil.h"
#include "DxfParser.h"
#include "SphereProjector.h"
#include "CylinderProjector.h"
#include "ConeProjector.h"
#include "Axies.h"

#include "LineModel.h"
#include "TriangleModel.h"
#include "ObjParser.h"
#include "FreeFormProjector.h"

DrawUtil::DrawUtil(void)
{
	getView().setOrtho(-3.0f,3.0f,-3.0f,3.0f,1.0f,1000000.0f);
	getView().setLookAt(10000.0f,-45.0f,45.0f);

	DxfParser parser;
	LineModel* model = new LineModel();
	LineModel* projectModel = new LineModel();
	
	parser.configCenter(true).parse("C:/Users/smallpi/Downloads/20160306/jinbao.dxf").to( model );
	/*SphereProjector projector;
	projector.project(*model).to(*projectModel);*/
	//CylinderProjector projector;
	//projector.project(model).to(projectModel);
	//ConeProjector projector;
	//projector.setOffset(0.0,-80.0);
	//projector.project(model).to(projectModel);
	/*modelManager.addModel("dxfModel",model);
	modelManager.addModel("dxfProjectModel",projectModel);
	projectModel->setColor(1.0f,0.0f,0.0f);*/

	TriangleModel* testModel = new TriangleModel();
	ObjParser objParser;
	objParser.parse("C:/Users/smallpi/Desktop/custom.obj").to( testModel );
	modelManager.addModel("objModel",testModel);
	modelManager.addModel("lineModel",model);
	model->setColor(0.0f,1.0f,1.0f);
	FreeFormProjector fProjector;
	fProjector.setBaseModel( testModel ).project( model ).to( projectModel );
	modelManager.addModel("fProjectModel",projectModel);
	projectModel->setColor(1.0f,0.0f,0.0f);
}


DrawUtil::~DrawUtil(void)
{
}

void DrawUtil::onDraw(void){
	
	
	
	/*
	glColor3f(1.0f,1.0f,1.0f);
	m_model.draw(getView());
	glColor3f(1.0f,1.0f,0.0f);
	m_projectModel.draw(getView());
	*/
	modelManager.drawModels(getView());

	Axies::drawAxies(getView());
	Axies::drawSmallAxies(getView());
}
