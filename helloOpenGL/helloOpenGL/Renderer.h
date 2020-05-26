#pragma once


#define GL_CALL(x)\
x;\
{\
unsigned int errorCode = glGetError();\
if(errorCode) {\
	std::cout << "Error " << errorCode << " encountered in file " << __FILE__ << " at line no " << __LINE__ << std::endl;\
	assert(0);\
}\
}