#pragma once
#include "camera.h"
#include "model.h"
class ThirdPersonCamera :
	public Camera
{
public:
	ThirdPersonCamera(void);
	virtual ~ThirdPersonCamera(void);
	virtual void Update(float dt);
	virtual glm::mat4 GetViewMatrix() const;

	//sets the target which the camera rotates around
	virtual void setTarget(Model* model);
private:
	float distanceFromTarget;
	float rotateX;
	float rotateY;
	float angleSpeed;
	float moveSpeed;
	Model* targetModel;
};


