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
	glm::vec3 GetPosition(glm::vec3 v1,glm::vec3 v2, glm::vec3 v3, glm::vec3 v4, float p) const;
	glm::vec3 GetTangent(glm::vec3 v1,glm::vec3 v2, glm::vec3 v3, glm::vec3 v4, float p) const;

private:
	std::vector<glm::vec3> points;
	int currentPoints[4];
	float progress;

};

