#pragma once
#include "Test.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "ElementArray.h"
#include "Shaders.h"
#include "Texture.h"

namespace test {

	class TestDynamicBatchRendering : public Test
	{
		struct Vertex
		{
			float Positions[2];
			float TexCoord[2];
			float TexID;
		};

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
		void makePositions(Vertex* vts);

	public:
		TestDynamicBatchRendering();
		TestDynamicBatchRendering(const std::string &shaderCode);
		~TestDynamicBatchRendering();

		void onUpdate(float detlaTime) override;
		void onRender() override;
		void onImGuiRender() override;

	};
}
