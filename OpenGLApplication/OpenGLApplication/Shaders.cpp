#include "Shaders.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "Renderer.h"

Shaders::Shaders(const std::string& fileProgram)
{
	m_programFile = fileProgram;
	m_objectId = getProgram();
}

Shaders::~Shaders()
{
	if (m_objectId) GL_CALL(glDeleteProgram(m_objectId));
}

unsigned int Shaders::compileShader(unsigned int type, const std::string& source)
{
	GL_CALL(unsigned int id = glCreateShader(type));
	const char* src = source.c_str();
	GL_CALL(glShaderSource(id, 1, &src, NULL));
	GL_CALL(glCompileShader(id));

	//Error handling
	int compile_status;
	GL_CALL(glGetShaderiv(id, GL_COMPILE_STATUS, &compile_status));

	if (compile_status == GL_FALSE) {
		int log_length = 0;
		GL_CALL(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &log_length));
		char* message = (char*)alloca(log_length * sizeof(char));
		GL_CALL(glGetShaderInfoLog(id, log_length, &log_length, message));

		std::cout << "Error occured..." << std::endl;
		std::cout << message << std::endl;
	}

	return id;
}

unsigned int Shaders::makeProgram(const std::string& vertexShader, const std::string& fragmentShader)
{
	//get code
	//compile
	//combine

	GL_CALL(unsigned int program = glCreateProgram());
	GL_CALL(unsigned int vs = compileShader(GL_VERTEX_SHADER, vertexShader));
	GL_CALL(unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragmentShader));

	GL_CALL(glAttachShader(program, vs));
	GL_CALL(glAttachShader(program, fs));

	GL_CALL(glLinkProgram(program));
	GL_CALL(glValidateProgram(program));

	GL_CALL(glDeleteShader(vs));
	GL_CALL(glDeleteShader(fs));

	return program;
}


Shaders::Shader& Shaders::parseShader(std::string& filePath)
{
	std::ifstream vsFileStream;
	SHADER_TYPE type = SH_NONE;
	std::ostringstream sh[2];
	vsFileStream.open(filePath, std::ifstream::in);
	std::string line;
	if (vsFileStream.is_open())
	{
		while (getline(vsFileStream, line)) {
			if (line.find("VERTEX_SHADER") != std::string::npos) {
				type = SH_VERTEX;
				continue;
			}
			if (line.find("PIXEL_SHADER") != std::string::npos) {
				type = SH_PIXEL;
				continue;
			}
			if (type > -1) sh[type] << line << std::endl;
		}
		vsFileStream.close();
	}

	std::cout << sh[0].str();
	std::cout << sh[1].str();

	//1
	//return { sh[0].str(), sh[1].str() }; \\initializer list

	//2
	/*Shader resSh;
	resSh.vs = sh[0].str();
	resSh.fs = sh[1].str();
	return resSh;*/

	//3
	Shader* shP = new Shader;
	shP->vs = sh[0].str();
	shP->fs = sh[1].str();

	return *shP;

}

unsigned int Shaders::getProgram()
{
	Shader& sh = parseShader(m_programFile);
	m_objectId = makeProgram(sh.vs, sh.fs);

	return m_objectId;
}

void Shaders::bind() const
{
	GL_CALL(glUseProgram(m_objectId));
}

void Shaders::unbind() const
{
	GL_CALL(glUseProgram(0));
}
unsigned int Shaders::getProgramId()
{
	return m_objectId;
}

int Shaders::getUniform(const std::string name) const
{
	if (m_uniforms.find(name) != m_uniforms.end()) {
		return m_uniforms[name];
	}
	GL_CALL(int cLoc = glGetUniformLocation(m_objectId, name.c_str()));
	if (cLoc == -1)  assert(0);
	m_uniforms[name] = cLoc;

	return cLoc;
}

void Shaders::setUniform4f(unsigned int cLoc, float val1, float val2, float val3, float val4)
{
	if (cLoc >= 0) {
		GL_CALL(glUniform4f(cLoc, val1, val2, val3, val4));
	}
}

void Shaders::setUniformMat4f(unsigned int cLoc, const glm::mat4 mat)
{
	if (cLoc >= 0) {
		//matirx is already coloum major
		GL_CALL(glUniformMatrix4fv(cLoc, 1, GL_FALSE, &mat[0][0]));
	}
}

void Shaders::setUniform1i(unsigned int cLoc, int val)
{
	if (cLoc >= 0) {
		GL_CALL(glUniform1i(cLoc, val));
	}
}

void Shaders::setUniform1iv(unsigned int cLoc, int* val, int size)
{
	if (cLoc >= 0) {
		GL_CALL(glUniform1iv(cLoc, size, val));
	}
}
