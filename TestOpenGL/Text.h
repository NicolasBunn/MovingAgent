#pragma once

#include <map>
#include <GL/glew.h>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "ft2build.h"
#include FT_FREETYPE_H

#include "Shader.h"

class Text
{
	public:

		struct Character
		{
			GLuint textureID;
			glm::ivec2 size;
			glm::ivec2 bearing; // offset from baseline to left/top glyph
			GLuint advance;
		};

		Text();
		void LoadFont(const char* fontPath);
		void SetPixelSize(const FT_UInt width, const FT_UInt height);
		void LoadCharacter();
		void RenderText(Shader& shader, std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color);
		void InitBuffer();
		void Done();

		FT_Library ft;
		FT_Face face;
		GLuint vao, vbo;
		std::map<GLchar, Character> characters;

};