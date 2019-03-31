#include "Plane.h"

Plane::Plane()
{
	vertices = new float[48]{
		 3.0f, -0.5f,  3.0f,  0.0f, 1.0f, 0.0f,  5.0f,  0.0f,
		-3.0f, -0.5f,  3.0f,  0.0f, 1.0f, 0.0f,   0.0f,  0.0f,
		-3.0f, -0.5f, -3.0f,  0.0f, 1.0f, 0.0f,   0.0f, 5.0f,

		 3.0f, -0.5f,  3.0f,  0.0f, 1.0f, 0.0f,  5.0f,  0.0f,
		-3.0f, -0.5f, -3.0f,  0.0f, 1.0f, 0.0f,   0.0f, 5.0f,
		 3.0f, -0.5f, -3.0f,  0.0f, 1.0f, 0.0f,  5.0f, 5.0f
	};

}

Plane::~Plane()
{
	delete vertices;
	delete indices;
}

size_t Plane::VerticeSize() const
{
	return sizeof(float) * 48;
}

size_t Plane::IndiceSize() const
{
	return sizeof(indices) * 6;
}

void Plane::SetShader(Shader& shader)
{
	shapeShader = new Shader(shader);
}

void Plane::InitBuffer()
{
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 48, vertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glBindVertexArray(0);
}

void  Plane::InitBufferWithData()
{

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glBindVertexArray(0);
}

void Plane::Draw()
{
	glDrawArrays(GL_TRIANGLES, 0, 6);
}