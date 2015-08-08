#include "TrackCamera.h"
#include <glm/gtc/matrix_transform.hpp>

TrackCamera::TrackCamera(void)
{
	glm::vec3 arrpoints[5] = {
			glm::vec3(-10, 5,	-10),
			glm::vec3(-10, 5,	10),
			glm::vec3(10, 5,	-10),
			glm::vec3(10, 5,	10),
			glm::vec3(-10, 5,	-10),
			/*glm::vec3(10,  1,	10),
			glm::vec3(10,  2,	-10),
			glm::vec3(-10,	3,	-10),
			glm::vec3(-10,	4,	10)*/
	};
	points = std::vector<glm::vec3>(0);
	for(int i = 0; i < 5; i++){
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
	if(progress > 1){
		progress = 0;
		for(int i = 0; i < 3; i++){
			currentPoints[i] = currentPoints[i+1];
		}
		currentPoints[3] = (currentPoints[2]+1)%points.size();
		int i = 0;
	}
	if(progress < 0){
		progress = 0;
	}
}
glm::mat4 TrackCamera::GetViewMatrix() const{



	glm::vec3 position = glm::cubic(
		points[currentPoints[3]],
		points[currentPoints[2]],
		points[currentPoints[1]],
		points[currentPoints[0]],
		progress);
	glm::vec3 p0 = glm::cubic(
		points[currentPoints[3]],
		points[currentPoints[2]],
		points[currentPoints[1]],
		points[currentPoints[0]],
		progress+0.2);
	glm::vec3 p2 = glm::cubic(
		points[currentPoints[3]],
		points[currentPoints[2]],
		points[currentPoints[1]],
		points[currentPoints[0]],
		progress-0.2);

	glm::vec3 tangent = p2-p0;
	return glm::lookAt(position, position-tangent, glm::vec3(0.0f, 1.0f, 0.0f));

}

