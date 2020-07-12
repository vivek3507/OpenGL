
VERTEX_SHADER

#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec4 colorV;

out vec4 colorVS;

uniform mat4 u_MVP; //model view projection matrix

void main()
{
	gl_Position = u_MVP * position;
	colorVS = colorV;
};


PIXEL_SHADER

#version 330 core

layout(location = 0) out vec4 color;
in vec4 colorVS;

void main()
{
	//color = vec4(1.0, 0.6, 0.1, 1.0);
	color = colorVS;
};