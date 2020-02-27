#version 430 core

out vec4 color;
in vec4 fragmentCol;

void main()
{
    color = fragmentCol;
}
