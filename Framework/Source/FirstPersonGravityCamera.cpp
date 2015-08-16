#include "FirstPersonGravityCamera.h"
#include "EventManager.h"
#include "World.h"
#include "Plane.h"
#include <GLFW/glfw3.h>
float FirstPersonGravityCamera::getGroundHeight(float x, float z){

	return 10;

}

void FirstPersonGravityCamera::Update(float dt){
	//getting initial position
	glm::vec3 initialPosition = getPosition();
	float height = initialPosition.y;

	//updating the camera as if it were a normal FP camera
	FirstPersonCamera::Update(dt);

	glm::vec3 nextPosition = getPosition();


	/*----applying the Gravity and Jump constraints----*/

	//if the player is on the ground and has pressed space
	if(glfwGetKey(EventManager::GetWindow(), GLFW_KEY_SPACE) == GLFW_PRESS && grounded == true){

		//set the initial vertical velocity for a jump
		verticalVelocity = 100;

		//set the horizontal velocity to the current horizontal velocity
		horizontalVelocity = glm::vec3(nextPosition.x - initialPosition.x, 0, nextPosition.z - initialPosition.z)/dt;

		grounded = false;

	}
	//if the player is in the air, the change in x and z must correspond to the initial velocity at the beginning of the jump. 
	if(grounded == false){
		nextPosition = glm::vec3(initialPosition.x + horizontalVelocity.x*dt, 0, initialPosition.z + horizontalVelocity.z*dt);
	}

	//apply gravity to velocity
	verticalVelocity -= 100 * dt;

	//apply velocity to position
	height += verticalVelocity * dt;

	float groundHeight = getGroundHeight(nextPosition.x, nextPosition.z);
	if (height < groundHeight)
	{
		grounded = true;
		height = groundHeight;
	}
	nextPosition.y = height;
	setPosition (nextPosition);

	hasMoved = false;
}

FirstPersonGravityCamera::FirstPersonGravityCamera() : FirstPersonCamera(glm::vec3(10,20,10), glm::vec3(0,0,0)){
	setSpeed(20.0f);
}
FirstPersonGravityCamera::~FirstPersonGravityCamera(){
}
