#pragma once
#include "Camera.h"
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

private:
	std::vector<glm::vec3> points;
	int currentPoints[4];
	float progress;

};

