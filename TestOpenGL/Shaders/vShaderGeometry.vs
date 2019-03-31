#version 330

layout (location = 0) in vec2 aPosition;
layout (location = 1) in vec3 aColor;

out VS_OUT
{
	vec3 color;
}vs_out;

void main()
{
	vs_out.color = aColor;
    gl_Position =  vec4(aPosition.x,aPosition.y,0.0,1.0);

}