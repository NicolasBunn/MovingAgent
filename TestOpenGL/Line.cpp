#include "Line.h"

Line::Line()
{
	vertices = new float[numbVertices]
	{
		0.0f, 0.0f, 0.0f,
		5.0f, 0.0f, 0.0f,
	};

}

Line::~Line()
{
	delete vertices;
}

size_t Line::VerticeSize() const
{
	return sizeof(float) * numbVertices;
}

void Line::SetShader(Shader& shader)
{
	shapeShader = new Shader(shader);
}

void Line::InitBuffer()
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

void Line::Draw()
{
	/*glm::vec4 a(vertices[0], vertices[1], vertices[2],1.0f);
	glm::vec4 b(vertices[3], vertices[4], vertices[5],1.0f);

	a = transform * a;
	b = transform * b;*/

	glDrawArrays(GL_LINES, 0, 2);
}

