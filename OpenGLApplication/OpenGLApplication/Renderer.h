#pragma once

#include <iostream>
#include <assert.h>

#include "VertexArray.h"
#include "ElementArray.h"
#include "Shaders.h"

#define GL_CALL(x)\
x;\
{\
unsigned int errorCode = glGetError();\
if(errorCode) {\
	std::cout << "Error " << errorCode << " encountered in file " << __FILE__ << " at line no " << __LINE__ << std::endl;\
	assert(0);\
}\
}

class Renderer
{

public:
	Renderer();
	~Renderer();

	void Draw(const VertexArray& va, const ElementArray& ea, const Shaders& sh) const;
	void clear() const;

};