#include <fstream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Renderer.h"

#include "Texture.h"
#include "stb_image.h"


Texture::Texture(std::string fileName)
{
	m_path = fileName;
	//stbi has bottom-left as (0,0) while for openeGL it is top-left
	stbi_set_flip_vertically_on_load(true);

	m_localBuffer = stbi_load(m_path.c_str(), &m_width, &m_height, &m_BPP, 4);
	if (!m_localBuffer) {
		std::cout << "Texture loading error." << std::endl;
		return;
	}
	//std::cout << "m_BPP:" << m_BPP << std::endl;

	GL_CALL(glGenTextures(1, &m_objectId));
	//GL_CALL(glBindTexture(GL_TEXTURE_2D, m_objectId));

	//set textute parameters
	//GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	//GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	//GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE)); //x
	//GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE)); //y

	//GL_CALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_localBuffer));

	//pic the texture slot
	//glActiveTexture(GL_TEXTURE0);
	//unbind it in the end
	//GL_CALL(glBindTexture(GL_TEXTURE_2D, 0));

	/*if (m_localBuffer) {
		stbi_image_free(m_localBuffer);
	}*/
}

Texture::Texture(Texture&& src)
{
	std::cout << "Move constructor called." << std::endl;
	m_path = src.m_path;
	m_width = src.m_width;
	m_height = src.m_height;
	m_BPP = src.m_BPP;

	m_localBuffer = src.m_localBuffer;

	m_objectId = src.m_objectId;

	src.m_objectId = 0;
	src.m_localBuffer = 0;
}


Texture::~Texture()
{
	std::cout << "Deleting the texture." << std::endl;
	if (m_objectId)
		GL_CALL(glDeleteTextures(1, &m_objectId));
	if (m_localBuffer) {
		stbi_image_free(m_localBuffer);
		m_localBuffer = 0;
	}
}

void Texture::bind(unsigned int slot /* = 0*/)
{
	//pic the texture slot
	glActiveTexture(GL_TEXTURE0 + slot);
	GL_CALL(glBindTexture(GL_TEXTURE_2D, m_objectId));

	//set textute parameters
	GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE)); //x
	GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE)); //y

	GL_CALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_localBuffer));

	//GL_CALL(glBindTextureUnit(slot, m_objectId));
}

void Texture::unbind()
{
	GL_CALL(glBindTexture(GL_TEXTURE_2D, 0));
}
