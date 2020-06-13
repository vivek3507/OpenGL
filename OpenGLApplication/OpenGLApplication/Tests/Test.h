#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>


#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include "../Renderer.h"

#include <unordered_map>
#include <functional>

namespace test {

	class Test
	{
	public:
		Test() {}
		virtual ~Test() {}
		
		virtual void onUpdate(float detlaTime) {}
		virtual void onRender() {}
		virtual void onImGuiRender() {}
	};

	class TestMenu : public Test
	{
		std::unordered_map<std::string, std::function<Test*()>> m_tests;
		Test*& m_currentTest;
		Renderer m_renderer;
	public:
		TestMenu(Test*& currentTest);
		~TestMenu();

		template <typename T>
		void registerTest(const std::string& name)
		{
			m_tests.insert(std::make_pair(name, []() {
				return new T();
			}));
		}

		void onUpdate(float detlaTime) override;
		void onRender() override;
		void onImGuiRender() override;
	};

}
