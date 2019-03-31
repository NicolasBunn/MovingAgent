#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "Shape.h"

class Line : public Shape
{
public:
	Line();
	~Line();

	float *vertices;

	const int numbVertices = 6;

	void SetShader(Shader& shader) override;
	void InitBuffer() override;

	size_t VerticeSize() const;

	void Draw() override;

};