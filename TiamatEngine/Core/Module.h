#pragma once

#include "Scene.h"
#include "../Graphics/Window.h"

namespace TMT 
{
	class TMT_Module {
	public:
		TMT_Module(const Window& window, Scene& scene);
		~TMT_Module();

		virtual void update();

	private:
		Scene& m_scene;
		Window m_window;
		GLFWwindow* m_glfwWindow;
	};
}