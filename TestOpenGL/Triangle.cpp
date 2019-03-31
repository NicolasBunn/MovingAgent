#include "Triangle.h"

Triangle::Triangle()
{
	vertices = new float[numbVertices]
	{
		-0.25f, 0.25f, 0.0f,
		-0.25f, -0.25f, 0.0f,
		0.45f,  0.0f, 0.0f,
	};

}

Triangle::~Triangle()
{
	delete vertices;
}

size_t Triangle::VerticeSize() const
{
	return sizeof(float) * numbVertices;
}

void Triangle::SetShader(Shader& shader)
{
	shapeShader = new Shader(shader);
}

void Triangle::InitBuffer()
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

void Triangle::Draw()
{
	glDrawArrays(GL_TRIANGLES, 0, 3);
}

