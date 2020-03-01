#version 430 core

layout(location=0) in vec3 position;
layout(location=1) in vec4 col;

out vec4 fragmentCol;

mat4 matrixVariable;

uniform float osilator;
uniform float incrementor;


mat4x4 matrix = {
	{ 1, 0, 0, 0 },
	{ 0, 1, 0, 0 },
	{ 0, 0, 1, 0 },
	{ 0, 0, 0, 1 }
};

mat4x4 angleX = {
	{ 0, 0, 0, 0 },
	{ 0, 0.95, 0.3, 0 },
	{ 0, -0.3, 0.95, 0 },
	{ 0, 0, 0, 0 }
};

void main()
{
	/* matrixVariable[0] = vec4(1, 0, 0, 0); */
	/* matrixVariable[1] = vec4(0, 1, 0, 0); */
	/* matrixVariable[2] = vec4(0, 0, 1, 0); */
	/* matrixVariable[3] = vec4(0, 0, 0, 1); */

	// Y-axis rotation
	mat4x4 yRot = mat4x4(1);
	yRot[0][0] = cos(incrementor);
	yRot[2][0] = -sin(incrementor);
	yRot[0][2] = sin(incrementor);
	yRot[2][2] = cos(incrementor);

	// X-axis rotation
	mat4x4 xRot = mat4x4(1);
	xRot[1][1] = cos(incrementor);
	xRot[2][1] = sin(incrementor);
	xRot[1][2] = -sin(incrementor);
	xRot[2][2] = cos(incrementor);

	// Z-axis rotation
	mat4x4 zRot = mat4x4(1);
	zRot[0][0] = cos(incrementor);
	zRot[1][0] = sin(incrementor);
	zRot[0][1] = -sin(incrementor);
	zRot[1][1] = cos(incrementor);
	


    gl_Position = vec4(position, 1.0f) * xRot * yRot * zRot; //* angleX;
	fragmentCol = col;
}
