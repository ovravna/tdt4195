#version 430 core

layout(location=0) in vec3 position;
layout(location=1) in vec4 col;

out vec4 fragmentCol;

mat4 matrixVariable;

uniform float osilator;
uniform float incrementor;

uniform mat4x4 viewMatrix;


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

	float cosx = cos(incrementor);
	float sinx = sin(incrementor);

	// Y-axis rotation
	mat4x4 yRot = mat4x4(1);
	yRot[0][0] = cosx;
	yRot[2][0] = -sinx;
	yRot[0][2] = sinx;
	yRot[2][2] = cosx;

	// X-axis rotation
	mat4x4 xRot = mat4x4(1);
	xRot[1][1] = cosx;
	xRot[2][1] = sinx;
	xRot[1][2] = -sinx;
	xRot[2][2] = cosx;

	// Z-axis rotation
	mat4x4 zRot = mat4x4(1);
	zRot[0][0] = cosx;
	zRot[1][0] = sinx;
	zRot[0][1] = -sinx;
	zRot[1][1] = cosx;
	
	mat4x4 scale = mat4x4(1);
	float w = 0.5;
	scale[0][0] = w;
	scale[1][1] = w;
	scale[2][2] = w;


	mat4x4 movement = mat4x4(1);
	float r = 0.5;
	movement[0][3] = r * cosx;
	movement[1][3] = r * sinx;

	mat4x4 transform = movement * scale * xRot * yRot * viewMatrix;

    gl_Position = vec4(position, 1.0f) * transform; 
	fragmentCol = col;
}
