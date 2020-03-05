#version 430 core

out vec4 color;

in vec4 fragmentCol;
in vec2 TexCoord;
in vec3 fragmentNormal;

vec3 lightDirection = normalize(vec3(0.8, -0.5, 0.6));
uniform sampler2D myTexture;
vec3 c;

void main()
{
    /* color = vec4(1, 0, 0, 1); */
	c = vec3(1, 0, 0) * max(vec3(0), fragmentNormal * -lightDirection);
    color = vec4(c, 1.0);
    /* color = texture(myTexture, TexCoord); */
	
}
