#include <iostream>
#include <assert.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Renderer.h"

#include "VertexBuffer.h"

VertexBuffer::VertexBuffer()
{
	GL_CALL(glGenBuffers(1, &m_objectId));
}

VertexBuffer::~VertexBuffer()
{
	GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

void VertexBuffer::setBufferData(size_t count, float * vertices, bool isDynamic)
{
	if (isDynamic) {
		//ready for dynamic data, by giving nullptr and later filling the data
		GL_CALL(glBufferData(GL_ARRAY_BUFFER, count * sizeof(float), nullptr, GL_DYNAMIC_DRAW));
	}
	else {
		GL_CALL(glBufferData(GL_ARRAY_BUFFER, count * sizeof(float), vertices, GL_STATIC_DRAW));
	}
}

void VertexBuffer::setBufferDataDynamic(size_t size, float * vertices)
{
	glBufferSubData(GL_ARRAY_BUFFER, 0, size, vertices);
}

void VertexBuffer::bind() const
{
	GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, m_objectId));
}

void VertexBuffer::unbind() const
{
	GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, 0));
}
