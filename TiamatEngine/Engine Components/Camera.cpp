#include "Camera.h"

TMT::Camera::Camera(std::string name, Window& window, const tmt_transform& cam_transform) : m_window(window), Object(name, "camera_transform", cam_transform), m_projection(1.0f)
{
	std::cout << "Window x: " << m_window.get_size().m_x << std::endl;
	std::cout << "Window y: " << m_window.get_size().m_y << std::endl;
}

TMT::Camera::~Camera()
{
}

glm::mat4 TMT::Camera::update()
{
	Vector2 size = m_window.get_size();
	m_projection = glm::ortho(0.f, size.m_x, 0.f, size.m_y, -1.f, 1.f);

	transform.position = glm::vec2(m_model_transform[3][0], m_model_transform[3][1]);
	transform.scale = glm::vec2(m_model_transform[0][0], m_model_transform[1][1]);

	return m_model_transform * m_projection;
}
