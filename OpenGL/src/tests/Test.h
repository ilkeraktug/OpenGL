#pragma once

#include <glad\glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <functional>
#include <vector>
#include <string>

#include "imgui.h"

namespace test {
	class Test {
	public:
		Test() {}
		virtual ~Test() {}

		virtual void OnUpdate(float deltaTime) {}
		virtual void OnRender() {}
		virtual void OnImGuiRender() {}
	};

	class TestMenu : public Test {
	public:
		TestMenu(Test*& currentTest);
		~TestMenu();

		void OnRender() override;
		void OnImGuiRender() override;

		template<typename T>
		void RegisterMenu(const std::string& name)
		{
			std::cout << "Registering test " << name << std::endl;

			m_Tests.push_back(std::make_pair(name, []() { return new T(); }));
		}

		template<typename T>
		T* GetWindow() { return new T(); }
		
		template<typename T>
		T* GetWindowAssimp(const std::string& filePath) { return new T(filePath); }
	private:
		Test*& m_CurrentTest;
		std::vector<std::pair<std::string, std::function<Test* ()>>> m_Tests;
	};
}