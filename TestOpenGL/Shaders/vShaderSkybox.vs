#version 330

layout (location = 0) in vec3 aPosition;

out vec3 fTexCoord;

uniform mat4 projection;
uniform mat4 view;

void main()
{
	fTexCoord = aPosition;
	vec4 pos = projection * view * vec4(aPosition,1.0);
    gl_Position =  pos.xyww;

}