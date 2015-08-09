#include "TrackCamera.h"
#include <glm/gtc/matrix_transform.hpp>



TrackCamera::TrackCamera(void)
{
	glm::vec3 arrpoints[8] = {
			glm::vec3(5,	5,	5),
			glm::vec3(10,	5,	11),
			glm::vec3(20,	5,	22),
			glm::vec3(30,	10,	33),
			glm::vec3(15,	15,	13),
			glm::vec3(0,	5,	10),
			glm::vec3(10,	5,	10),
			glm::vec3(10,	10,	10)
	};
	std::vector<glm::vec3>	points = std::vector<glm::vec3>(0);
	for(int i = 0; i < 8; i++){
		points.push_back(arrpoints[i]);
	}

	curve = new LinearCurve(points);
}


TrackCamera::~TrackCamera(void)
{

}

void TrackCamera::Update(float dt){
	progress+=0.001;//dt*0.1;
	if(progress >= 1){
		progress = 0;
		curve->nextPoint();
	}
	if(progress < 0){
		progress = 0;
	}
}
glm::mat4 TrackCamera::GetViewMatrix() const{

	glm::vec3 position = GetPosition(progress);

	glm::vec3 tangent = GetTangent(progress);
	return glm::lookAt(position, position+tangent /*glm::vec3(0)*/, glm::vec3(0.0f, 1.0f, 0.0f));

}

glm::vec3 TrackCamera::GetPosition(float t) const{
	
	return curve->getPosition(t);
	/*return glm::mix(
		points[currentPoints[0]],
		points[currentPoints[3]],
		t);*/
}

glm::vec3 TrackCamera::GetTangent(float t) const{
	return curve->getTangent(t);
}


