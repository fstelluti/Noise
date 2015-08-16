/*
// Noise Project
//
// Created by Geoffrey Boom. When your sanity drips away, and all you're left with is madness, gaze up and see doge in all their wow.
*/

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
	virtual void setPoints(std::vector<glm::vec3> points);
	virtual void nextPoint();
	void setCurveType(int t);


private:
	Curve* curve;
	float progress;
	int type;
};




