#include "ThirdPersonCamera.h"
#include "EventManager.h"
#include <GLM/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <stdio.h>

#include <GLFW/glfw3.h>
#include <algorithm>


ThirdPersonCamera::ThirdPersonCamera(void)
{
	radius = 10.0f;
	rotateX = 0;
	rotateY = 0;
	angleSpeed = 10;
	moveSpeed = 1;
	
	targetModel = NULL;

}

void ThirdPersonCamera::setTarget(Model* target){
	targetModel = target;
}



ThirdPersonCamera::~ThirdPersonCamera(void)
{
}

void ThirdPersonCamera::Update(float dt)
{
	EventManager::DisableMouseCursor();

	//changing the rotation of our camera around the object. 
	rotateX += EventManager::GetMouseMotionX() * dt * angleSpeed;
	rotateY += EventManager::GetMouseMotionY() * dt * angleSpeed;

	//using this procedure instead of modulo since we're dealing with floats.
	if (rotateX < 0){
		rotateX = 360;
	}
	else if (rotateX > 360){
		rotateX = 0;
	}
	if (rotateY > 50){
		rotateY = 50;
	}
	else if (rotateY < -50){
		rotateY = -50;
	}
}

glm::mat4 ThirdPersonCamera::GetViewMatrix() const{
	
	glm::vec3 displacement = glm::vec3(0.0f,0.0f,1.0f) * radius;

	float RX = glm::radians(rotateX);
	float RY = glm::radians(rotateY);

	displacement = glm::mat3(
			cosf(RX),0.0f,sinf(RX),
			0.0f,1.0f,0.0f,
			-sinf(RX),0.0f,cosf(RX)) * displacement;

	glm::vec3 newAxis = glm::mat3(
			cosf(RX),0.0f,sinf(RX),
			0.0f,1.0f,0.0f,
			-sinf(RX),0.0f,cosf(RX)) * glm::vec3(1.0f,0.0f,0.0f);

	displacement = glm::mat3(
			cosf(RY) + newAxis[0]*newAxis[0]*(1-cosf(RY))						, newAxis[0] * newAxis[1] * (1-cosf(RY)) - newAxis[2]*sinf(RY)		, newAxis[0] * newAxis[2] * (1-cosf(RY)) + newAxis[1] * sinf(RY),
			newAxis[1] * newAxis[0] * (1 - cosf(RY)) + newAxis[2] * sinf(RY)	, cosf(RY) + newAxis[1] * newAxis[1] * (1 - cosf(RY))				, newAxis[1] * newAxis[2] * (1-cosf(RY)) - newAxis[0] * sinf(RY),
			newAxis[2] * newAxis[0] * (1 - cosf(RY)) - newAxis[1] * sinf(RY)	, newAxis[2] * newAxis[2] * (1 - cosf(RY)) + newAxis[0] * sinf(RY)	, cosf(RY) + newAxis[2]*newAxis[2] * (1-cosf(RY)))
			* displacement; // magic.
	
	if(targetModel){
		return glm::lookAt(targetModel->GetPosition()-displacement,targetModel->GetPosition(),glm::vec3(0.0f,1.0f,0.0f));
	}
	else
		return glm::lookAt(glm::vec3(0,0,0)-displacement, glm::vec3(0,0,0),glm::vec3(0.0f,1.0f,0.0f));
}

