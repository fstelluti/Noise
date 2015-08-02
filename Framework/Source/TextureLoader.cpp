//
// COMP 371 Assignment Framework
//
// Created by Nicolas Bergeron on 15/7/15.
//
// Copyright (c) 2014-2015 Concordia University. All rights reserved.
//
// Modified by: Francois Stelluti
//

#include "TextureLoader.h"

#include <cassert>
#include <GL/glew.h>

#include <FreeImageIO.h>


int TextureLoader::LoadTexture(const char * imagepath)
{    
    // Load image using the Free Image library
    FREE_IMAGE_FORMAT format = FreeImage_GetFileType(imagepath, 0);
    FIBITMAP* image = FreeImage_Load(format, imagepath);
    FIBITMAP* image32bits = FreeImage_ConvertTo32Bits(image);
    
    // Get an available texture index from OpenGL
    GLuint texture = 0;
    glGenTextures(1, &texture);
    assert(texture != 0);
    
    // Set OpenGL filtering properties (bi-linear interpolation)
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    // Retrieve width and hight
    int width = FreeImage_GetWidth(image32bits);
    int height = FreeImage_GetHeight(image32bits);
    
    // This will upload the texture to the GPU memory
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height,
                 0, GL_BGRA, GL_UNSIGNED_BYTE, (void*)FreeImage_GetBits(image32bits));
    
    // Free images
    FreeImage_Unload(image);
    FreeImage_Unload(image32bits);
 
    return texture;
}

int TextureLoader::LoadSkyboxTexture(const char* imagepath, GLuint texture)
{    
    // Load image using the Free Image library
    FREE_IMAGE_FORMAT format = FreeImage_GetFileType(imagepath, 0);
    FIBITMAP* image = FreeImage_Load(format, imagepath);
    FIBITMAP* image32bits = FreeImage_ConvertTo32Bits(image);
    

    //Generate the cube map texture in Opengl
    glActiveTexture (GL_TEXTURE0);
    glGenTextures (1, &texture);
    //GLuint textureInd = 0;
    //glGenTextures(1, &textureInd);
    assert(texture != 0);
    
    // Set OpenGL filtering properties (bi-linear interpolation)
    //Bind the texture to the cube map
	glBindTexture (GL_TEXTURE_CUBE_MAP, texture);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//Texture parameters
    //Clamp-to-edge parameter helps to hide the seams of the cube textures
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    
    // Retrieve width and hight
    int width = FreeImage_GetWidth(image32bits);
    int height = FreeImage_GetHeight(image32bits);
    
    // This will upload the texture to the GPU memory
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height,
                 0, GL_BGRA, GL_UNSIGNED_BYTE, (void*)FreeImage_GetBits(image32bits));
    
    // Free images
    FreeImage_Unload(image);
    FreeImage_Unload(image32bits);
 
    return texture;
}
