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

TMT::Game::Collider::Collider(const Window& window, Object& object, std::string collider_tag) :
	TMT_Module(window, object, "collider"),
	m_collided(false), m_bounds(glm::vec2(0, 0)), m_collider_tag(collider_tag)
{
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
	for (auto& o : m_others) {
		if (m_object.transform.position.x - m_bounds.x <= o->m_object.transform.position.x + o->m_bounds.x) {
			std::cout << "collision" << std::endl;
		}
	}
}
