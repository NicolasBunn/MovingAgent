#pragma once

#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "Shape.h"
#include "Collision.h"

class Wall : public Shape
{
public:
	Wall();
	~Wall();

	float *vertices;

	const int numbVertices = 18;

	void SetShader(Shader& shader) override;
	void InitBuffer() override;

	size_t VerticeSize() const;

	void Draw() override;

	Collision::LineCollision* GetEntityCollision() const override;

};