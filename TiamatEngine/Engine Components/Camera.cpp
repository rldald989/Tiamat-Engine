#include "Camera.h"

TMT::Camera::Camera(const Window& window, const tmt_transform& cam_transform) : m_window(window), Object("camera_transform", cam_transform)
{
	polarity = -1;
}

TMT::Camera::~Camera()
{
}

void TMT::Camera::update() {
	transform.position = glm::vec2(m_model_transform[3][0] * polarity, m_model_transform[3][1] * polarity);
	transform.scale = glm::vec2(m_model_transform[0][0], m_model_transform[1][1]);
	m_model_transform = glm::ortho(0.f, m_window.get_size().m_x, 0.f, m_window.get_size().m_y, 0.f, 100.f);
}

void TMT::Camera::zoom(float amount)
{
	scale(amount, amount);
}
