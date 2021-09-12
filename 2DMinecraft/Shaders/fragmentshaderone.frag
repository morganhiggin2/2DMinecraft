#version 400 core

layout (location = 0) out vec4 fColor;

in vec4 outColor;

void main()
{
    fColor = outColor;
}
