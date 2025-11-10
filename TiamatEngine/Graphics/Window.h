#pragma once

#include "glew.h"
#include "glfw3.h"
#include "../Vector/Vector2.h"
#include "../Vector/Vector3.h"

namespace TMT {


	struct IVector2 {
		int x;
		int y;
	};

	class Window
	{
	public:
		Window(const char* name);
		Window(int width, int height, const char* name, Vector3 color);
		~Window();

		GLFWwindow* get_window() { return m_window;  }

		Vector2 get_size();

		int& get_width();
		int& get_height();

		float get_aspect_ratio();

		void set_color(Vector3 color);

		void enable_alpha();

		void clear();

		void swap_buffers();

		void poll_events();

	private:
		int m_width, m_height;
		const char* m_name;
		GLFWwindow* m_window;
		Vector3 m_color;

	};
};