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
#include "Model.h"
#include <vector>

#include <GLM/glm.hpp>


class AnimationKey : public Model
{
public:
    AnimationKey();
    ~AnimationKey();

	virtual void Update(float dt);
	virtual void Draw();
    
protected:
	virtual bool ParseLine(const std::vector<ci_string> &token);
};

class Animation
{
public:
    
	Animation();
    virtual ~Animation();

	/*void CreateVertexBuffer();*/

    virtual void Update(float dt, float currentVolume, float* currentSpec);
    virtual void Draw();

	//a function that gets the position of the object
	virtual glm::vec3 GetPosition() const;

    void AddKey(AnimationKey* key, float time);
	glm::mat4 GetAnimationWorldMatrix(glm::vec3 position, glm::vec3 scaling, glm::vec3 stretchVec, int numerator, int denominator) const;

	void Load(ci_istringstream& iss);
	ci_string GetName() const;

	void setCurrentModel(Model* currentModel);

protected:
    virtual bool ParseLine(const std::vector<ci_string> &token);

private:


	/*  #justkeythings  */
	
	//gets the previous key's index
	int getPrevKeyIndex() const;

	//gets the next key's index
	int getNextKeyIndex() const;
	
	//gets the key that happened before current time
	AnimationKey getPrevKey() const;

	//gets the key that happens after current time
	AnimationKey getNextKey() const;

	//gets how much progress has been made between two keys
	float getKeyProgress() const;

	ci_string mName; // The model name is mainly for debugging

	float mCurrentTime;
    float mDuration;
	float mCurrentVolume;
	float* mCurrentSpec;

    std::vector<AnimationKey> mKey;
    std::vector<float> mKeyTime;

	Model* currentModel;
    // For drawing lines between keys
    // The vertex format is only position
    struct Vertex
    {
        glm::vec3 position;
    };
    
    std::vector<Vertex> mVertexBuffer;
    unsigned int mVertexArrayID;
    unsigned int mVertexBufferID;
};
