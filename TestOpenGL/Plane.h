#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "Shape.h"

class Plane : public Shape
{
public:
	Plane();
	~Plane();

	float* vertices;
	int* indices;

	void SetShader(Shader& shader) override;
	void InitBuffer() override;
	void InitBufferWithData();

	size_t VerticeSize() const;
	size_t IndiceSize() const;

	void Draw() override;
}; 
