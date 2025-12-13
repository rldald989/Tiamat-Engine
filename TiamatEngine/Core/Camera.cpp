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
	float aspect_ratio = m_window.get_aspect_ratio();
	m_projection = glm::ortho(-aspect_ratio, aspect_ratio, -1.f, 1.f, -1.f, 1.f);
	 
	transform.position = glm::vec2(m_model_transform[3][0], m_model_transform[3][1]);
	transform.scale = glm::vec2(m_model_transform[0][0], m_model_transform[1][1]);

	return m_projection * m_model_transform;
}


