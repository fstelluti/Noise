/*
// Noise Project
//
// Created by Geoffrey Boom. Don't look behind you. Cthulhu awaits.
// http://cdn2.hubspot.net/hub/293166/file-1087156844-jpg/images/gothic_dreams_cthulhu_the_chase.jpg
*/

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

