#version 330

layout (location = 0) in vec2 aPosition;
layout (location = 1) in vec2 aTexCoord;

out vec2 fTexCoord;

void main()
{
    gl_Position =  vec4(aPosition.x,aPosition.y,0.0,1.0);
	fTexCoord = aTexCoord;
}