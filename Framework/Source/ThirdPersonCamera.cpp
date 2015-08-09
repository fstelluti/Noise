#include "ThirdPersonCamera.h"
#include "EventManager.h"
#include <GLM/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Animation.h"
#include "World.h"

#include <stdio.h>

#include <string>
#include <GLFW/glfw3.h>
#include <algorithm>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>

glm::vec3 rotateAroundAxis(glm::vec3 displacement, glm::vec3 newAxis, float RY){

	glm::quat rotation = glm::angleAxis(RY, newAxis);
	glm::mat4 r = glm::mat4_cast(rotation);
	/*glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), RY, newAxis);*/
	glm::vec4 temp = rotation * glm::vec4(displacement, 1);
	return glm::vec3(temp[0],temp[1],temp[2]);
}


ThirdPersonCamera::ThirdPersonCamera(void)
{

	setTarget(getNextModel());

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

	if(glfwGetKey(EventManager::GetWindow(), GLFW_KEY_UP) == GLFW_PRESS){
		radius -= 0.01  * angleSpeed;
	}
	if(glfwGetKey(EventManager::GetWindow(), GLFW_KEY_DOWN) == GLFW_PRESS){
		radius += 0.01  * angleSpeed;
	}

	static bool pressed = 0;
	if(glfwGetKey(EventManager::GetWindow(), GLFW_KEY_N) == GLFW_PRESS && !pressed){
		pressed = 1;
		setTarget(getNextModel());
	}
	if(glfwGetKey(EventManager::GetWindow(), GLFW_KEY_N) == GLFW_RELEASE){
		pressed = 0;
	}

	if(radius < 0){
		radius = 0;
	}
}

Model* ThirdPersonCamera::getNextModel(){

	static int index = 0;
	index = (index + 1) % 2;
	std::string names[4] = {
		"\"Cube4\"",
		"\"Sphere\""
	};

	World* w = World::GetInstance();
	return w->FindModel(ci_string(names[index].c_str()));

}
glm::mat4 ThirdPersonCamera::GetViewMatrix() const{
	
	glm::vec3 displacement = glm::vec3(0.0f,0.0f,1.0f);

	float RX = glm::radians(rotateX);
	
	glm::mat3 rotation = glm::mat3(
			cosf(RX),0.0f,sinf(RX),
			0.0f,1.0f,0.0f,
			-sinf(RX),0.0f,cosf(RX));

	displacement = rotation * displacement;

	glm::vec3 newAxis = rotation * glm::vec3(1.0f,0.0f,0.0f);

	//rotating around an arbitrary axis newAxis
	displacement = rotateAroundAxis(displacement, newAxis,rotateY);

	displacement *= radius;
	
	if(targetModel){
		glm::vec3 pos = (targetModel)->GetPosition();
		return glm::lookAt(pos-displacement,pos,glm::vec3(0.0f,1.0f,0.0f));
	}
	else
		return glm::lookAt(glm::vec3(0,5,0)-displacement, glm::vec3(0,5,0),glm::vec3(0.0f,1.0f,0.0f));
}

