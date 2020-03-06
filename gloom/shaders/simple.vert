#version 430 core

layout(location=0) in vec3 position;
layout(location=1) in vec4 col;
/* layout(location=2) in vec2 texCoord; */
layout(location=3) in vec3 normal;

out vec4 fragmentCol;
out vec2 TexCoord;
out vec3 fragmentNormal;
out vec3 fragmentPos;


uniform float incrementor;

uniform mat4x4 view;
uniform mat4x4 model;
uniform mat4x4 projection;

void main()
{   
	gl_Position = projection * view * model * vec4(position, 1.0f); 

	fragmentCol = col;
	/* fragmentNormal = normalize(mat3(model) * normal); */ 
	fragmentNormal = mat3(transpose(inverse(model))) * normal;
	/* fragmentNormal = normal; */
	fragmentPos = vec3(model * vec4(position, 1.0));

	/* TexCoord = texCoord; */
}
