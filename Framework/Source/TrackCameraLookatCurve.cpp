#include "TrackCameraLookatCurve.h"
#include <vector>

TrackCameraLookatCurve::TrackCameraLookatCurve(){

	const int numpoints = 16;
	glm::vec3 arrpoints[numpoints] = {
			glm::vec3(0,	5,		0),
			glm::vec3(0,	3,		1),
			glm::vec3(0,	0,		3),
			glm::vec3(0,	12,		4),
			glm::vec3(0,	15,		12),
			glm::vec3(0,	10,		0),
			glm::vec3(0,	-10,	0),
			glm::vec3(0,	0,		13),
			glm::vec3(0,	5,		0),
			glm::vec3(0,	3,		1),
			glm::vec3(0,	0,		3),
			glm::vec3(0,	12,		4),
			glm::vec3(0,	15,		12),
			glm::vec3(0,	10,		0),
			glm::vec3(0,	-10,	0),
			glm::vec3(0,	0,		13)

	};
	glm::vec3 arrpoints2[numpoints] = {
			glm::vec3(64,	12,		4),
			glm::vec3(2,	0,		13),
			glm::vec3(32,	5,		75),
			glm::vec3(33,	3,		1),
			glm::vec3(14,	0,		3),
			glm::vec3(21,	15,		12),
			glm::vec3(31,	10,		0),
			glm::vec3(31,	-10,	0),
			glm::vec3(51,	5,		23),
			glm::vec3(15,	3,		23),
			glm::vec3(23,	0,		64),
			glm::vec3(64,	12,		0),
			glm::vec3(0,	15,		-64),
			glm::vec3(-64,	10,		0),
			glm::vec3(0,	-10,	64),
			glm::vec3(64,	0,		0)
	};	
	std::vector<glm::vec3> lookatpoints		= std::vector<glm::vec3>(0);
	std::vector<glm::vec3> positionpoints	= std::vector<glm::vec3>(0);

	for(int i = 0; i < numpoints; i++){
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
