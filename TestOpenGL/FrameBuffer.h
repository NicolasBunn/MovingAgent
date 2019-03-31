#pragma once

#include <GL/glew.h>

class FrameBuffer
{
	public:
		unsigned int depthMapFBO;
		unsigned int depthMap;

		float frameBufferWidth;
		float frameBufferHeight;
		
		FrameBuffer(const float width, const float height);
		void BindFrameBuffer();


};
