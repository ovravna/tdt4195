#version 430 core

out vec4 color;
uniform vec4 myUniform;
void main()
{
    color = myUniform;
}
