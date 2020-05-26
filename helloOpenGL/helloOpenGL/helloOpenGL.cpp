#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stdio.h>
#include <assert.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Renderer.h"


//Modern OpenGL
//Graphics rendering
//									Setup Vertex Array
//									|
//									v
//									Setup Data Buffer
//									|
//								    v
//									Setup Data Layout (Setup Array Attributes)
//									|
//									v
//									glUseProgram <-- Link Program <-- Attach Compiled Shaders To a Program |<--- Compile Shader  <-- Create Shader Container <-- Supply Vertex Shader Code as Text
//									|																	   |	
//									|																	   |<--- Compile Shader  <-- Create Shader Container <-- Supply Fragment Shader Code as Text
//									v
//									glDrawArrays(GL_TRAINGLES, 0)	


unsigned int ideaOfIndexBuffers();

void makeLegacyOpenGLTriangle()
{
	glBegin(GL_TRIANGLES);
	glVertex2f(-0.5f, -0.5f);
	glVertex2f(0.0f, 0.5f);
	glVertex2f(0.5f, -0.5f);
	glEnd();
}

unsigned int compileShader(unsigned int type, const std::string& source)
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
		char* message = (char*)alloca(log_length*sizeof(char));
		GL_CALL(glGetShaderInfoLog(id, log_length, &log_length, message));

		std::cout << "Error occured..." << std::endl;
		std::cout << message << std::endl;
	}

	return id;
}

static unsigned int makeProgram(const std::string& vertexShader, const std::string& fragmentShader)
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

//OpenGL acts as a state machine. Every commad issued to it works on the current state (of the data) amd then next
//comand on the next/generated state of the data.

//Tell the data (Buffer), specify the Shader and then say Draw.
void makeModernOpenGLDataBuffer() //As per the (OpenGL-) Graphics Pipeline
{
	//Make vertex Array object, to which everything else binds like, vertex buffer, its attributes and raw vertex data
	unsigned int vao;
	GL_CALL(glGenVertexArrays(1, &vao));
	GL_CALL(glBindVertexArray(vao));

	//Make Vertex Buffer

	//In OpenGL what ever we generate assigned an Id. Below buffer holds that id.
	unsigned int buffer; //holds the id of the buffer, id assigned to the chunk of created memory
	GL_CALL(glGenBuffers(1, &buffer));

	//select the buffer
	GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, buffer)); //we select the above buffer by giving its id and telling that it is an Array buffer

	float positions[6] = {
		-0.5f, -0.5f,
		0.0f, 0.5f,
		0.5f, -0.5f
	};

	GL_CALL(glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), (void*)positions, GL_STATIC_DRAW));

	//OpenGL Vertex Attributes tell what kind of data we have in the buffer or layout of the buffer memory.
	//These attributes are used by the shader to understabd the data.
	GL_CALL(glEnableVertexAttribArray(0));
	GL_CALL(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float)*2, 0));

	//shader a program run on GPU: A text code
	//There are main two types of shaders: 1. Vertex Shader 2. Pixel/Fragment Shader 3. ...
	//shader is used by draw call
	//PipeLine: .... Vertex Shader --> Pixel Shader .... Draw on screen
	//Vertex shader it tells the GPU where the vertex data is positioned
	//Next fragment takes on the data from Vertex Shader
	//Vertex shader is called here 3 times for each vertex

	//Fragment/Pixel shader is called once for each pixel to make the triangle. It will detemine the color for each pixel.
	//So if it is heavy it will affect performance.



}

enum SHADER_TYPE { SH_NONE = -1, SH_VERTEX, SH_PIXEL };

struct Shader {
	std::string vs;
	std::string fs;
};

Shader& parseShader(std::string&& filePath)
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

unsigned int getProgram()
{
	//std::string vertex_shader =
	//	"#version 330 core\n"
	//	"\n"
	//	"layout(location = 0) in vec4 position;"
	//	"\n"
	//	"void main()\n"
	//	"{\n"
	//	"	gl_position = position;\n"
	//	"}\n";

	//std::string fragment_shader =
	//	"#version 330 core\n"
	//	"\n"
	//	"layout(location = 0) out vec4 color;"
	//	"\n"
	//	"void main()\n"
	//	"{\n"
	//	"	color = vec4(1.0, 0.0, 0.0, 1.0);\n"
	//	"}\n";

	Shader& sh = parseShader("source.shader");
	return makeProgram(sh.vs, sh.fs);
	//return makeProgram(vertex_shader, fragment_shader);
}

unsigned int makeModernOpenGLGraphicsEntityProgram() //As per the (OpenGL-) Graphics Pipeline
{
	//makeModernOpenGLDataBuffer();
	ideaOfIndexBuffers();
	//Shader -> A Program that runs on very likely on GPU and consumes buffer data
	return getProgram();

}

int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;



	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	//Only after above context formation as per GLEW directive
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		/* Problem: glewInit failed, something is seriously wrong. */
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
		return -1;
	}
	fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));

	std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;

	unsigned int gEntityProg = makeModernOpenGLGraphicsEntityProgram();
	std::cout << "ProgramCode:" << gEntityProg << std::endl;
	GL_CALL(glUseProgram(gEntityProg));
	GL_CALL(unsigned int cLoc = glGetUniformLocation(gEntityProg, "inUColor"));
	if (cLoc >= 0) {
		GL_CALL(glUniform4f(cLoc, 1.0, 0.0, 1.0, 0.0));
	}
	float fc = 0.0;
	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		GL_CALL(glClear(GL_COLOR_BUFFER_BIT));
		
		//openGL Legacy Code to draw triangle
		//makeLegacyOpenGLTriangle();

		GL_CALL(glUniform4f(cLoc, 1.0-fc, 0.0, 1.0, 0.0));
		fc += 0.1f;
		if (fc > 1.0f) fc = 0.0f;
		//glDrawArrays(GL_TRIANGLES, 0, 6);
		//below goes with index buffers
		GL_CALL(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));
		

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}
	unsigned int errorCode = 0;
	
	while (errorCode = glGetError()) {
		std::cout << errorCode << std::endl;
	}
	GL_CALL(glDeleteProgram(gEntityProg));

	glfwTerminate();
	return 0;

}