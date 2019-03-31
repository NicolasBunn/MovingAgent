#include "Square.h"

Square::Square()
{
	vertices = new float[numbVertices]
	{
		-0.025f, 0.025f, 0.0f,
		-0.025f, -0.025f, 0.0f,
		 0.025f, -0.025f, 0.0f,

		-0.025f, 0.025f, 0.0f,
		0.025f, -0.025f, 0.0f,
		0.025f, 0.025f, 0.0f,
	};

}

Square::~Square()
{
	delete vertices;
}

size_t Square::VerticeSize() const
{
	return sizeof(float) * numbVertices;
}

void Square::SetShader(Shader& shader)
{
	shapeShader = new Shader(shader);
}

void Square::InitBuffer()
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

void Square::Draw()
{
	glDrawArrays(GL_TRIANGLES, 0, 6);
}

