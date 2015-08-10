
#include "Plane.h"
#include "Renderer.h"

// Include GLEW - OpenGL Extension Wrangler
#include <GL/glew.h>

using namespace glm;

Plane::Plane(int side) : Model()
{
	Plane::side = side;
	int SIZE_PER_SIDE = side;
	float MIN_POSITION = -side / 2;

	int* vbo = new int[1];
	int* ibo = new int[1];

	int floatsPerVertex = 10;
	int xLength = SIZE_PER_SIDE;
	int yLength = SIZE_PER_SIDE;

	for (int y = 0; y < yLength; y++){
		for (int x = 0; x < xLength; x++){
			float xPosition = MIN_POSITION + x;
			float yPosition = MIN_POSITION + y;
			float zPosition = 0.0f;

			vertexBuffer.push_back(glm::vec3(xPosition, yPosition, zPosition));
			vertexBuffer.push_back(glm::vec3(0.0f, 0.0f, 1.0f));
			vertexBuffer.push_back(glm::vec3(x*5 / 255.0f, y*5 / 255.0f, (x+y)*5 / 255.0f));
		}
	}

	int numStripsRequired = yLength - 1;
	int numDegensRequired = 2 * (numStripsRequired - 1);
	int verticesPerStrip = 2 * xLength;

	std::vector<unsigned short> indexData;

	for (int y = 0; y < yLength - 1; y++){
		if (y > 0){
			indexData.push_back((unsigned short)(y * yLength));
		}

		for (int x = 0; x < xLength; x++){
			indexData.push_back((unsigned short)((y * yLength) + x));
			indexData.push_back((unsigned short)(((y + 1) * yLength) + x));
		}
		if (y < yLength - 2){
			indexData.push_back((unsigned short)(((y + 1) * yLength) + (xLength - 1)));
		}
	}
	indexCount = indexData.size();

	// Create a vertex array
	glGenVertexArrays(1, &mVertexArrayID);

	// Upload Vertex Buffer to the GPU, keep a reference to it (mVertexBufferID)
	glGenBuffers(1, &mVertexBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, mVertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, vertexBuffer.size() * sizeof(vec3), &vertexBuffer[0], GL_DYNAMIC_DRAW);

	glGenBuffers(1, &mIndexBufferID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBufferID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount * sizeof(unsigned short), &indexData[0], GL_STATIC_DRAW);
}

Plane::~Plane()
{
	// Free the GPU from the Vertex Buffer
	glDeleteBuffers(1, &mVertexBufferID);
	glDeleteVertexArrays(1, &mVertexArrayID);
	glDeleteBuffers(1, &mIndexBufferID);
}

void Plane::Update(float dt)
{
	// If you are curious, un-comment this line to have spinning cubes!
	// That will only work if your world transform is correct...
	// mRotationAngleInDegrees += 90 * dt; // spins by 90 degrees per second

	Model::Update(dt);
}

void Plane::Draw()
{
	// Create a vertex array
	glGenVertexArrays(1, &mVertexArrayID);

	glGenBuffers(1, &mVertexBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, mVertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, vertexBuffer.size() * sizeof(vec3), &vertexBuffer[0], GL_DYNAMIC_DRAW);

	// Draw the Vertex Buffer
	// Note this draws a unit Cube
	// The Model View Projection transforms are computed in the Vertex Shader
	glBindVertexArray(mVertexArrayID);

	GLuint WorldMatrixLocation = glGetUniformLocation(Renderer::GetShaderProgramID(), "WorldTransform");
	glUniformMatrix4fv(WorldMatrixLocation, 1, GL_FALSE, &GetWorldMatrix()[0][0]);

	// 1st attribute buffer : vertex Positions
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, mVertexBufferID);
	glVertexAttribPointer(0,				// attribute. No particular reason for 0, but must match the layout in the shader.
		3,				// size
		GL_FLOAT,		// type
		GL_FALSE,		// normalized?
		sizeof(Vertex), // stride
		(void*)0        // array buffer offset
		);

	// 2nd attribute buffer : vertex normal
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, mVertexBufferID);
	glVertexAttribPointer(1,
		3,
		GL_FLOAT,
		GL_FALSE,
		sizeof(Vertex),
		(void*)sizeof(vec3)    // Normal is Offseted by vec3 (see class Vertex)
		);


	// 3rd attribute buffer : vertex color
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, mVertexBufferID);
	glVertexAttribPointer(2,
		3,
		GL_FLOAT,
		GL_FALSE,
		sizeof(Vertex),
		(void*)(2 * sizeof(vec3)) // Color is Offseted by 2 vec3 (see class Vertex)
		);

	//index buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBufferID);

	// Draw the triangles !
	glDrawElements(GL_TRIANGLE_STRIP, indexCount, GL_UNSIGNED_SHORT, (void*) 0);

	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);
}

bool Plane::ParseLine(const std::vector<ci_string> &token)
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

std::vector<glm::vec3>* Plane::getVertexBuffer(){
	return &(Plane::vertexBuffer);
}
