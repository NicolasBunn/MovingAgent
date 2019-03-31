#version 330

in vec2 fTexCoords;

out vec4 fragColor;

uniform sampler2D text;
uniform vec3 textColor;

void main()
{
    vec4 sampled = vec4(1.0f,1.0f,1.0f,texture(text,fTexCoords).r);
	fragColor = vec4(textColor,1.0f) * sampled;
}