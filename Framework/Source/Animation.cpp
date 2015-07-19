//
// COMP 371 Assignment Framework
//
// Created by Nicolas Bergeron on 8/7/14.
// Updated by Gary Chang on 14/1/15
//
// Copyright (c) 2014-2015 Concordia University. All rights reserved.
//

#include "Animation.h"
#include "Renderer.h"
#include "World.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>


// Include GLEW - OpenGL Extension Wrangler
#include <GL/glew.h>

using namespace glm;
using namespace std;

AnimationKey::AnimationKey() : Model()
{
}

AnimationKey::~AnimationKey()
{
}

void AnimationKey::Update(float dt)
{
	Model::Update(dt);
}

void AnimationKey::Draw()
{
	Model::Draw();
}

bool AnimationKey::ParseLine(const std::vector<ci_string> &token)
{
	if (token.empty())
	{
		return true;
	}
	else
	{
		return Model::ParseLine(token);
	}
}

Animation::Animation() 
	: mName(""), mCurrentTime(0.0f), mDuration(0.0f), mVertexBufferID(0), mVertexArrayID(0)
{
}

Animation::~Animation()
{
}

void Animation::CreateVertexBuffer()
{
    // This is just to display lines between the animation keys
    for (int i=0; i<mKey.size(); ++i)
    {
        Vertex v;
        v.position = mKey[i].mPosition;
        mVertexBuffer.push_back(v);
    }
    
	// Create a vertex array
	glGenVertexArrays(1, &mVertexArrayID);

	// Upload Vertex Buffer to the GPU, keep a reference to it (mVertexBufferID)
	glGenBuffers(1, &mVertexBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, mVertexBufferID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3)*mVertexBuffer.size(), &(mVertexBuffer[0]), GL_STATIC_DRAW);
}

void Animation::Update(float dt)
{
	mCurrentTime += dt;

    while(mCurrentTime > mDuration)
    {
        mCurrentTime -= mDuration;
    }
}

void Animation::Draw()
{
	// Draw lines between waypoints
	//
	// Steps:
	// - Draw the Vertex Buffer
	// - The Shader used to draw the Animation is AnimationLines, only requires to send the positions of the waypoints
	// - You need to bind the vertex buffer created in CreateVertexBuffer() as the input of the vertex shader
	// - Also set the WorldTransform uniform variable in the vertex shader
	// - You Should use GL_LINE_LOOP as a primitive to draw lines (not triangles)
	// - You can look at CubeModel::Draw() for a good example!

	// The Model View Projection transforms are computed in the Vertex Shader
	glBindVertexArray(mVertexArrayID);
	GLuint WorldMatrixLocation = glGetUniformLocation(Renderer::GetShaderProgramID(), "WorldTransform");
    glUniformMatrix4fv(WorldMatrixLocation, 1, GL_FALSE, &mat4(1.0f)[0][0]);

	// 1st attribute buffer : vertex Positions
    glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, mVertexBufferID);
	glVertexAttribPointer(0,
		3,				// size
		GL_FLOAT,		// type
		GL_FALSE,		// normalized?
		sizeof(Vertex), // stride
		(void*)0        // array buffer offset
		);
    
	// Draw the triangles !
	glDrawArrays(GL_LINE_LOOP, 0, mVertexBuffer.size());

	glDisableVertexAttribArray(0);
}


void Animation::Load(ci_istringstream& iss)
{
	ci_string line;

	// Parse model line by line
	while(std::getline(iss, line))
	{
		// Splitting line into tokens
		ci_istringstream strstr(line);
		istream_iterator<ci_string, char, ci_char_traits> it(strstr);
		istream_iterator<ci_string, char, ci_char_traits> end;
		vector<ci_string> token(it, end);

		if (ParseLine(token) == false)
		{
			fprintf(stderr, "Error loading scene file... token:  %s!", token[0].c_str());
			getchar();
			exit(-1);
		}
	}
}


bool Animation::ParseLine(const std::vector<ci_string> &token)
{
    if (token.empty())
    {
        return true;
    }
	else if (token[0] == "name")
	{
		assert(token.size() > 2);
		assert(token[1] == "=");

		mName = token[2];
		return true;
	}
	else if (token[0] == "key")
	{
		assert(token.size() > 5);
        assert(token[1] == "=");
        assert(token[3] == "time");
        assert(token[4] == "=");

		ci_string name = token[2];
		AnimationKey *key = World::GetInstance()->FindAnimationKey(name);
        
		assert(key != nullptr);
		AddKey(key, atof(token[5].c_str()));
		return true;
	}
	return false;
}

void Animation::AddKey(AnimationKey* key, float time)
{
    assert(time >= mDuration);
	mKey.push_back(*key);
    mKeyTime.push_back(time);
    mDuration = time;
}

ci_string Animation::GetName() const
{
	return mName;
}

glm::mat4 Animation::GetAnimationWorldMatrix() const
{
	
	float beforeT = 0.0f;
	AnimationKey before;
	AnimationKey after;
	float afterT = mDuration;

	for (int i = 0; i < mKeyTime.size(); i++){ //find before and after keyframes
		if (mKeyTime[i] >= beforeT && mKeyTime[i] <= mCurrentTime){
			beforeT = mKeyTime[i];
			before = mKey[i];
		}
		if (mKeyTime[i] <= afterT && mKeyTime[i] >= mCurrentTime){
			afterT = mKeyTime[i];
			after = mKey[i];
		}
	}
	//% between keyframes
	float dc = mCurrentTime - beforeT;
	float dt = afterT - beforeT;
	float pt = dc / dt;
	
	vec3 posVec = mix(before.mPosition, after.mPosition, pt);
	mat4 t = translate(mat4(1.0f), posVec);
	
	vec3 scaleVec = mix(before.mScaling, after.mScaling, pt);
	mat4 s = scale(mat4(1.0f), scaleVec);
	
	quat beforeQuat = angleAxis(before.mRotationAngleInDegrees, before.mRotationAxis);
	quat afterQuat = angleAxis(after.mRotationAngleInDegrees, after.mRotationAxis);
	quat rotationQuat = slerp(beforeQuat, afterQuat, pt);
	mat4 r = mat4_cast(rotationQuat);

	mat4 worldMatrix = t * r * s;

	return worldMatrix;
}

AnimationKey Animation::getPrevKey(){
	return mKey[getPrevKeyIndex()];
}
AnimationKey Animation::getNextKey(){
	return mKey[getNextKeyIndex()];
}

int Animation::getNextKeyIndex(){
	int i;
	for(;i < mKeyTime.size() && mCurrentTime > mKeyTime[i]; i++);
	return i;
}

int Animation::getPrevKeyIndex(){
	return getNextKeyIndex()-1;
}



float Animation::getKeyProgress(){
	int before = getPrevKeyIndex();
	int after = getNextKeyIndex();
	return (mKeyTime[before]-mCurrentTime) / (mKeyTime[after] - mKeyTime[before]);
}

glm::vec3 Animation::getPosition(){
	return glm::mix(getPrevKey().GetPosition(), getNextKey().GetPosition(), getKeyProgress());
}

