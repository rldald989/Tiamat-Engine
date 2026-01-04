#include "Object.h"

TMT::Object::Object() : matrix_name("model_transform"), transform(glm::vec2(0), glm::vec2(1), 0), m_model_transform(1.0f), m_local_transform(1.0f), m_final_transform(1.0f)
{
}

TMT::Object::Object(std::string name, const std::string& _matrix_name, const tmt_transform& _transform) : m_name(name), matrix_name(_matrix_name), transform(_transform), m_model_transform(1.0f), m_local_transform(1.0f), m_final_transform(1.0f)
{
	m_model_transform[3][0] = transform.position.x;
	m_model_transform[3][1] = transform.position.y;
	m_model_transform[0][0] = transform.scale.x;
	m_model_transform[1][1] = transform.scale.y;

	m_model_transform = m_model_transform * glm::mat4_cast(glm::angleAxis(glm::radians(transform.rotation), glm::vec3(0, 0, 1)));
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
	m_model_transform = glm::scale(m_model_transform, glm::vec3(x, y, 1));
}

void TMT::Object::rotate(float degrees)
{
	m_model_transform = glm::rotate(m_model_transform, glm::radians(degrees), glm::vec3(0, 0, 1));
}

void TMT::Object::local_move(float x, float y)
{
	m_local_transform = glm::translate(m_local_transform, glm::vec3(x * 1.25f, y * 1.25f, 0));
}

void TMT::Object::local_scale(float x, float y)
{
	m_local_transform = glm::scale(m_local_transform, glm::vec3(x * 1.25f, y * 1.25f, 1));
}

void TMT::Object::local_rotate(float degrees)
{
	m_local_transform = glm::rotate(m_local_transform, glm::radians(degrees) / 2, glm::vec3(0, 0, 1));
}

void TMT::Object::set_position(float x, float y)
{
	m_model_transform[3][0] = x;
	m_model_transform[3][1] = y;
}

void TMT::Object::set_scale(float x, float y)
{
	m_model_transform[0][0] = x;
	m_model_transform[1][1] = y;
}

void TMT::Object::add_tag(std::string tag)
{
	m_tags[tag] = tag;
}

bool TMT::Object::has_tag(std::string tag)
{
	return m_tags.find(tag.c_str()) != m_tags.end();
}

void TMT::Object::parent(Object* to_child)
{
	to_child->m_parent = this->m_name;
}


glm::mat4& TMT::Object::get_transform()
{
	return m_model_transform;
}


glm::mat4 TMT::Object::update()
{
	transform.position = glm::vec2(m_model_transform[3][0], m_model_transform[3][1]);
	transform.scale = glm::vec2(m_model_transform[0][0], m_model_transform[1][1]);

	m_final_transform = m_model_transform * m_local_transform;

	//std::cout << m_name << " is being updated" << std::endl;

	return m_final_transform;
}