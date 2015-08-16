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

	glm::vec3 direction = glm::vec3(getDisplacement().x, 0, getDisplacement().z);
	glm::vec3 sideVector = glm::cross(direction, glm::vec3(0.0f, 1.0f, 0.0f));
	glm::vec3 upVector = glm::vec3(0,1.0f,0);

	if(targetModel){
		if (glfwGetKey(EventManager::GetWindow(), GLFW_KEY_W ) == GLFW_PRESS)
		{
			targetModel->SetPosition(targetModel->GetPosition() + (glm::normalize(direction) * dt * 7.0f));
			hasMoved = true;
		}

		if (glfwGetKey(EventManager::GetWindow(), GLFW_KEY_S ) == GLFW_PRESS)
		{
			targetModel->SetPosition(targetModel->GetPosition() - (glm::normalize(direction) * dt * 7.0f));
			hasMoved = true;
		}

		if (glfwGetKey(EventManager::GetWindow(), GLFW_KEY_D ) == GLFW_PRESS)
		{
			targetModel->SetPosition(targetModel->GetPosition() + (glm::normalize(sideVector) * dt * 7.0f));
			hasMoved = true;
		}

		if (glfwGetKey(EventManager::GetWindow(), GLFW_KEY_A ) == GLFW_PRESS)
		{
			targetModel->SetPosition(targetModel->GetPosition() -(glm::normalize(sideVector) * dt * 7.0f));
			hasMoved = true;
		}


		//space and shift for up and down

		if(glfwGetKey(EventManager::GetWindow(), GLFW_KEY_SPACE) == GLFW_PRESS){
			targetModel->SetPosition(targetModel->GetPosition() + (upVector * dt * 4.0f));
			hasMoved = true;
		}
		if(glfwGetKey(EventManager::GetWindow(), GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS){
			targetModel->SetPosition(targetModel->GetPosition() - (upVector * dt * 4.0f));
			hasMoved = true;
		}
	}

	if(glfwGetKey(EventManager::GetWindow(), GLFW_KEY_UP) == GLFW_PRESS){
		radius -= 0.01  * angleSpeed;
	}
	if(glfwGetKey(EventManager::GetWindow(), GLFW_KEY_DOWN) == GLFW_PRESS){
		radius += 0.01  * angleSpeed;
	}



	static bool four_pressed = 1;
	if(glfwGetKey(EventManager::GetWindow(), GLFW_KEY_6) == GLFW_PRESS && !four_pressed){
		four_pressed = 1;
		setTarget(getNextModel());
	}
	if(glfwGetKey(EventManager::GetWindow(), GLFW_KEY_6 ) == GLFW_RELEASE){
		four_pressed = 0;
	}

	if(radius < 0){
		radius = 0;
	}
}

Model* ThirdPersonCamera::getNextModel(){

	static int index = 0;
	int x = World::GetInstance()->getAllModels()->size();
	if(x == 0){
		return nullptr;
	}
	else{
		index = (index + 1) % (x);
	}
	World* w = World::GetInstance();
	return w->FindModel((*World::GetInstance()->getAllModels())[index]->GetName());

}

glm::vec3 ThirdPersonCamera::getDisplacement() const{
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

	return displacement;
}

glm::mat4 ThirdPersonCamera::GetViewMatrix() const{
	
	glm::vec3 displacement = getDisplacement();
	
	if(targetModel){
		glm::mat4 worldmatrix = (targetModel)->GetWorldMatrix();
		glm::vec3 pos = targetModel->GetPosition();//glm::vec3(worldmatrix[3][0], worldmatrix[3][1], worldmatrix[3][2]);
		return glm::lookAt(pos-displacement,pos,glm::vec3(0.0f,1.0f,0.0f));
	}
	else
		return glm::lookAt(glm::vec3(0,5,0)-displacement, glm::vec3(0,5,0),glm::vec3(0.0f,1.0f,0.0f));
}

