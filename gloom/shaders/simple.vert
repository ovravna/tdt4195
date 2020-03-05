#version 430 core

layout(location=0) in vec3 position;
layout(location=1) in vec4 col;
/* layout(location=2) in vec2 texCoord; */

out vec4 fragmentCol;
out vec2 TexCoord;

uniform mat4x4 view;
uniform mat4x4 model;
uniform mat4x4 projection;

void main()
{   
	gl_Position = projection * view * model * vec4(position, 1.0f); 

	fragmentCol = col;
	/* TexCoord = texCoord; */
}
