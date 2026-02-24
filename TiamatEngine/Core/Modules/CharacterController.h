#pragma once

#include "../Module.h"
#include "../Scene.h"

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
		Collider(const Window& window, Scene& scene, Object& object, std::string collider_tag);
		~Collider();

		void conform_to_scale();

		void update() override;

		friend class CharacterController;

		float velocity;

	protected:
		bool m_collided;
		glm::vec2 m_bounds;
		std::string m_collider_tag;
		std::vector<Object*> m_others;
		Scene& m_scene;

		float m_last_x;
		float m_current_x;
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