#include "TestBatchRenderingBasic.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"


namespace test {
	TestBatchRenderingBasic::TestBatchRenderingBasic(const std::string &shaderCode)
		: m_shaders(shaderCode), m_translationA(0.0f, 0.0f, 0.0f)
	{
		Init();
	}

	TestBatchRenderingBasic::TestBatchRenderingBasic()
		: m_shaders("res/Shaders/BatchRenderingBasicTest.shader"), m_translationA(0.0f, 0.0f, 0.0f)
	{
		Init();
	}

	void TestBatchRenderingBasic::Init()
	{
		float positions[] =
		{
		-0.5f, -0.5f,
		0.5f, -0.5f,
		0.5f, 0.5f,
		-0.5f, 0.5f,

		0.0f, 0.0f,
		1.0f, 0.0f,
		1.f, 1.0f,
		0.0f, 1.0f
		};

		unsigned int indices[] = {
		0, 1, 2, //first triangle
		2, 3, 0, //second triagnle

		4, 5, 6, //first triangle
		6, 7, 4 //second triagnle
		};

		//VertexArray vao;
		m_vao.bind();

		//VertexBuffer vbo;
		m_vbo.bind();

		m_vbo.setBufferData(16, positions);

		//BufferLayout buffLayout;
		m_buffLayout.addAttribute<float>(0, 2, false);

		m_vao.setBufferLayout(m_buffLayout);

		//ElementArray indexBuff;
		m_indexBuff.bind();

		m_indexBuff.setIndexBufferData(12, indices);
		m_shaders.bind();

		m_attributeMVPMat = m_shaders.getUniform("u_MVP");
	}

	TestBatchRenderingBasic::~TestBatchRenderingBasic()
	{
		m_vao.unbind();
		m_vbo.unbind();
		m_indexBuff.unbind();
		m_shaders.unbind();
	}

	void TestBatchRenderingBasic::onUpdate(float detlaTime)
	{

	}

	void TestBatchRenderingBasic::onRender()
	{
		m_renderer.clear();

		m_shaders.bind(); //before below call

		glm::mat4 view = glm::translate(glm::mat4(1.0f), m_translationA);

		glm::mat4 mvp = view; //reverse of MVP due to OpenGL being Column Major

		m_shaders.setUniformMat4f(m_attributeMVPMat, mvp);

		//below goes with index buffers
		m_renderer.Draw(m_vao, m_indexBuff, m_shaders);

	}

	void TestBatchRenderingBasic::onImGuiRender()
	{
		//ImGui::Begin("Texture and Multiple Objects!");                          // Create a window called "Hello, world!" and append into it.

		ImGui::Text("Sliders to control translation in X and Y direction.");               // Display some text (you can use a format strings too)

		ImGui::SliderFloat3("Object 1:", &m_translationA.x, -1.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f

		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		//ImGui::End();

	}

}
