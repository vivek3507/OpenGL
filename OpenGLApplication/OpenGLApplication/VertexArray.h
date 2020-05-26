#pragma once
#include "GLBase.h"
#include  "BufferLayout.h"

class VertexArray : public GLBase
{
	BufferLayout m_buffLayout;

public:
	VertexArray();
	~VertexArray();

	void bind() const;
	void unbind() const;

	void setBufferLayout(BufferLayout& blay);
};


