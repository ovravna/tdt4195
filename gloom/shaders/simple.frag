#version 430 core

out vec4 color;
in vec4 fragmentCol;

void main()
{
    /* color = vec4(1, 0, 0, 1); */
    color = fragmentCol;
}
