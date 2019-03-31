#pragma once

#include "glm/gtc/matrix_transform.hpp"
#include <string>
#include <GL/glew.h>
#include "Shader.h"
#include "Collision.h"

class Shape
{
public:
	Shape();
	~Shape();

	Shader* shapeShader;

	glm::vec3 shapeColor;
	glm::mat4 transform;

	GLuint vbo;
	GLuint vao;

	void ShaderUse();
	virtual void SetShader(Shader& shader) = 0;
	virtual void InitBuffer();
	
	void SetShaderBool(const std::string &name, bool value) const;
	void SetShaderInt(const std::string& name, int value) const;
	void SetShaderFloat(const std::string& name, float value) const;
	void SetVec3(const std::string& name, glm::vec3 value) const;
	void SetShaderMatrix(const std::string& name, glm::mat4 value) const;

	void SetColor(const glm::vec3 color);

	virtual Collision::LineCollision* GetEntityCollision() const;

	virtual void Draw() = 0;

};