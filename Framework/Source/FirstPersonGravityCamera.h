#pragma once
#include "FirstPersonCamera.h"
class FirstPersonGravityCamera: public FirstPersonCamera
{
public:
	FirstPersonGravityCamera(void);
	~FirstPersonGravityCamera(void);

	float FirstPersonGravityCamera::getGroundHeight(float x, float z);
	void Update(float dt);

private:
	float verticalVelocity;
	glm::vec3 horizontalVelocity;
	bool grounded;
};

