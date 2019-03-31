#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "Shape.h"

class Cube : public Shape
{
public:
	Cube();
	~Cube();

	float* vertices;
	int* indices;

	void SetShader(Shader& shader) override;
	void InitBuffer() override;

	size_t VerticeSize() const;
	size_t IndiceSize() const;

	float* Vertices() const;
	int* Indices() const;

	void Draw() override;

};
