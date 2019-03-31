#version 330

in vec2 fTexCoord;

out vec4 color;

uniform sampler2D texture1;

void main()
{
    color = texture(texture1,fTexCoord);
}