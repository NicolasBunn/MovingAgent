#pragma once

#include <iostream>
#include <vector>

#include <GL/glew.h>

#include "stb_image.h"


class Texture
{

	public:
		static int LoadTexture(const char* path, bool alpha);
		static unsigned int LoadCubemap(std::vector<std::string> faces);

};
