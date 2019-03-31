#include "Wall.h"

Wall::Wall()
{
	vertices = new float[numbVertices]
	{
		-0.25f, 0.05f, 0.0f,
		-0.25f, 0.00f, 0.0f,
		0.25f, 0.00f, 0.0f,

		-0.25f, 0.05f, 0.0f,
		0.25f, 0.00f, 0.0f,
		0.25f, 0.05f, 0.0f,
	};

}

Wall::~Wall()
{
	delete vertices;
}

size_t Wall::VerticeSize() const
{
	return sizeof(float) * numbVertices;
}

void Wall::SetShader(Shader& shader)
{
	shapeShader = new Shader(shader);
}

void Wall::InitBuffer()
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

void Wall::Draw()
{
	glDrawArrays(GL_TRIANGLES, 0, 6);
}

Collision::LineCollision* Wall::GetEntityCollision() const
{
	Collision::LineCollision* tab = new Collision::LineCollision[2];

	Collision::LineCollision l1;
	glm::vec4 a = glm::vec4(vertices[0], vertices[1], vertices[2], 1.0f);
	glm::vec4 b = glm::vec4(vertices[6], vertices[7], vertices[8], 1.0f);

	a = transform * a;
	b = transform * b;

	l1.start = glm::vec3(a.x, a.y, a.z);
	l1.direction = glm::vec3(b.x, b.y, b.z);

	tab[0] = l1;

	Collision::LineCollision l2;
	a = glm::vec4(vertices[3], vertices[4], vertices[5], 1.0f);
	b = glm::vec4(vertices[15], vertices[16], vertices[17], 1.0f);

	a = transform * a;
	b = transform * b;

	l2.start = glm::vec3(a.x, a.y, a.z);
	l2.direction = glm::vec3(b.x, b.y, b.z);

	tab[1] = l2;

	return tab;
}

