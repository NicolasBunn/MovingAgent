#version 330

out vec4 fragColor;
in  vec3 fTexCoord;

uniform samplerCube skybox;

void main()
{
	fragColor = texture(skybox,fTexCoord);
}

