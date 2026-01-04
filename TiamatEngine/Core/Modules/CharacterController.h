#pragma once

#include "../Module.h"

namespace TMT::Game
{
	enum class character_direction
	{
		LEFT,
		RIGHT
	};

	class CharacterController : public TMT_Module
	{
	public:
		CharacterController(const Window& window, Scene& scene, std::string character_object_name, float speed);
		~CharacterController();

		void update() override;

	private:
		float m_speed;
		character_direction m_character_dir;
	};
}