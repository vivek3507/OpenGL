#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>


#include "GLBase.h"

class ElementArray : public GLBase
{
	size_t m_count;
public:
	ElementArray();
	~ElementArray();

	void bind() const;
	void unbind() const;

	void setIndexBufferData(size_t count, unsigned int * indices);
	size_t getCount() const;
};

