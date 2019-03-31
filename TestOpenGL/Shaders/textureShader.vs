#version 330

layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec2 aTexCoord;

out vec2 fTexCoord;

uniform mat4 transform;

void main()
{
    gl_Position =  transform * vec4(aPosition.x,aPosition.y,aPosition.z,1.0f);
	fTexCoord = vec2(aTexCoord.x, aTexCoord.y);
}