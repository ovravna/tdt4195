#version 430 core

out vec4 color;

in vec4 fragmentCol;
in vec2 TexCoord;
in vec3 fragmentNormal;

uniform sampler2D myTexture;

void main()
{
    /* color = vec4(1, 0, 0, 1); */
    color = vec4(fragmentNormal, 1.0);
    /* color = texture(myTexture, TexCoord); */
	
}
