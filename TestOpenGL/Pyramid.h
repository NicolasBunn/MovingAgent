#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "Shape.h"

class Pyramid : public Shape
{
public:
	Pyramid();
	~Pyramid();

	float *vertices;

	const int numbVertices = 55;

	void SetShader(Shader& shader) override;
	void InitBuffer() override;

	size_t VerticeSize() const;

	void Draw() override;

};