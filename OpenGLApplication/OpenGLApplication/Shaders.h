#pragma once

#include <string>
#include <unordered_map>

#include "GLBase.h"
#include "glm/glm.hpp"

class Shaders : public GLBase
{
	enum SHADER_TYPE { SH_NONE = -1, SH_VERTEX, SH_PIXEL };

	struct Shader {
		std::string vs;
		std::string fs;
	};

	std::string m_programFile;
	mutable std::unordered_map<std::string, int> m_uniforms;

	Shader& parseShader(std::string& filePath);
	unsigned int compileShader(unsigned int type, const std::string& source);
	unsigned int makeProgram(const std::string& vertexShader, const std::string& fragmentShader);
	unsigned int getProgram();


public:
	Shaders(const std::string& fileProgram);
	~Shaders();


	void bind() const;
	void unbind() const;

	unsigned int getProgramId();
	
	int getUniform(const std::string name) const;
	void setUniform4f(unsigned int cLoc, float val1, float val2, float val3, float val4);
	void setUniformMat4f(unsigned int cLoc, const glm::mat4 mat);
	void setUniform1i(unsigned int cLoc, int val);
};

