/*
// Noise Project
//
// Created by Geoffrey Boom. Pizza is the first food group, all others are extraneous.
*/
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
	glm::vec3 getDisplacement() const;

	//sets the target which the camera rotates around
	virtual void setTarget(Model* model);

	Model* getNextModel();
private:
	float radius;
	float rotateX;
	float rotateY;
	float angleSpeed;
	float moveSpeed;
	Model* targetModel;
};


