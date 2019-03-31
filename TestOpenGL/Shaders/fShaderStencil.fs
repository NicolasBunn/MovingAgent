#version 330

out vec4 fragColor;
in  vec2 fTexCoord;

uniform sampler2D texture1;

void main()
{
	fragColor = texture(texture1,fTexCoord);
}

