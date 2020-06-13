#include "TestClearColor.h"
#include "imgui/imgui.h"

test::TestClearColor::TestClearColor()
	: m_clearColor{0.2f, 0.3f, 0.8f, 1.0f}
{
}

test::TestClearColor::~TestClearColor()
{
}

void test::TestClearColor::onUpdate(float detlaTime)
{
}

void test::TestClearColor::onRender()
{
	m_renderer.clear();
	GL_CALL(glClearColor(m_clearColor[0], m_clearColor[1], m_clearColor[2], m_clearColor[3]));
	GL_CALL(glClear(GL_COLOR_BUFFER_BIT));
}

void test::TestClearColor::onImGuiRender()
{
	ImGui::ColorEdit4("Clear Color", m_clearColor);
}
