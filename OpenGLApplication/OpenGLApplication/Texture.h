#pragma once
#include <string>
#include "GLBase.h"


class Texture :
	public GLBase
{
	std::string m_path;
	int m_width, m_height, m_BPP;
	unsigned char *m_localBuffer;

public:
	Texture(std::string path);
	~Texture();

	void bind(unsigned int slot = 0);
	void  unbind();
};

