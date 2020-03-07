#version 430 core

out vec4 color;

in vec4 fragmentCol;
in vec2 TexCoord;
in vec3 fragmentNormal;
in vec3 fragmentPos;

vec3 lightDirection = normalize(vec3(0.8, -0.5, 0.6));
uniform vec3 light_pos; // = vec3(20, 20, 10);
uniform sampler2D myTexture;

uniform vec3 viewPos;
vec3 c;

float ambientStrength = 0.1;

vec3 ambientColor = vec3(1, 1, 1);
vec3 ambient = ambientColor * ambientStrength;

vec3 diffuseColor = vec3(1, 1, 1);

float specularStrength = 0.7;
vec3 specularColor = vec3(1, 1, 1);

void main()
{
	

	//diffuse 
	vec3 lightDir = normalize(light_pos - fragmentPos);
	vec3 norm = normalize(fragmentNormal);
	float diff = clamp(dot(norm, lightDir), 0.0, 1.0);
	vec3 diffuse = diff * diffuseColor;

	//specular
	vec3 viewDir = normalize(viewPos - fragmentPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 1024);
	vec3 specular = specularStrength * spec * specularColor;

	c = (ambient + diffuse + specular) * fragmentCol.rgb;
	/* c *= diffuse; */
	/* c *= ambient;  // ambient lighting */
	/* c *= max(0, dot(fragmentNormal, -lightDirection)); */ 

	color = vec4(c, 1.0);
	
}



    /* color = texture(myTexture, TexCoord); */
