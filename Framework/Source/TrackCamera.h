#pragma once
#include "Camera.h"
#include "Curves.h"
#include <glm/gtx/spline.hpp>
#include <vector>

class TrackCamera :
	public Camera
{
public:
	TrackCamera(void);
	~TrackCamera(void);

	virtual void Update(float dt);
	virtual glm::mat4 GetViewMatrix() const;
	glm::vec3 GetPosition(float t) const;
	glm::vec3 GetTangent(float t) const;

private:
	Curve* curve;
	float progress;

};




