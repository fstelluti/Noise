#include "TrackCamera.h"
#include <glm/gtc/matrix_transform.hpp>

TrackCamera::TrackCamera(void)
{
	glm::vec3 arrpoints[8] = {
			glm::vec3(0,	5,	0),
			glm::vec3(0,	5,	13),
			glm::vec3(10,	5,	19),
			glm::vec3(10,	10,	10),
			glm::vec3(15,	15,	13),
			glm::vec3(0,	5,	10),
			glm::vec3(10,	5,	10),
			glm::vec3(10,	10,	10)
	};
	points = std::vector<glm::vec3>(0);
	for(int i = 0; i < 8; i++){
		points.push_back(arrpoints[i]);
	}

	for(int i = 0; i < 4; i++){
		currentPoints[i] = i;
	}

}


TrackCamera::~TrackCamera(void)
{

}

void TrackCamera::Update(float dt){
	progress+=0.001;//dt*0.1;
	if(progress >= 1){
		progress = 0;
		currentPoints[0] = currentPoints[3];
		for(int i = 1; i < 4; i++){
			currentPoints[i] = (currentPoints[0] + i)%points.size();// currentPoints[i+1];
		}
		//currentPoints[3] = (currentPoints[2]+3)%points.size();
		int i = 0;
	}
	if(progress < 0){
		progress = 0;
	}
}
glm::mat4 TrackCamera::GetViewMatrix() const{

	glm::vec3 position = GetPosition(
		points[currentPoints[0]],
		points[currentPoints[1]],
		points[currentPoints[2]],
		points[currentPoints[3]],
		progress);

	glm::vec3 tangent = GetTangent(
		points[currentPoints[0]],
		points[currentPoints[1]],
		points[currentPoints[2]],
		points[currentPoints[3]],
		progress);
	return glm::lookAt(position, position+tangent /*glm::vec3(0)*/, glm::vec3(0.0f, 1.0f, 0.0f));

}

glm::vec3 TrackCamera::GetPosition(glm::vec3 v1,glm::vec3 v2, glm::vec3 v3, glm::vec3 v4, float p) const{
	 return glm::mix(
		v1,
		v4,
		p);
}

glm::vec3 TrackCamera::GetTangent(glm::vec3 v1,glm::vec3 v2, glm::vec3 v3, glm::vec3 v4, float p) const{
	return GetPosition(v1, v2, v3, v4, p + 0.05) - GetPosition(v1, v2, v3, v4, p - 0.05);
}