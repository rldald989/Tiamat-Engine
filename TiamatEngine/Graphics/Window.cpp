#include "Window.h"

TMT::Window::Window(const char* name) : m_width(640), m_height(420), m_name(name), m_color(0, 0, 0), m_window(glfwCreateWindow(m_width, m_height, m_name, NULL, NULL))
{
	if (!m_window) {
		"Window creation failed";
	}

	glfwMakeContextCurrent(m_window);
}

TMT::Window::Window(int width, int height, const char* name, Vector3 color) : m_width(height), m_height(width), m_name(name), m_color(color), m_window(glfwCreateWindow(m_width, m_height, m_name, NULL, NULL))
{
	if (!m_window) {
		"Window creation failed";
	}

	glfwMakeContextCurrent(m_window);
}

TMT::Window::~Window()
{
	glfwDestroyWindow(m_window);
	glfwTerminate();
}

Vector2 TMT::Window::get_size()
{
	return Vector2(m_width, m_height);
}

int& TMT::Window::get_width()
{
	return m_width;
}

int& TMT::Window::get_height()
{
	return m_height;
}

float TMT::Window::get_aspect_ratio()
{
	return static_cast<float>(m_width) / static_cast<float>(m_height);
}

void TMT::Window::set_color(Vector3 color)
{
	m_color = color;
}

void TMT::Window::enable_alpha()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void TMT::Window::clear()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(m_color.x, m_color.y, m_color.z, 1.0f);
}

void TMT::Window::swap_buffers()
{
	glfwSwapBuffers(m_window);
}

void TMT::Window::poll_events()
{
	glfwPollEvents();
}
