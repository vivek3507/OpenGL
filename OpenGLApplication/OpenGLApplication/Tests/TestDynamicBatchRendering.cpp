#include "TestDynamicBatchRendering.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"


namespace test {
	TestDynamicBatchRendering::TestDynamicBatchRendering(const std::string &shaderCode)
		: m_shaders(shaderCode), m_translationA(0.0f, 0.0f, 0.0f), m_translationB(0.0f, 0.0f, 0.0f),
		m_proj(glm::ortho(-2.0f, 2.0f, -1.5f, 1.5f, -1.0f, 1.0f)), m_model(glm::rotate(glm::mat4(1.0f), 0.0f, glm::vec3(0.0f, 0.0f, 1.0f)))
	{
		Init();
	}

	TestDynamicBatchRendering::TestDynamicBatchRendering()
		: m_shaders("res/Shaders/BatchDynamicRendering.shader"), m_translationA(0.0f, 0.0f, 0.0f), m_translationB(0.0f, 0.0f, 0.0f),
		m_proj(glm::ortho(-2.0f, 2.0f, -1.5f, 1.5f, -1.0f, 1.0f)), m_model(glm::rotate(glm::mat4(1.0f), 0.0f, glm::vec3(0.0f, 0.0f, 1.0f)))
	{
		Init();
	}

	void TestDynamicBatchRendering::Init()
	{


		/*float positions[] =
		{
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
		0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
		0.5f, 0.5f, 1.0f, 1.0f, 0.0f,
		-0.5f, 0.5f, 0.0f, 1.0f, 0.0f,

		0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f, 1.0f,
		1.f, 1.0f, 1.0f, 1.0f, 1.0f,
		0.0f, 1.0f, 0.0f, 1.0f, 1.0f
		};*/

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

		m_vbo.setBufferData(8*sizeof(Vertex), nullptr, true);

		//BufferLayout buffLayout;
		m_buffLayout.addAttribute<float>(0, 2, false);
		m_buffLayout.addAttribute<float>(1, 2, true);
		m_buffLayout.addAttribute<float>(2, 1, true);

		m_vao.setBufferLayout(m_buffLayout);

		//ElementArray indexBuff;
		m_indexBuff.bind();

		m_indexBuff.setIndexBufferData(12, indices);

		//MVP:Model-View-Projection Matrices => Part of Transformation Pipeline which is applied on each vertex.
		//Each Matrix is 4x4 matrix and all of them are multiplied in M-V-P order in row major system, OpenGL being Column major
		//it multiplied them in reverse order to get final transformation matrix (P-V-M).

		//Projection Matrix: Project it to normalised coordinate system. Kind of Window view obtained from Camera full view.
		//View Matrix: Camera/Eye view coordinate system.
		//Model Matrix: Model Transformation matrix like translation, rotation etc in the environment.


		//Shaders shaders("source.shader");
		m_shaders.bind();

		m_attributeMVPMat = m_shaders.getUniform("u_MVP");
		//if (attributeMat) {
			//shaders.setUniformMat4f(attributeMat, mvp);
		//}

		//Texture texture("res/Textures/png3.png");
		m_textures.reserve(2);
		m_textures.emplace_back("res/Textures/png3.png");
		m_textures.emplace_back("res/Textures/png2.png");
		//m_textures.push_back(Texture("res/Textures/png3.png"));
		//m_textures.push_back(Texture("res/Textures/png3.png"));

		m_textures[0].bind(0);
		m_textures[1].bind(1);

		int samplers[] = { 0, 1 };

		//int loc = m_shaders.getUniform("u_Texture[0]");
		//std::cout << "texture uniform sampler location:" << loc << std::endl;
		//m_shaders.setUniform1i(loc, 0 /*slot number*/);
		//loc = m_shaders.getUniform("u_Texture[1]");
		//std::cout << "texture uniform sampler location:" << loc << std::endl;
		//m_shaders.setUniform1i(loc, 1 /*slot number*/);

		m_shaders.setUniform1iv(m_shaders.getUniform("u_Texture"), samplers, 2);

		//std::cout << "texture uniform sampler location:" << m_shaders.getUniform("u_TextureA") << std::endl;
		//std::cout << "texture uniform sampler location:" << m_shaders.getUniform("u_TextureB") << std::endl;

		//m_shaders.setUniform1i(m_shaders.getUniform("u_TextureA"), 0 /*slot number*/);
		//m_shaders.setUniform1i(m_shaders.getUniform("u_TextureB"), 1 /*slot number*/);





		//left-right-bottom-top ranges
		//othographic projection do not show the sign of persepective projections. Things do not have sense of distnace while looking at them.
		glm::mat4 proj = glm::ortho(-2.0f, 2.0f, -1.5f, 1.5f, -1.0f, 1.0f); //adjusting to the 4:3 aspect ratio of the window (first 4 values. last 2 values are for z coordinate)
		//glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(-0.5, 0.0f, 0.0f));
		glm::mat4 model = glm::rotate(glm::mat4(1.0f), 0.0f, glm::vec3(0.0f, 0.0f, 1.0f)); //rotate about z-axis

		//glm::mat4 mvp = proj * view * model; //reverse of MVP due to OpenGL being Column Major


	}

