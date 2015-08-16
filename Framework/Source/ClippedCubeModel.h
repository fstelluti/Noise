//
// COMP 371 Assignment Framework
//
// Created by Nicolas Bergeron on 8/7/14.
// Updated by Gary Chang on 14/1/15
//
// Modified by: Liuai Hatter
//
// Copyright (c) 2014-2015 Concordia University. All rights reserved.
//

#pragma once

#include "Model.h"
#include "World.h"
#include <vector>

class ClippedCubeModel : public Model
{
private:
    // The vertex format could be different for different types of models
    struct Vertex
    {
        glm::vec3 position;
        glm::vec3 normal;
        glm::vec3 color;
    };

public:
    ClippedCubeModel(glm::vec4 planeL, glm::vec3 size = glm::vec3(1.0f, 1.0f, 1.0f), bool s = 0);
	virtual ~ClippedCubeModel();

	virtual void Update(float dt);
	virtual void Draw();
    
    void ClipTriangle(const Vertex& v1, const Vertex& v2, const Vertex& v3, const glm::vec4& L,std::vector<Vertex> &vertexBuffer,  std::vector<Vertex> &oF);
    
    glm::vec3 GetIntersection(glm::vec3 point0, glm::vec3 point1, glm::vec4 p);
    

protected:
	virtual bool ParseLine(const std::vector<ci_string> &token);

private:

	unsigned int mVertexArrayID;
	unsigned int mVertexBufferID;
    
    glm::vec3 mVelocity;

    
};
