#version 330

layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in vec3 aNormal;

out vec2 fTexCoord;
out vec3 fFragPos;
out vec3 fNormal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position =  projection * view * model * vec4(aPosition,1.0f);
	fTexCoord = vec2(aTexCoord.x, aTexCoord.y);
	fNormal = mat3(transpose(inverse(model))) * aNormal;
	fFragPos = vec3(model * vec4(aPosition,1.0));
}