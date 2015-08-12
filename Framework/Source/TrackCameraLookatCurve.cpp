#include "TrackCameraLookatCurve.h"
#include <vector>

TrackCameraLookatCurve::TrackCameraLookatCurve(){

	const int numpoints = 8;
	glm::vec3 arrpoints[numpoints] = {
			glm::vec3(0,	5,		0),
			glm::vec3(0,	3,		1),
			glm::vec3(0,	0,		3),
			glm::vec3(0,	12,		4),
			glm::vec3(0,	15,		12),
			glm::vec3(0,	10,		0),
			glm::vec3(0,	-10,	0),
			glm::vec3(0,	0,		13)

	};
	
	std::vector<glm::vec3> points = std::vector<glm::vec3>(0);
	for(int i = 0; i < numpoints; i++){
		points.push_back(arrpoints[i]);
	}
	lookatCurve = new BSplineCurve(points);
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
