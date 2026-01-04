#pragma once

#include "Scene.h"
#include "../Graphics/Window.h"

namespace TMT 
{
	class TMT_Module {
	public:
		TMT_Module(const Window& window, Scene& scene, Object& object);
		~TMT_Module();

		virtual void update();

	protected:
		Object& m_object;
		Scene& m_scene;
		Window m_window;
		GLFWwindow* m_glfwWindow;
	};
}