	TestDynamicBatchRendering::~TestDynamicBatchRendering()
	{
		m_vao.unbind();
		m_vbo.unbind();
		m_indexBuff.unbind();
		m_shaders.unbind();
	}

	void TestDynamicBatchRendering::makePositions(Vertex* vts)
	{
		static float topX = 0.0f;
		static bool left = true;
		if (left) {
			topX -= 0.005f;
			if (topX < -2.0f) left = false;
		}
		if (!left) {
			topX += 0.005f;
			if (topX > 2.0f) left = true;
		}

		/*
		struct Vertex
		{
			float Positions[2];
			float TexCoord[2];
			float TexID;
		};
		*/

		vts[0] = { -0.5f - topX, -0.5f, 0.0f, 0.0f, 0.0f };
		vts[1] = {0.5f - topX, -0.5f, 1.0f, 0.0f, 0.0f};
		vts[2] = {0.5f - topX, 0.5f, 1.0f, 1.0f, 0.0f};
		vts[3] = {-0.5f - topX, 0.5f, 0.0f, 1.0f, 0.0f};

		vts[4] = { 0.0f, 0.0f, 0.0f, 0.0f, 1.0f };
		vts[5] = {1.0f, 0.0f, 1.0f, 0.0f, 1.0f};
		vts[6] = {1.f, 1.0f, 1.0f, 1.0f, 1.0f};
		vts[7] = {0.0f, 1.0f, 0.0f, 1.0f, 1.0f};

	}

	void TestDynamicBatchRendering::onUpdate(float detlaTime)
	{
		/*static float topX = 0.0f;
		static bool left = true;
		if (left) {
			topX -= 0.005f;
			if (topX < -2.0f) left = false;
		}
		if (!left) {
			topX += 0.005f;
			if (topX > 2.0f) left = true;
		}
		
		float positions[] =
		{
		-0.5f-topX, -0.5f, 0.0f, 0.0f, 0.0f,
		0.5f-topX, -0.5f, 1.0f, 0.0f, 0.0f,
		0.5f-topX, 0.5f, 1.0f, 1.0f, 0.0f,
		-0.5f-topX, 0.5f, 0.0f, 1.0f, 0.0f,

		0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f, 1.0f,
		1.f, 1.0f, 1.0f, 1.0f, 1.0f,
		0.0f, 1.0f, 0.0f, 1.0f, 1.0f
		};*/

		Vertex vts[8];
		makePositions(vts);
		//VertexBuffer vbo;

		m_vbo.bind();
		m_vbo.setBufferDataDynamic(8*sizeof(Vertex), (float*)vts);

	}

	void TestDynamicBatchRendering::onRender()
	{
		m_renderer.clear();

		glm::mat4 view = glm::translate(glm::mat4(1.0f), m_translationA);


		//left-right-bottom-top ranges
		//othographic projection do not show the sign of persepective projections. Things do not have sense of distnace while looking at them.
		//glm::mat4 proj = glm::ortho(-2.0f, 2.0f, -1.5f, 1.5f, -1.0f, 1.0f); //adjusting to the 4:3 aspect ratio of the window (first 4 values. last 2 values are for z coordinate)
		//glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(-0.5, 0.0f, 0.0f));
		//glm::mat4 model = glm::rotate(glm::mat4(1.0f), 30.0f, glm::vec3(0.0f, 0.0f, 1.0f)); //rotate about z-axis

		//glm::mat4 mvp = proj * view * model; //reverse of MVP due to OpenGL being Column Major

		glm::mat4 mvp = m_proj * view * m_model; //reverse of MVP due to OpenGL being Column Major

		m_shaders.bind(); //before below call
		m_shaders.setUniformMat4f(m_attributeMVPMat, mvp);

		//below goes with index buffers
		m_renderer.Draw(m_vao, m_indexBuff, m_shaders);

		//view = glm::translate(glm::mat4(1.0f), m_translationB);

		//mvp = m_proj * view * m_model; //reverse of MVP due to OpenGL being Column Major
		//m_shaders.setUniformMat4f(m_attributeMVPMat, mvp);

		////below goes with index buffers
		//m_renderer.Draw(m_vao, m_indexBuff, m_shaders);


	}

	void TestDynamicBatchRendering::onImGuiRender()
	{
		//ImGui::Begin("Texture and Multiple Objects!");                          // Create a window called "Hello, world!" and append into it.

		ImGui::Text("Sliders to control translation in X and Y direction.");               // Display some text (you can use a format strings too)

		ImGui::SliderFloat3("Object 1:", &m_translationA.x, -1.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
		//ImGui::SliderFloat3("Object 2:", &m_translationB.x, -1.0f, 1.0f);

		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		//ImGui::End();

	}

}
