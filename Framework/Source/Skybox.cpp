/*
COMP 371 - Final Project

Created by Nicolas Bergeron on 8/7/14.
Updated by Gary Chang on 14/1/15
Modified by: Francois Stelluti

*/

#include "Skybox.h"
#include "Renderer.h"
#include "TextureLoader.h"

// Include GLEW
#include <GL/glew.h>

using namespace glm;

Skybox::Skybox() {
	
	//Create the Cube for the Skybox, as an array of floats
	float cubeVerticies[] = {
	  -25.0f,  25.0f, -25.0f,
	  -25.0f, -25.0f, -25.0f,
	   25.0f, -25.0f, -25.0f,
	   25.0f, -25.0f, -25.0f,
	   25.0f,  25.0f, -25.0f,
	  -25.0f,  25.0f, -25.0f,
  
	  -25.0f, -25.0f,  25.0f,
	  -25.0f, -25.0f, -25.0f,
	  -25.0f,  25.0f, -25.0f,
	  -25.0f,  25.0f, -25.0f,
	  -25.0f,  25.0f,  25.0f,
	  -25.0f, -25.0f,  25.0f,
  
	   25.0f, -25.0f, -25.0f,
	   25.0f, -25.0f,  25.0f,
	   25.0f,  25.0f,  25.0f,
	   25.0f,  25.0f,  25.0f,
	   25.0f,  25.0f, -25.0f,
	   25.0f, -25.0f, -25.0f,
   
	  -25.0f, -25.0f,  25.0f,
	  -25.0f,  25.0f,  25.0f,
	   25.0f,  25.0f,  25.0f,
	   25.0f,  25.0f,  25.0f,
	   25.0f, -25.0f,  25.0f,
	  -25.0f, -25.0f,  25.0f,
  
	  -25.0f,  25.0f, -25.0f,
	   25.0f,  25.0f, -25.0f,
	   25.0f,  25.0f,  25.0f,
	   25.0f,  25.0f,  25.0f,
	  -25.0f,  25.0f,  25.0f,
	  -25.0f,  25.0f, -25.0f,
  
	  -25.0f, -25.0f, -25.0f,
	  -25.0f, -25.0f,  25.0f,
	   25.0f, -25.0f, -25.0f,
	   25.0f, -25.0f, -25.0f,
	  -25.0f, -25.0f,  25.0f,
	   25.0f, -25.0f,  25.0f
	};

	//Create a vertex array
	glGenVertexArrays (1, &mSkyBoxVertexArrayID);

	//Generate and bind the vertex buffer
	glGenBuffers (1, &mSkyBoxVertexBufferID);
	glBindBuffer (GL_ARRAY_BUFFER, mSkyBoxVertexBufferID);
	//Each triangle (3) * (6 sides of a cube * (2 triangles each * 3 verts)) * the size of a float
	glBufferData (GL_ARRAY_BUFFER, 3 * 36 * sizeof (float), &cubeVerticies, GL_STATIC_DRAW);

}

Skybox::~Skybox()
{
	//Free the GPU from the Vertex Buffer
	glDeleteBuffers(1, &mSkyBoxVertexBufferID);
	glDeleteVertexArrays(1, &mSkyBoxVertexArrayID);
}

void Skybox::draw() {

	//Draw the vertex buffer
	//Generate and bind the vertex array
	glBindVertexArray (mSkyBoxVertexArrayID);

	//Get the world transform matrix
	GLuint WorldMatrixLocation = glGetUniformLocation(Renderer::GetShaderProgramID(), "WorldTransform"); 
	glUniformMatrix4fv(WorldMatrixLocation, 1, GL_FALSE, &GetWorldMatrix()[0][0]);

	glEnableVertexAttribArray (0);
	glBindBuffer (GL_ARRAY_BUFFER, mSkyBoxVertexBufferID);
	glVertexAttribPointer(0,			// attribute
						3,				// size
						GL_FLOAT,		// type
						GL_FALSE,		// normalized?
						0,				// stride
						nullptr         // array buffer offset
					);

	//Draw the cube!

}

void Skybox::cubeMap(const char* front, const char* back, const char* top, const char* bottom,
			const char* left, const char* right, GLuint* cubeTexture) {

  //Load each side of the cube (6 textures total) according to the their position
  cubeMapSideLoader(*cubeTexture, GL_TEXTURE_CUBE_MAP_POSITIVE_X, right);
  cubeMapSideLoader(*cubeTexture, GL_TEXTURE_CUBE_MAP_NEGATIVE_X, left);
  cubeMapSideLoader(*cubeTexture, GL_TEXTURE_CUBE_MAP_POSITIVE_Y, top);
  cubeMapSideLoader(*cubeTexture, GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, bottom);
  cubeMapSideLoader(*cubeTexture, GL_TEXTURE_CUBE_MAP_POSITIVE_Z, back);
  cubeMapSideLoader(*cubeTexture, GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, front);

}

bool Skybox::cubeMapSideLoader(GLuint texture, GLenum side, const char* fileName) {

	//Load image
	unsigned int image = TextureLoader::LoadSkyboxTexture(fileName, texture);

	//Check that the image was loaded properly 
	if (image == 0) {
		fprintf (stderr, "ERROR: could not load %s\n", fileName);
		return false;
	}
	
	return true;
}
