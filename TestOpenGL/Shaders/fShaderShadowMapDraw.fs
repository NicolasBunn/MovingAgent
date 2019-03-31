#version 330

out vec4 fragColor;

in vec2 fTexCoords;

uniform sampler2D depthMap;
uniform float nearPlane;
uniform float farPlane;

float LinearizeDepth(float depth)
{
	float z = depth * 2.0 - 1.0;
	return (2.0 * nearPlane * farPlane) / (farPlane + nearPlane - z * (farPlane - nearPlane));	
}

void main()
{
	float depthValue = texture(depthMap,fTexCoords).r;
	fragColor = vec4(vec3(depthValue),1.0);
}