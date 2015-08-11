#pragma once
#include "Camera.h"
#include "Curves.h"
#include <glm/gtx/spline.hpp>
#include <vector>


enum curveType{
	linear = 0,
	hermite = 1,
	bspline = 2
};
class TrackCamera :
	public Camera{
public:
	TrackCamera(void);
	~TrackCamera(void);

	virtual void Update(float dt);
	virtual glm::mat4 GetViewMatrix() const;
	virtual glm::vec3 GetPosition(float t) const;
	virtual glm::vec3 GetTangent(float t) const;
	virtual glm::vec3 GetFocusPoint(float t) const;
	virtual void nextPoint();
	void setCurveType(int t);

private:
	Curve* curve;
	float progress;
	int type;
};




