#pragma once
#include "GLBase.h"

class VertexBuffer : public GLBase
{
public:
	VertexBuffer();
	~VertexBuffer();

	void setBufferData(size_t count, float* vertices);
	void bind() const;
	void unbind() const;

};

