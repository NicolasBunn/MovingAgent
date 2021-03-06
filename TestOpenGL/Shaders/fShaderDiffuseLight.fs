#version 330

struct Material
{
	sampler2D diffuse;
	vec3 specular;
	float shininess;
};

struct Light
{
	vec3 direction;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	
};

in vec2 fTexCoord;
in vec3 fNormal;
in vec3 fFragPos;

out vec4 color;

uniform sampler2D texture1;

uniform Material material;
uniform Light light;
uniform vec3 viewPos;

void main()
{
	vec3 ambient = light.ambient * texture(material.diffuse,fTexCoord).rgb;
	
	vec3 norm = normalize(fNormal);
	vec3 lightDir = normalize(-light.direction);
	float diff = max(dot(norm,lightDir), 0.0);
	vec3 diffuse = light.diffuse * diff * texture(material.diffuse,fTexCoord).rgb;

	vec3 viewDir = normalize(viewPos - fFragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir),0.0),material.shininess);
	vec3 specular = light.specular * (spec * material.specular);
	
	vec3 result = (ambient + diffuse + specular);
    color = vec4(result,1.0);
}