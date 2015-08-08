#pragma once

#include "Model.h"

class Plane : public Model
{
public:
	Plane(int side);
	virtual ~Plane();

	virtual void Update(float dt);
	virtual void Draw();

	std::vector<glm::vec3>* getVertexBuffer();

protected:
	virtual bool ParseLine(const std::vector<ci_string> &token);

private:
	// The vertex format could be different for different types of models
	struct Vertex
	{
		glm::vec3 position;
		glm::vec3 normal;
		glm::vec3 color;
	};
	std::vector<glm::vec3> vertexBuffer;
	unsigned int mVertexArrayID;
	unsigned int mVertexBufferID;
	unsigned int mIndexBufferID;
	int indexCount;
	int side;
};
