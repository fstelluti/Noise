#pragma once

#include "TrackCamera.h"
#include "Curves.h"
class TrackCameraLookatCurve: public TrackCamera
{
public:


	TrackCameraLookatCurve(void);
	~TrackCameraLookatCurve(void);

	virtual glm::vec3 GetFocusPoint(float t) const;
	virtual void nextPoint();

private:
	Curve* lookatCurve;
};

