#version 430 core

layout(location=0) in vec3 position;
layout(location=1) in vec4 col;

out vec4 fragmentCol;
void main()
{
    gl_Position = vec4(position, 1.0f);
	fragmentCol = col;
}
