#pragma once

#include "../Module.h"
#include "../Timer.h"

namespace TMT::Game 
{
	class SpriteAnimator : public TMT_Module
	{
	public:
		SpriteAnimator(const Window& window, Scene& scene, std::string object_name, int columns, int rows, int framerate);
		~SpriteAnimator();

		void update() override;

		void select_row(int row);

		void set_single(bool is_single);

	private:
		Material& m_material;
		Shader& m_shader;
		Timer m_anim_timer;
		Vector2 m_scale;

		int m_framerate;
		int m_accumulator;
		int m_current_row;

		bool m_is_single;
	};
}