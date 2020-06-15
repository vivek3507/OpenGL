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

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include "Tests/TestClearColor.h"
#include "Tests/TestTexture.h"

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
	window = glfwCreateWindow(640, 480, "OpenGL Application", NULL, NULL);
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

	{
		//To handle alpha channels
		GL_CALL(glEnable(GL_BLEND));
		GL_CALL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

		//test::TestTexture textureTest("source.shader", "res/Textures/png3.png");
		test::Test* currentTest = NULL;
		test::TestMenu* testMenu = new test::TestMenu(currentTest);
		if (currentTest == NULL) currentTest = testMenu;

		testMenu->registerTest<test::TestClearColor>("Clear Color");
		testMenu->registerTest<test::TestTexture>("MultiObject Texture");

		//testMenu.registerTest<test::TestTexture>("Test Texture");

		// Setup Dear ImGui context
		const char* glsl_version = "#version 130";
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

		// Setup Dear ImGui style
		ImGui::StyleColorsDark();
		//ImGui::StyleColorsClassic();

		// Setup Platform/Renderer bindings
		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init(glsl_version);

		float fc = 0.0;
		/* Loop until the user closes the window */
		while (!glfwWindowShouldClose(window))
		{
			GL_CALL(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
			//textureTest.onUpdate(0.0f);

			/* Render here */
			//textureTest.onRender();
			currentTest->onUpdate(0.0f);
			currentTest->onRender();

			// Start the Dear ImGui frame
			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();

			//textureTest.onImGuiRender();
			if (currentTest != testMenu) {
				ImGui::Begin("Test case");
				if (ImGui::Button("<-")) {
					delete currentTest;
					currentTest = testMenu;
				}
			}
			else {
				ImGui::Begin("Pick a test case");
			}
			currentTest->onImGuiRender();
			ImGui::End();

			//ImGui Rendering
			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

			/* Swap front and back buffers */
			glfwSwapBuffers(window);

			/* Poll for and process events */
			glfwPollEvents();
		}
	}

	// Cleanup
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwTerminate();
	return 0;

}