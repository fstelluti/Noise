#include "ThirdPersonCamera.h"
#include "EventManager.h"
#include <GLM/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <stdio.h>

#include <GLFW/glfw3.h>
#include <algorithm>


ThirdPersonCamera::ThirdPersonCamera(void)
{
	distanceFromTarget = 5.0f;
	rotateX = 0;
	rotateY = 0;
	angleSpeed = 1;
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
	if (rotateX > 360){
		rotateX -= 360;
	}
	else if (rotateX < 360){
		rotateX += 360;
	}
	if (rotateY > 360){
		rotateY -= 360;
	}
	else if (rotateY < 360){
		rotateY += 360;
	}
	
	glm::vec3 displaceVector = glm::vec3(1.0f);

}

glm::mat4 ThirdPersonCamera::GetViewMatrix() const{
	
	if(targetModel){
		return glm::lookAt(targetModel->GetPosition(),-targetModel->GetPosition(),glm::vec3(0.0f,1.0f,0.0f));
	}
	else
		return glm::mat4(1);
}

