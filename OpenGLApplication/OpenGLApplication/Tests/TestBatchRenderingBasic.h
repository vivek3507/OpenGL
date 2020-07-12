#pragma once
#include "Test.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "ElementArray.h"
#include "Shaders.h"
#include "Texture.h"

namespace test {

	class TestBatchRenderingBasic : public Test
	{
		VertexArray m_vao;
		VertexBuffer m_vbo;
		BufferLayout m_buffLayout;
		ElementArray m_indexBuff;
		Shaders m_shaders;
		Renderer m_renderer;

		glm::vec3 m_translationA;

		int m_attributeMVPMat;

		void Init();
	public:
		TestBatchRenderingBasic();
		TestBatchRenderingBasic(const std::string &shaderCode);
		~TestBatchRenderingBasic();

		void onUpdate(float detlaTime) override;
		void onRender() override;
		void onImGuiRender() override;

	};
}
