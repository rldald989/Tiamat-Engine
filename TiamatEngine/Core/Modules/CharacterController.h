#pragma once

#include "../Module.h"

namespace TMT::Game
{
	enum class character_direction
	{
		LEFT,
		RIGHT
	};

	class Collider : public TMT_Module
	{
	public:
		Collider(const Window& window, Object& object, std::string collider_tag);
		~Collider();

		void conform_to_scale();

		void update() override;

		friend class CharacterController;

	protected:
		bool m_collided;
		glm::vec2 m_bounds;
		std::string m_collider_tag;
		std::vector<Collider*> m_others;
	};

	class CharacterController : public TMT_Module
	{
	public:
		CharacterController(Collider& collider, float speed);
		~CharacterController();

		void update() override;

	private:
		float m_speed;
		character_direction m_character_dir;
	};
}