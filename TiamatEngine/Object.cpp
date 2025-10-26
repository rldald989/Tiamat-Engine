#include "Object.h"

TMT::Object::Object() : matrix_name("model_transform"), transform(glm::vec2(0), glm::vec2(1), 0), m_model_transform(1.0f)
{
}

TMT::Object::Object(std::string _matrix_name, const tmt_transform& _transform) : matrix_name(_matrix_name), transform(_transform), m_model_transform(1.0f)
{
	m_model_transform[3][0] = transform.position.x;
	m_model_transform[3][1] = transform.position.y;

	m_model_transform = m_model_transform * glm::mat4_cast(glm::angleAxis(glm::radians(transform.rotation), glm::vec3(0, 0, 1)));

	m_model_transform[0][0] = transform.scale.x;
	m_model_transform[1][1] = transform.scale.y;
}

TMT::Object::~Object()
{

}

void TMT::Object::move(float x, float y)
{
	m_model_transform = glm::translate(m_model_transform, glm::vec3(x, y, 0));
}

void TMT::Object::scale(float x, float y)
{
	m_model_transform = glm::scale(m_model_transform, glm::vec3(x, y, 0));
}

void TMT::Object::rotate(float degrees)
{
	m_model_transform = glm::rotate(m_model_transform, glm::radians(degrees), glm::vec3(0, 0, 1));
}

glm::mat4 TMT::Object::get_transform()
{
	return m_model_transform;
}

void TMT::Object::update()
{
	transform.position = glm::vec2(m_model_transform[3][0], m_model_transform[3][1]);
	transform.scale = glm::vec2(m_model_transform[0][0], m_model_transform[1][1]);
}