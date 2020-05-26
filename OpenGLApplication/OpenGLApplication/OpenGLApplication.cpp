#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stdio.h>
#include <assert.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Renderer.h"

#include "VertexArray.h"
#include "VertexBuffer.h"
#include "ElementArray.h"
#include "BufferLayout.h"
#include "Shaders.h"
#include "Texture.h"
#include "Renderer.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"


//Modern OpenGL
//Graphics rendering Pipeline (roughly)
//									Setup Vertex Array
//									|
//									v
//									Setup Data Buffer
//									|
//								    v
//									Setup Data Layout (Setup Array Attributes)
//									|
//									v
//									Setup Index Buffer
//									|
//									v
//									glUseProgram <-- Link Program <-- Attach Compiled Shaders To a Program |<--- Compile Shader  <-- Create Shader Container <-- Supply Vertex Shader Code as Text
//									|																	   |	
//									|																	   |<--- Compile Shader  <-- Create Shader Container <-- Supply Fragment Shader Code as Text
//									v
//									glDrawArrays(GL_TRAINGLES, 0)	

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
	/*
	float positions[] = {
		-0.5f, -0.5f,
		 0.5f, -0.5f,
		 0.5f, 0.5f,
		-0.5f, 0.5f,
	};
	*/

	float positions[] = {
	-0.5f, -0.5f, 0.0f, 0.0f,
	 0.5f, -0.5f, 1.0f, 0.0f,
	 0.5f, 0.5f, 1.0f, 1.0f,
	-0.5f, 0.5f, 0.0f, 1.0f,
	};

	unsigned int indices[] = {
	0, 1, 2, //first triangle
	2, 3, 0 //second triagnle
	};

	{
		//To handle alpha channels
		GL_CALL(glEnable(GL_BLEND));
		GL_CALL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
		VertexArray vao;
		vao.bind();

		VertexBuffer vbo;
		vbo.bind();

		vbo.setBufferData(16, positions);

		BufferLayout buffLayout;
		buffLayout.addAttribute<float>(0, 2, false);
		buffLayout.addAttribute<float>(1, 2, true);

		vao.setBufferLayout(buffLayout);

		ElementArray indexBuff;
		indexBuff.bind();

		indexBuff.setIndexBufferData(6, indices);

		//MVP:Model-View-Projection Matrices => Part of Transformation Pipeline which is applied on each vertex.
		//Each Matrix is 4x4 matrix and all of them are multiplied in M-V-P order in row major system, OpenGL being Column major
		//it multiplied them in reverse order to get final transformation matrix (P-V-M).

		//Projection Matrix: Project it to normalised coordinate system. Kind of Window view obtained from Camera full view.
		//View Matrix: Camera/Eye view coordinate system.
		//Model Matrix: Model Transformation matrix like translation, rotation etc in the environment.

		//left-right-bottom-top ranges
		//othographic projection do not show the sign of persepective projections. Things do not have sense of distnace while looking at them.
		glm::mat4 proj = glm::ortho(-2.0f, 2.0f, -1.5f, 1.5f, -1.0f, 1.0f); //adjusting to the 4:3 aspect ratio of the window (first 4 values. last 2 values are for z coordinate)
		glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(-0.5, 0.0f, 0.0f));
		glm::mat4 model = glm::rotate(glm::mat4(1.0f), 30.0f, glm::vec3(0.0f, 0.0f, 1.0f)); //rotate about z-axis

		glm::mat4 mvp = proj * view * model; //reverse of MVP due to OpenGL being Column Major

		Shaders shaders("source.shader");
		shaders.bind();

		int attributeL = shaders.getUniform("inUColor");
		//if (attributeL) {
			shaders.setUniform4f(attributeL, 1.0, 0.0, 1.0, 0.0);
		//}

		int attributeMat = shaders.getUniform("u_MVP");
		//if (attributeMat) {
			shaders.setUniformMat4f(attributeMat, mvp);
		//}

		Texture texture("res/Textures/png3.png");
		texture.bind();
		shaders.setUniform1i(shaders.getUniform("u_Texture"), 0 /*slot number*/);


		vao.unbind();
		vbo.unbind();
		indexBuff.unbind();
		shaders.unbind();

		Renderer renderer;

		float fc = 0.0;
		/* Loop until the user closes the window */
		while (!glfwWindowShouldClose(window))
		{
			/* Render here */
			renderer.clear();

			shaders.bind(); //before below call
			shaders.setUniform4f(attributeL, 1.0 - fc, 0.0, 1.0, 0.0);

			fc += 0.1f;
			if (fc > 1.0f) fc = 0.0f;

			//below goes with index buffers
			renderer.Draw(vao, indexBuff, shaders);

			/* Swap front and back buffers */
			glfwSwapBuffers(window);

			/* Poll for and process events */
			glfwPollEvents();
		}
	}

	glfwTerminate();
	return 0;

}