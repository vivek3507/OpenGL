
VERTEX_SHADER

#version 330 core

layout(location = 0) in vec4 position;

void main()
{
	gl_Position = position;
};


PIXEL_SHADER

#version 330 core

layout(location = 0) out vec4 color;
uniform vec4 inUColor;

void main()
{
	//color = vec4(1.0, 0.0, 0.0, 1.0);
	color = inUColor;
};