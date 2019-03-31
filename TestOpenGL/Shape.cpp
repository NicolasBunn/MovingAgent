#include "Shape.h"
#include "Collision.h"

Shape::Shape()
	:shapeColor(glm::vec3(1.0f, 1.0f, 1.0f))
{

}

Shape::~Shape()
{
	delete shapeShader;
}

void Shape::ShaderUse()
{
	shapeShader->Use();
}

void  Shape::SetShaderBool(const std::string &name, bool value) const
{
	shapeShader->SetBool(name, value);
}

void  Shape::SetShaderInt(const std::string& name, int value) const
{
	shapeShader->SetInt(name, value);
}

void  Shape::SetShaderFloat(const std::string& name, float value) const
{
	shapeShader->SetFloat(name, value);
}

void Shape::SetVec3(const std::string& name, glm::vec3 value) const
{
	shapeShader->SetVec3(name, value);
}

void  Shape::SetShaderMatrix(const std::string& name, glm::mat4 value) const
{
	shapeShader->SetMatrix(name, value);
}

void Shape::SetColor(const glm::vec3 color)
{
	shapeColor = color;
}

void Shape::InitBuffer()
{

}

Collision::LineCollision* Shape::GetEntityCollision() const
{
	return nullptr;
}