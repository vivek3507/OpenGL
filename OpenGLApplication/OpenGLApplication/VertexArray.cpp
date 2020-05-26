#include "VertexArray.h"
#include "Renderer.h"

VertexArray::VertexArray()
{
	GL_CALL(glGenVertexArrays(1, &m_objectId));
}

void VertexArray::bind() const
{
	GL_CALL(glBindVertexArray(m_objectId));
}

void VertexArray::unbind() const
{
	GL_CALL(glBindVertexArray(0));
}

void VertexArray::setBufferLayout(BufferLayout& blay)
{
	bind();

	std::vector<BufferLayoutUnit>& elems = blay.getBufferLayoutUnits();
	unsigned int offset = 0;
	for (auto& ele : elems) {
		unsigned int vAttribP = 0;
		if (ele.isName) {
			GL_CALL(vAttribP = glGetAttribLocation(ele.program, ele.attribName.c_str()));
		}
		else {
			vAttribP = ele.location;
		}
		GL_CALL(glVertexAttribPointer(vAttribP, ele.count, ele.type, ele.isNormalised,
			blay.getStride(), (void*)offset));
		offset += ele.count * BufferLayoutUnit::getSizeOfType(ele.type);
		GL_CALL(glEnableVertexAttribArray(vAttribP));
	}
}

VertexArray::~VertexArray()
{
	GL_CALL(glDeleteVertexArrays(1, &m_objectId));
}
