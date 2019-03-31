#pragma once

#include "Shape.h"
#include "Texture.h"

class Skybox : public Shape
{
	public:

		Skybox();
		~Skybox();

		float* vertices;
		int* indices;
		unsigned int cubemapTexture;

		void SetShader(Shader& shader) override;
		void InitBuffer() override;
		void LoadCubemapTexture();

		size_t VerticeSize() const;
		size_t IndiceSize() const;

		void Draw() override;
};