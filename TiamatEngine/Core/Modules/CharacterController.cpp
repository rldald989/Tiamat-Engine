#include "CharacterController.h"

TMT::Game::CharacterController::CharacterController(const Window& window, Scene& scene, std::string character_object_name, float speed):
	TMT_Module(window, scene, *scene.get_object(character_object_name)),
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
		m_character_dir == character_direction::LEFT;
	}
	else if (glfwGetKey(m_glfwWindow, GLFW_KEY_D) == GLFW_PRESS)
	{
		character_movement = 1.f;
		m_character_dir == character_direction::RIGHT;
	}

	m_object.move(character_movement * m_speed * delta_time, 0.0f);
}
