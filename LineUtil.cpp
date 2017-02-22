#include "StdAfx.h"
#include "LineUtil.h"


LineUtil::LineUtil(void)
{
	m_interval = 5.0;
}


LineUtil::~LineUtil(void)
{
}
/*
*	单例
*/
LineUtil& LineUtil::getInstance(void){
	static LineUtil m_instance;
	return m_instance;
}

/*
*	在线段的两点之间插值
*/
void LineUtil::interpolateLine(const glm::dvec3 vertex, const glm::dvec3 vertexNext, vector<glm::dvec3>& verticesResult,bool hasEnd){
	// 线段向量
	glm::dvec3 lineVector = vertexNext - vertex;
	// 线段长度
	double length = glm::length( lineVector );
	// 插值段数
	double interpolateCount = ceil( length/m_interval );
	
	verticesResult.clear();

	glm::dvec3 innerVertex;
	for(double i=0; i<interpolateCount; ++i){
		innerVertex = vertex + i/interpolateCount * lineVector;
		verticesResult.push_back(innerVertex);
	}
	if( hasEnd ){
		verticesResult.push_back(vertexNext);
	}
}

/*
*	计算两个向量的叉积的大小
*/
double LineUtil::cross(const double p1, const double p2, const double p3, const double p4){
	return ( p1 * p4 - p2 * p3 );
}

double LineUtil::cross(const glm::dvec2& vector1, const glm::dvec2& vector2){
	return cross( vector1.x, vector1.y, vector2.x, vector2.y );
}

double LineUtil::cross(const glm::dvec3& vector1, const glm::dvec3& vector2, bool isTwoDimension){
	if( isTwoDimension ){
		return cross( vector1.x, vector1.y, vector2.x, vector2.y );
	}else{
		return 0;
	}
}

/*
*	判断两条线段是否相交
*/
bool LineUtil::isIntersect(const glm::dvec3& p1, const glm::dvec3& p2, const glm::dvec3& p3, const glm::dvec3& p4){

	//延长100倍
	glm::dvec3 longP2 = p1 + 100.0 * (p2 - p1);

	glm::dvec3 vector1 = p3 - p1;
	glm::dvec3 vector2 = longP2 - p1;
	glm::dvec3 vector3 = p4 - p1;
	glm::dvec3 vector4 = -vector1;
	glm::dvec3 vector5 = p4 - p3;
	glm::dvec3 vector6 = longP2 - p3;

	double c1 = cross(vector1, vector2);
	double c2 = cross(vector3, vector2);
	if( c1*c2 > 0.0 || (c1+c2) == 0.0 ){
		return false;
	}
	double c3 = cross(vector4, vector5);
	double c4 = cross(vector6, vector5);
	if( c3*c4 > 0.0 ){
		return false;
	}
	return true;
}

/*
*	计算第二条直线 与第一条直线所在竖直平面 的交点
*/
glm::dvec3 LineUtil::getIntersectPoint( glm::dvec3& p1, glm::dvec3& p2, glm::dvec3& p3, glm::dvec3& p4 ){

	glm::dvec3 vertexResult;
	/*就是两条线段的交点
	double tempNum1 = p4.x * p3.y - p3.x * p4.y;
	double tempNum2 = p2.x * p1.y - p1.x * p2.y;
	double den = ( ( p1.x - p2.x ) * ( p3.y - p4.y ) - ( p3.x - p4.x ) * ( p1.y - p2.y ) );
	vertexResult.x = ( tempNum1*(p1.x-p2.x) - tempNum2*(p3.x-p4.x) ) / den;
	vertexResult.y = ( tempNum1*(p1.y-p2.y) - tempNum2*(p3.y-p4.y) ) / den;
	*/
	glm::dvec3 baseVector = p2 - p1;
	// 平面法向量
	glm::dvec3 faceNormal = glm::dvec3( baseVector.y, -baseVector.x, 0.0 );
	// 平面上一点 p1
	// 直线上一点 p3
	// 直线向量
	glm::dvec3 lineVector = p4 - p3;

	double den = glm::dot( faceNormal, lineVector );
	if( den == 0.0 ){
		return glm::dvec3(0.0);
	}
	double t = glm::dot( faceNormal, p1-p3 ) / den;
	//结果
	vertexResult = p3 + lineVector * t;
	return vertexResult;
}

/*
*	判断点是否在三角形内
*/
bool LineUtil::isPointInTriangle(glm::dvec3& point, glm::dvec3& vertex1, glm::dvec3& vertex2, glm::dvec3& vertex3){
	
	glm::dvec2 v0 = glm::dvec2( vertex3 ) - glm::dvec2( vertex1 );
	glm::dvec2 v1 = glm::dvec2( vertex2 ) - glm::dvec2( vertex1 );
	glm::dvec2 v2 = glm::dvec2( point ) - glm::dvec2( vertex1 );

	double dot00 = glm::dot(v0,v0);
	double dot01 = glm::dot(v0,v1);
	double dot02 = glm::dot(v0,v2);
	double dot11 = glm::dot(v1,v1);
	double dot12 = glm::dot(v1,v2);

	double den = dot00 * dot11 - dot01 * dot01;

	double u = (dot11 * dot02 - dot01 * dot12) / den;
	if( u<0 || u>1 ){
		return false;
	}

	double v = (dot00 * dot12 - dot01 * dot02) / den;
	if( v<0 || v>1 ){
		return false;
	}
	return (u+v) <= 1.0;
}