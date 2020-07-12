
VERTEX_SHADER

#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoord;
layout(location = 2) in float texId;

out vec2 v_TexCoord;
out float v_TexId;

uniform mat4 u_MVP; //model view projection matrix

void main()
{
	gl_Position = u_MVP * position;
	v_TexCoord = texCoord;
	v_TexId = texId;
};


PIXEL_SHADER

#version 330 core

layout(location = 0) out vec4 color;

in vec2 v_TexCoord;
in float v_TexId;

//uniform vec4 inUColor;
uniform sampler2D u_Texture[2];
uniform sampler2D u_TextureA;
uniform sampler2D u_TextureB;
void main()
{
	//int index = int(v_TexId);
	//color = vec4(index, index, index, 1.0);
	
	int index = int(v_TexId);
	//Below indexing is not possible with, seems like it should be compile time constant, will look further into it.
	//color = texture(u_Texture[index], v_TexCoord);
	
	if (index == 0)
		color = texture(u_Texture[0], v_TexCoord);
	else 
		color = texture(u_Texture[1], v_TexCoord);

	/*if (index == 0)
		color = texture(u_TextureA, v_TexCoord);
	else 
		color = texture(u_TextureB, v_TexCoord);*/
};