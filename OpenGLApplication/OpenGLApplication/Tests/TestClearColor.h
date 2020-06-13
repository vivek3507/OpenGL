#pragma once
#include "Test.h"

namespace test {
	class TestClearColor : public Test
	{
	public:
		TestClearColor();
		~TestClearColor();

		void onUpdate(float detlaTime) override;
		void onRender() override;
		void onImGuiRender() override;

	private:
		float m_clearColor[4];
		Renderer m_renderer;
	};


}

