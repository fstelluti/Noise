//
// COMP 371 Assignment Framework
//
// Created by Nicolas Bergeron on 8/7/14.
// Updated by Gary Chang on 14/1/15
//
// Copyright (c) 2014-2015 Concordia University. All rights reserved.
//

#pragma once

#include "ParsingHelper.h"
#include "Billboard.h"
#include "Skybox.h"
#include <vector>

class Camera;
class Model;
class Animation;
class AnimationKey;
class ParticleSystem;
class ClippedCubeModel;
class Saw;
class CubeInitial;

class World
{
public:
	World();
	~World();
	
    static World* GetInstance();

	void Update(float dt, float currentVolume, float* currentSpec);
	void Draw();

	void LoadScene(const char * scene_path);
    Animation* FindAnimation(ci_string animName);
	Model* FindModel(ci_string modelName);
	AnimationKey* FindAnimationKey(ci_string keyName);

	const Camera* GetCurrentCamera() const;
	void AddBillboard(Billboard* b);
	void RemoveBillboard(Billboard* b);
	void AddParticleSystem(ParticleSystem* particleSystem);
	void RemoveParticleSystem(ParticleSystem* particleSystem);
	void TriggerBeat();
	std::vector<Model*>* getAllModels();
	

private:
    static World* instance;
	
	std::vector<Model*> mModel;
	Skybox skyboxModel;
    std::vector<Animation*> mAnimation;
    std::vector<AnimationKey*> mAnimationKey;
	std::vector<Camera*> mCamera;
	std::vector<ParticleSystem*> mParticleSystemList;
	unsigned int mCurrentCamera;

	Saw* saw;
    CubeInitial* initialCube;
	std::vector<Saw*> mSaw;
    std::vector<CubeInitial*> mCubeInitial;
	std::vector<ClippedCubeModel*> mClippedCubeModel;
	int clipped;

	BillboardList* mpBillboardList;
};
