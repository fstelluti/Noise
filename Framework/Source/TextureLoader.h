//
// COMP 371 Assignment Framework
//
// Created by Nicolas Bergeron on 15/7/15.
//
// Copyright (c) 2014-2015 Concordia University. All rights reserved.
//
// Modified by: Francois Stelluti
//

#pragma once

#include <GL/glew.h>

// Simple Texture Loader Class
class TextureLoader
{
public:
    static int LoadTexture(const char * imagepath);
	static int LoadSkyboxTexture(const char * imagepath, GLuint skyTexture, GLenum side);

private:
    
};
