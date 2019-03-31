#version 330

layout (location = 0) in vec4 aPosition;
out vec2 fTexCoords;

uniform mat4 projection;

void main()
{
    gl_Position = projection * vec4(aPosition.xy,0.0f,1.0f);
	fTexCoords = aPosition.zw;
}