#include "Test.h"
#include "Renderer.h"

namespace test {
	
	TestMenu::TestMenu(Test*& currentTest)
		:m_CurrentTest(currentTest) {}

	TestMenu::~TestMenu()
	{
	}

	void TestMenu::OnRender()
	{
		Renderer renderer;
		renderer.Clear();
	}
	void TestMenu::OnImGuiRender()
	{
		for (auto& test : m_Tests)
		{
			if (ImGui::Button(test.first.c_str()))
				m_CurrentTest = test.second();
		}
	}
}
