#version 430 core

layout(location=0) in vec3 position;
layout(location=1) in vec4 col;

out vec4 fragmentCol;

mat4 matrixVariable;

uniform float osilator;


mat4x4 matrix = {
	{ 1, 0, 0, 0 },
	{ 0, 1, 0, 0 },
	{ 0, 0, 1, 0 },
	{ 0, 0, 0, 1 }
};

void main()
{
	/* matrixVariable[0] = vec4(1, 0, 0, 0); */
	/* matrixVariable[1] = vec4(0, 1, 0, 0); */
	/* matrixVariable[2] = vec4(0, 0, 1, 0); */
	/* matrixVariable[3] = vec4(0, 0, 0, 1); */
	matrix[0][1] = osilator;
	matrix[0][0] = 2*osilator;
	matrix[1][0] = 2*osilator;

    gl_Position = vec4(position, 1.0f) * matrix;
	fragmentCol = col;
}
