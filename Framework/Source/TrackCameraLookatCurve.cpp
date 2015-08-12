#include "TrackCameraLookatCurve.h"
#include <vector>

TrackCameraLookatCurve::TrackCameraLookatCurve(){

	const int numLookat = 13;
	glm::vec3 arrpoints[numLookat] = {
			glm::vec3(32,	5,		0),
			glm::vec3(0,	3,		1),
			glm::vec3(0,	0,		3),
			glm::vec3(12,	12,		4),
			glm::vec3(0,	15,		12),
			glm::vec3(0,	10,		0),
			glm::vec3(51,	-10,	0),
			glm::vec3(0,	0,		13),
			glm::vec3(2,	5,		0),
			glm::vec3(15,	3,		1),
			glm::vec3(23,	0,		3),
			glm::vec3(0,	12,		4),
			glm::vec3(0,	15,		12),


	};
	const int numpoints = 17;
	glm::vec3 arrpoints2[numpoints] = {
			glm::vec3(64,	12,		4),
			glm::vec3(2,	-5,		13),
			glm::vec3(-32,	15,		75),
			glm::vec3(0,	75,		0),
			glm::vec3(0,	66,		3),
			glm::vec3(-21,	15,		-12),
			glm::vec3(-31,	10,		0),
			glm::vec3(15,	20,	0),
			glm::vec3(-1,	5,		23),
			glm::vec3(-15,	3,		23),
			glm::vec3(23,	0,		64),
			glm::vec3(64,	12,		0),
			glm::vec3(0,	15,		-64),
			glm::vec3(-64,	10,		0),
			glm::vec3(0,	-10,	64),
			glm::vec3(64,	0,		0),
			glm::vec3(0,	20,		-64),

	};	
	std::vector<glm::vec3> lookatpoints		= std::vector<glm::vec3>(0);
	std::vector<glm::vec3> positionpoints	= std::vector<glm::vec3>(0);

	for(int i = 0; i < numLookat; i++){
		lookatpoints.push_back(arrpoints[i]);
	}
	for(int i = 0; i < numpoints; i++){
		positionpoints.push_back(arrpoints2[i]);
	}
	lookatCurve = new BSplineCurve(lookatpoints);
	setPoints(positionpoints);
}

TrackCameraLookatCurve::~TrackCameraLookatCurve(){
}


glm::vec3 TrackCameraLookatCurve::GetFocusPoint(float t) const{
	return  lookatCurve->getPosition(t);
}

void TrackCameraLookatCurve::nextPoint(){
	lookatCurve->nextPoint();
	TrackCamera::nextPoint();
}
