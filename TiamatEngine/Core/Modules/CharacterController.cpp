#include "CharacterController.h"

TMT::Game::CharacterController::CharacterController(Collider& collider, float speed):
	TMT_Module(collider.m_window, collider.m_object, "character_controller"),
	m_speed(speed), m_character_dir(character_direction::RIGHT)
{
}

TMT::Game::CharacterController::~CharacterController()
{
}

void TMT::Game::CharacterController::update()
{ 
	float character_movement = 0;
	if (glfwGetKey(m_glfwWindow, GLFW_KEY_A) == GLFW_PRESS) 
	{
		character_movement = -1.f;
		m_character_dir = character_direction::LEFT;
	}
	else if (glfwGetKey(m_glfwWindow, GLFW_KEY_D) == GLFW_PRESS)
	{
		character_movement = 1.f;
		m_character_dir = character_direction::RIGHT;
	}

	m_object.move(character_movement * m_speed * delta_time, 0.0f);
}

TMT::Game::Collider::Collider(const Window& window, Scene& scene, Object& object, std::string collider_tag) :
	TMT_Module(window, object, "collider"),
	m_collided(false), m_bounds(glm::vec2(0, 0)), m_collider_tag(collider_tag),
	m_scene(scene), m_last_x(0), m_current_x(0), velocity(0)
{
	for (auto& o : m_scene.get_objects()) {
		if (o.second->has_tag(collider_tag) && &*o.second != &m_object) 
		{
			std::cout << "Found object with the collider tag" << std::endl;
			m_others.push_back(o.second);
		}
	}
}

TMT::Game::Collider::~Collider()
{
}

void TMT::Game::Collider::conform_to_scale()
{
	m_bounds = m_object.transform.scale * .5f;
}

void TMT::Game::Collider::update()
{
	m_current_x = m_object.transform.position.x;

	velocity = m_last_x - m_current_x;

	for (auto& o : m_others) {
		if (m_object.transform.position.x - m_bounds.x <= o->transform.position.x) {
			m_collided = true;
		}
		else {
			m_collided = false;
		}
	}

	m_last_x = m_object.transform.position.x;
}
