#include "TrackCamera.h"
#include <glm/gtc/matrix_transform.hpp>
#include "EventManager.h"
#include <GLFW/glfw3.h>



TrackCamera::TrackCamera(void)
{
	type = 2;
	setCurveType(bspline);
}


void TrackCamera::setCurveType(int t){
	
	if (t == 2){
		const int numPoints = 6;
		glm::vec3 arrpoints[numPoints] = {
				glm::vec3(0,	5,	-32),
				glm::vec3(-32, 20, 0),
				glm::vec3(0,	5,	32),
				glm::vec3(32,	12,  0),
				glm::vec3(0, 20, 0),
				glm::vec3(32,	0,	0)

		};

		std::vector<glm::vec3>	points = std::vector<glm::vec3>(0);
		for(int i = 0; i < numPoints; i++){
			points.push_back(arrpoints[i]);
		}

		curve = new BSplineCurve(points);
	}
	else if (t == 1){
		const int numPoints = 4;
		glm::vec3 arrpoints[numPoints] = {
				glm::vec3(0,	5,	-50),
				glm::vec3(100,	0,	0),
				glm::vec3(0,	5,	50),
				glm::vec3(-100,	0,  0)

		};

		std::vector<glm::vec3>	points = std::vector<glm::vec3>(0);
		for(int i = 0; i < numPoints; i++){
			points.push_back(arrpoints[i]);
		}

		curve = new HermiteCurve(points);
	}

	else if(t == 0){
		const int numPoints = 4;
		glm::vec3 arrpoints[numPoints] = {
				glm::vec3(4,	5,	21),
				glm::vec3(32,	40,	21),
				glm::vec3(22,	13,	24),
				glm::vec3(15,	16,  32)
		};

		std::vector<glm::vec3>	points = std::vector<glm::vec3>(0);
		for(int i = 0; i < numPoints; i++){
			points.push_back(arrpoints[i]);
		}

		curve = new LinearCurve(points);
	}
}

void TrackCamera::setPoints(std::vector<glm::vec3> points){
	curve->setPoints(points);
}



TrackCamera::~TrackCamera(void)
{

}

void TrackCamera::Update(float dt){

	EventManager::EnableMouseCursor();

	progress+= dt*0.1 * (EventManager::GetCurrentVolume()*10);

	if(progress >= 1){
		progress = 0;
		nextPoint();
	}
	if(progress < 0){
		progress = 0;
	}

	static bool five_pressed = 1;
	if(glfwGetKey(EventManager::GetWindow(), GLFW_KEY_5) == GLFW_PRESS && !five_pressed){
		five_pressed = 1;
		type = (type+1) % 3;
		setCurveType(type);
	}
	if(glfwGetKey(EventManager::GetWindow(), GLFW_KEY_5) == GLFW_RELEASE){
		five_pressed = 0;
	}
}
void TrackCamera::nextPoint(){
	curve->nextPoint();
}
glm::mat4 TrackCamera::GetViewMatrix() const{

	glm::vec3 position = GetPosition(progress);

	glm::vec3 tangent = GetTangent(progress);
	return glm::lookAt(position, GetFocusPoint(progress) /*glm::vec3(0)*/, glm::vec3(0.0f, 1.0f, 0.0f));

}

glm::vec3 TrackCamera::GetPosition(float t) const{
	return curve->getPosition(t);
}

glm::vec3 TrackCamera::GetFocusPoint(float t) const{
		return GetPosition(t) + curve->getTangent(t);

}

glm::vec3 TrackCamera::GetTangent(float t) const{
	return curve->getTangent(t);
}


