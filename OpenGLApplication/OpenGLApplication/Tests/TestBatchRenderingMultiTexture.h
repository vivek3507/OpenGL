#pragma once
#pragma once
#pragma once
#include "Test.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "ElementArray.h"
#include "Shaders.h"
#include "Texture.h"

namespace test {

	class TestBatchRenderingMultiTexture : public Test
	{
		VertexArray m_vao;
		VertexBuffer m_vbo;
		BufferLayout m_buffLayout;
		ElementArray m_indexBuff;
		Shaders m_shaders;
		std::vector<Texture> m_textures;
		Renderer m_renderer;

		glm::vec3 m_translationA;
		glm::vec3 m_translationB;

		glm::mat4 m_proj;
		glm::mat4 m_model;

		int m_attributeMVPMat;

		void Init();
	public:
		TestBatchRenderingMultiTexture();
		TestBatchRenderingMultiTexture(const std::string &shaderCode);
		~TestBatchRenderingMultiTexture();

		void onUpdate(float detlaTime) override;
		void onRender() override;
		void onImGuiRender() override;

	};
}
