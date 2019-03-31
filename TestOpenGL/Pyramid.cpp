#include "Pyramid.h"

Pyramid::Pyramid()
{
	vertices = new float[numbVertices]
	{
		//Front
		-1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		0.0f, 1.0f, -0.5f,

		//Behind
		-1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		 0.0f, 1.0f, -0.5f,

		//Left
		0.0f, 1.0f, -0.5f,
		-1.0f, -1.0f, 0.0f,
		-1.0f, -1.0f, -1.0f,

		//Right
		0.0f, 1.0f, -0.5f,
		1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, -1.0f,

		-1.0,-1.0,0.0f,
		1.0f,-1.0f,0.0f,
		1.0f,-1.0f,-1.0f,

		-1.0, -1.0, 0.0f,
		1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
	};

}

Pyramid::~Pyramid()
{
	delete vertices;
}

size_t Pyramid::VerticeSize() const
{
	return sizeof(float) * numbVertices;
}

void Pyramid::SetShader(Shader& shader)
{
	shapeShader = new Shader(shader);
}

void Pyramid::InitBuffer()
{
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * numbVertices, vertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glBindVertexArray(0);


}

void Pyramid::Draw()
{
	glDrawArrays(GL_TRIANGLES, 0, 12);
}

