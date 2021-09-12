#version 400 core

layout (location = 0) in vec4 vPosition;
layout (location = 1) in vec4 inColor;

out vec4 outColor;

void
main()
{
    gl_Position = vPosition;
	outColor = inColor;
}
