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

/*void Animation::CreateVertexBuffer()
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
}*/

void Animation::Update(float dt, float currentVolume, float* currentSpec)
{
	mCurrentTime += dt;
	if (mDuration > 0){
		while(mCurrentTime > mDuration)
			{
				mCurrentTime -= mDuration;
			}
	}
    
	mCurrentVolume = currentVolume;
	mCurrentSpec = currentSpec;
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

glm::mat4 Animation::GetAnimationWorldMatrix(vec3 position, vec3 scaling, vec3 stretchVec, int numerator, int denominator) const
{
	if (mName == "\"StretchX\""){
		vec3 scaleVec(1.0f, 0.0f, 0.0f);
		scaleVec = scaleVec * mCurrentVolume;
		mat4 s = scale(mat4(1.0f), scaling + scaleVec);
		
		vec3 translateVec(1.0f, 0.0f, 0.0f);
		translateVec = translateVec * mCurrentVolume;
		mat4 t = translate(mat4(1.0f), position + translateVec);
		mat4 worldMatrix = t * s;
		return worldMatrix;
	}
	else if (mName == "\"StretchY\""){
		vec3 scaleVec(0.0f, 1.0f, 0.0f);
		scaleVec = scaleVec * mCurrentVolume;
		mat4 s = scale(mat4(1.0f), scaling + scaleVec);

		vec3 translateVec(0.0f, 1.0f, 0.0f);
		translateVec = translateVec * mCurrentVolume;
		mat4 t = translate(mat4(1.0f), position + translateVec);
		mat4 worldMatrix = t * s;
		return worldMatrix;
	}
	else if (mName == "\"StretchZ\""){
		vec3 scaleVec(0.0f, 0.0f, 1.0f);
		scaleVec = scaleVec * mCurrentVolume;
		mat4 s = scale(mat4(1.0f), scaling + scaleVec);

		vec3 translateVec(0.0f, 0.0f, 1.0f);
		translateVec = translateVec * mCurrentVolume;
		mat4 t = translate(mat4(1.0f), position + translateVec);
		mat4 worldMatrix = t * s;
		return worldMatrix;
	}
	else if (mName == "\"StretchVec\""){
		vec3 scaleVec(abs(stretchVec.x), abs(stretchVec.y), abs(stretchVec.z));
		scaleVec = scaleVec * mCurrentVolume;
		mat4 s = scale(mat4(1.0f), scaling + scaleVec);

		vec3 translateVec = stretchVec;
		translateVec = translateVec * mCurrentVolume;
		mat4 t = translate(mat4(1.0f), position + translateVec);
		mat4 worldMatrix = t * s;
		return worldMatrix;

	}
	else if (mName == "\"Scale\""){
		vec3 scaleVec(1.0f, 1.0f, 1.0f);
		scaleVec = scaleVec * mCurrentVolume;
		mat4 s = scale(mat4(1.0f), scaling + scaleVec);

		mat4 t = translate(mat4(1.0f), position);
		mat4 worldMatrix = t * s;
		return worldMatrix;
	}
	else if (mName == "\"TranslateX\""){
		vec3 translateVec(1.0f, 0.0f, 0.0f);
		translateVec = translateVec * mCurrentVolume;
		mat4 t = translate(mat4(1.0f), position + translateVec);
		mat4 s = scale(mat4(1.0f), scaling);
		mat4 worldMatrix = t * s;
		return worldMatrix;
	}
	else if (mName == "\"TranslateY\""){
		vec3 translateVec(0.0f, 1.0f, 0.0f);
		translateVec = translateVec * mCurrentVolume;
		mat4 t = translate(mat4(1.0f), position + translateVec);
		mat4 s = scale(mat4(1.0f), scaling);
		mat4 worldMatrix = t * s;
		return worldMatrix;
	}
	else if (mName == "\"TranslateZ\""){
		vec3 translateVec(0.0f, 0.0f, 1.0f);
		translateVec = translateVec * mCurrentVolume;
		mat4 t = translate(mat4(1.0f), position + translateVec);
		mat4 s = scale(mat4(1.0f), scaling);
		mat4 worldMatrix = t * s;
		return worldMatrix;
	}
	else if (mName == "\"RotateX\""){
		mat4 t = translate(mat4(1.0f), position);
		float angle = 1.0f;
		angle = angle + angle * mCurrentVolume;
		quat rotationQuat(angle, vec3(1.0f, 0.0f, 0.0f));
		mat4 r = mat4_cast(rotationQuat);
		mat4 s = scale(mat4(1.0f), scaling);
		mat4 worldMatrix = t * r * s;
		return worldMatrix;
	} 
	else if (mName == "\"SpectrumTranslate\""){
		int range = 1024 / denominator;
		int startIndex = (numerator * range) - range;
		int endIndex = numerator * range;
		float rangeVolume = 0;
		for (int i = startIndex; i < endIndex; i++){
			rangeVolume += mCurrentSpec[i];
		}
		rangeVolume = rangeVolume / range;
		rangeVolume *= 500;

		vec3 translateVec(0.0f, 1.0f, 0.0f);
		translateVec = translateVec * rangeVolume;
		mat4 t = translate(mat4(1.0f), position + translateVec);
		mat4 s = scale(mat4(1.0f), scaling);
		mat4 worldMatrix = t * s;
		return worldMatrix;
	}
	else if (mName == "\"SpectrumStretch\""){
		int range = 1024 / denominator;
		int startIndex = (numerator * range) - range;
		int endIndex = numerator * range;
		float rangeVolume = 0;
		for (int i = startIndex; i < endIndex; i++){
			rangeVolume += mCurrentSpec[i];
		}
		rangeVolume = rangeVolume / range;
		rangeVolume *= 500;

		vec3 scaleVec(0.0f, 1.0f, 0.0f);
		scaleVec = scaleVec * rangeVolume;
		mat4 s = scale(mat4(1.0f), scaling + scaleVec);

		vec3 translateVec(0.0f, 1.0f, 0.0f);
		translateVec = translateVec * rangeVolume;
		mat4 t = translate(mat4(1.0f), position + translateVec);
		mat4 worldMatrix = t * s;
		return worldMatrix;
	}
	else{
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
		vec3 up(0.0f, 1.0f, 0.0f);
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
}
