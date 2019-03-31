#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <GL/glew.h>

#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

class Shader
{
	public:

		unsigned int id;

		GLuint VBO;
		GLuint VAO;
		GLuint EBO;

		Shader(const char* vertexPath, const char* fragmentPath, const char* geometryPath = nullptr);

		void Use();

		void SetBool(const std::string &name, bool value) const;
		void SetInt(const std::string& name, int value) const;
		void SetFloat(const std::string& name, float value) const;
		void SetVec3(const std::string& name, glm::vec3 value) const;
		void SetMatrix(const std::string& name, glm::mat4 value) const;
		void CheckCompileErrors(unsigned int shader, std::string type);

		void EnableBuffer(float* vertices, size_t verticeSize, int* indices, size_t indiceSize);
		void DeletBuffer();
};		
