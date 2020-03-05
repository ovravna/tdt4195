#version 430 core

out vec4 color;

in vec4 fragmentCol;
in vec2 TexCoord;

uniform sampler2D myTexture;

void main()
{
    /* color = vec4(1, 0, 0, 1); */
    color = fragmentCol;
    /* color = texture(myTexture, TexCoord); */
	
}
