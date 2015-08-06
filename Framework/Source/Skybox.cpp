/*
COMP 371 - Final Project

Created by Nicolas Bergeron on 8/7/14.
Updated by Gary Chang on 14/1/15
Modified by: Francois Stelluti

*/

#include "Skybox.h"
#include "Renderer.h"
#include "World.h"
#include "Camera.h"
#include "TextureLoader.h"

#include <iostream>

// Include GLEW
#include <GL/glew.h>

using namespace glm;

Skybox::Skybox() : Model() {
	
	//Create the Cube for the Skybox, as an array of floats
	float cubeVerticies[] = {
	  -50.0f,  50.0f, -50.0f,
	  -50.0f, -50.0f, -50.0f,
	   50.0f, -50.0f, -50.0f,
	   50.0f, -50.0f, -50.0f,
	   50.0f,  50.0f, -50.0f,
	  -50.0f,  50.0f, -50.0f,
  
	  -50.0f, -50.0f,  50.0f,
	  -50.0f, -50.0f, -50.0f,
	  -50.0f,  50.0f, -50.0f,
	  -50.0f,  50.0f, -50.0f,
	  -50.0f,  50.0f,  50.0f,
	  -50.0f, -50.0f,  50.0f,
  
	   50.0f, -50.0f, -50.0f,
	   50.0f, -50.0f,  50.0f,
	   50.0f,  50.0f,  50.0f,
	   50.0f,  50.0f,  50.0f,
	   50.0f,  50.0f, -50.0f,
	   50.0f, -50.0f, -50.0f,
   
	  -50.0f, -50.0f,  50.0f,
	  -50.0f,  50.0f,  50.0f,
	   50.0f,  50.0f,  50.0f,
	   50.0f,  50.0f,  50.0f,
	   50.0f, -50.0f,  50.0f,
	  -50.0f, -50.0f,  50.0f,
  
	  -50.0f,  50.0f, -50.0f,
	   50.0f,  50.0f, -50.0f,
	   50.0f,  50.0f,  50.0f,
	   50.0f,  50.0f,  50.0f,
	  -50.0f,  50.0f,  50.0f,
	  -50.0f,  50.0f, -50.0f,
  
	  -50.0f, -50.0f, -50.0f,
	  -50.0f, -50.0f,  50.0f,
	   50.0f, -50.0f, -50.0f,
	   50.0f, -50.0f, -50.0f,
	  -50.0f, -50.0f,  50.0f,
	   50.0f, -50.0f,  50.0f
	};

	//Create a vertex array
	glGenVertexArrays (1, &mSkyBoxVertexArrayID);

	//Generate and bind the vertex buffer
	glGenBuffers (1, &mSkyBoxVertexBufferID);
	glBindBuffer (GL_ARRAY_BUFFER, mSkyBoxVertexBufferID);
	//Each triangle (3) * (6 sides of a cube * (2 triangles each * 3 verts)) * the size of a float
	glBufferData (GL_ARRAY_BUFFER, 3 * 36 * sizeof(float), cubeVerticies, GL_STATIC_DRAW);

	//Load textures
	skyTextureID = 1;
	cubeMap("../Assets/Textures/negz.jpg","../Assets/Textures/posz.jpg","../Assets/Textures/negy.jpg", "../Assets/Textures/posy.jpg",
			"../Assets/Textures/negx.jpg", "../Assets/Textures/posx.jpg", &skyTextureID);

}

Skybox::~Skybox()
{
	//Free the GPU from the Vertex Buffer
	glDeleteBuffers(1, &mSkyBoxVertexBufferID);
	glDeleteVertexArrays(1, &mSkyBoxVertexArrayID);
}

void Skybox::Update(float dt)
{
	Model::Update(dt);
}

void Skybox::Draw() {

	Renderer::CheckForErrors();

	//Disable DepthMask so that everything always gets draw in fron of the skybox
	glDepthMask (GL_FALSE);

	// Set current shader to be the Textured Shader
    ShaderType oldShader = (ShaderType)Renderer::GetCurrentShader();
    
	//Use the Skybox shaders
	Renderer::SetShader(ShaderType::SHADER_TEXTURE_SKY);
    glUseProgram(Renderer::GetShaderProgramID());

    Renderer::CheckForErrors();

    GLuint textureLocation = glGetUniformLocation(Renderer::GetShaderProgramID(), "mySkyboxSamplerTexture");

    glUniform1i(textureLocation, 0);				// Set our Texture sampler to user Texture Unit 0

    Renderer::CheckForErrors();

	// This looks for the MVP Uniform variable in the Vertex Program
    GLuint VPMatrixLocation = glGetUniformLocation(Renderer::GetShaderProgramID(), "ProjectionTransform");
    
    // Send the view projection constants to the shader
    const Camera* currentCamera = World::GetInstance()->GetCurrentCamera();
    mat4 VP = currentCamera->GetViewProjectionMatrix();
	///////////
	//TODO Remove translation information????
	///////////
    glUniformMatrix4fv(VPMatrixLocation, 1, GL_FALSE, &VP[0][0]);

	//Draw the vertex buffer
	//Generate and bind the vertex array
	glBindVertexArray (mSkyBoxVertexArrayID);

	//Get the world transform matrix
	GLuint WorldMatrixLocation = glGetUniformLocation(Renderer::GetShaderProgramID(), "ViewTransform"); 

	//Skybox is relative to the origin (??)
	mat4 worldMatrix(1.0f);
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
	glDrawArrays(GL_TRIANGLES, 0, 36); // 36 vertices: 3 * 2 * 6 (3 per triangle, 2 triangles per face, 6 faces)

	glDisableVertexAttribArray(0);

	glDepthMask (GL_TRUE);

	Renderer::CheckForErrors();
    
    Renderer::SetShader(oldShader);

}

void Skybox::cubeMap(const char* front, const char* back, const char* top, const char* bottom,
			const char* left, const char* right, GLuint* cubeTexture) {

  glActiveTexture(GL_TEXTURE0);
  glGenTextures (1,cubeTexture);

  //Load each side of the cube (6 textures total) according to the their position
  cubeMapSideLoader(*cubeTexture, GL_TEXTURE_CUBE_MAP_POSITIVE_X, right);
  cubeMapSideLoader(*cubeTexture, GL_TEXTURE_CUBE_MAP_NEGATIVE_X, left);
  cubeMapSideLoader(*cubeTexture, GL_TEXTURE_CUBE_MAP_POSITIVE_Y, top);
  cubeMapSideLoader(*cubeTexture, GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, bottom);
  cubeMapSideLoader(*cubeTexture, GL_TEXTURE_CUBE_MAP_POSITIVE_Z, back);
  cubeMapSideLoader(*cubeTexture, GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, front);

}

bool Skybox::cubeMapSideLoader(GLuint skyTexture, GLenum side, const char* fileName) {

	glBindTexture(GL_TEXTURE_CUBE_MAP, skyTexture);

	//Load image
	unsigned int image = TextureLoader::LoadSkyboxTexture(fileName, skyTexture, side);

	//Check that the image was loaded properly 
	if (image == 0) {
		fprintf (stderr, "ERROR: could not load %s\n", fileName);
		return false;
	}
	
	return true;
}

bool Skybox::ParseLine(const std::vector<ci_string> &token)
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