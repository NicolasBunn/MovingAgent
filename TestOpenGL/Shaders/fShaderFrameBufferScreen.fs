#version 330

out vec4 fragColor;
in  vec2 fTexCoord;

uniform sampler2D screenTexture;

void main()
{
	fragColor = vec4(vec3(1.0 - texture(screenTexture,fTexCoord)),1.0);
}

