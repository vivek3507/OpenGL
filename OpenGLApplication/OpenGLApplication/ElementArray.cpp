#include "ElementArray.h"
#include "Renderer.h"

ElementArray::ElementArray()
{
	m_count = 0;
	GL_CALL(glGenBuffers(1, &m_objectId));
}

ElementArray::~ElementArray()
{
	GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}

void ElementArray::bind() const
{
	GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_objectId));
}

void ElementArray::unbind() const
{
	GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}

void ElementArray::setIndexBufferData(size_t count, unsigned int * indices)
{
	m_count = count;
	GL_CALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), (void*)indices, GL_STATIC_DRAW));
}

size_t ElementArray::getCount() const
{
	return m_count;
}