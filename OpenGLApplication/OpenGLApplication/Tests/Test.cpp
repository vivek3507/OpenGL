#include "Test.h"

namespace test {

	TestMenu::TestMenu(Test*& currentTest)
		: m_currentTest(currentTest)
	{

	}

	TestMenu::~TestMenu()
	{

	}

	void TestMenu::onUpdate(float detlaTime)
	{
	}

	void TestMenu::onRender()
	{
		m_renderer.clear();
	}

	void TestMenu::onImGuiRender()
	{
		for (auto& ele : m_tests) {
			if (ImGui::Button(ele.first.c_str())) {
				m_currentTest = (ele.second)();
			}
		}
	}

}
