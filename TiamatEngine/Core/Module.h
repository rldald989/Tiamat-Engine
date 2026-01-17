#pragma once

#include "Object.h"
#include "../Graphics/Window.h"

namespace TMT 
{
	class TMT_Module {
	public:
		TMT_Module(const Window& window, Object& object, std::string module_name);
		~TMT_Module();

		virtual void update();

	protected:
		Object& m_object;
		Window m_window;
		GLFWwindow* m_glfwWindow;
		std::string m_module_name;
	};
}