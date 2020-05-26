#include <iostream>
#include "Renderer.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

static void makeModernOpenGLDataBufferRect() //As per the (OpenGL-) Graphics Pipeline
{
	//Make vertex Array object, to which everything else binds like, vertex buffer, its attributes and raw vertex data
	unsigned int vao;
	GL_CALL(glGenVertexArrays(1, &vao));
	GL_CALL(glBindVertexArray(vao));
	//Make Vertex Buffer

	//In OpenGL what ever we generate assigned an Id. Below buffer holds that id.
	unsigned int buffer; //holds the id of the buffer, id assigned to the chunk of created memory
	glGenBuffers(1, &buffer);

	//select the buffer
	glBindBuffer(GL_ARRAY_BUFFER, buffer); //we select the above buffer by giving its id and telling that it is an Array buffer

	float positions[] = {
		-0.5f, -0.5f,
		0.5f, -0.5f,
		0.5f, 0.5f,

		0.5f, 0.5f,
		-0.5f, 0.5f,
		-0.5f, -0.5f,
	
	};

	glBufferData(GL_ARRAY_BUFFER, 6 * 2 * sizeof(float), (void*)positions, GL_STATIC_DRAW);

	//OpenGL Vertex Attributes tell what kind of data we have in the buffer or layout of the buffer memory.
	//These attributes are used by the shader to understabd the data.
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

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

static void makeModernOpenGLDataIndexBufferRect() //As per the (OpenGL-) Graphics Pipeline
{
	//Make Vertex Buffer

	//In OpenGL what ever we generate assigned an Id. Below buffer holds that id.
	unsigned int buffer; //holds the id of the buffer, id assigned to the chunk of created memory
	glGenBuffers(1, &buffer);

	//select the buffer
	glBindBuffer(GL_ARRAY_BUFFER, buffer); //we select the above buffer by giving its id and telling that it is an Array buffer

	float positions[] = {
		-0.5f, -0.5f,
		 0.5f, -0.5f,
		 0.5f, 0.5f,
		-0.5f, 0.5f,
	};

	glBufferData(GL_ARRAY_BUFFER, 4 * 2 * sizeof(float), (void*)positions, GL_STATIC_DRAW);

	//OpenGL Vertex Attributes tell what kind of data we have in the buffer or layout of the buffer memory.
	//These attributes are used by the shader to understabd the data.
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

	unsigned int indices[] = {
		0, 1, 2, //first triangle
		2, 3, 0 //second triagnle
	};

	//Prepare the buffer for index buffer
	unsigned int ibo; //index buffer object
	glGenBuffers(1, &ibo);

	//select the buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), (void*)indices, GL_STATIC_DRAW);

	//Below is not used
	//glEnableVertexAttribArray(1);
	//glVertexAttribPointer(0, 1, GL_UNSIGNED_INT, GL_FALSE, sizeof(unsigned int) * 1, 0);


}


unsigned int ideaOfIndexBuffers()
{
	//Anything we want to draw is broken into a set of Triangles and then sent to GPU.
	//Triangle is chosen a basic unit of drawing as Normal drawn to a triangle surface 
	//always point in one direction. With other virtex count there are more than one 
	//possible suface normals.

	//makeModernOpenGLDataBufferRect();
	makeModernOpenGLDataIndexBufferRect();

	return 0;

}