#include "SpriteAnimator.h"

TMT::Game::SpriteAnimator::SpriteAnimator(const Window& window, Scene& scene, std::string object_name, int columns, int rows, int framerate) : 
	TMT_Module(window, scene, *scene.get_object(object_name)), m_anim_timer(1.f/framerate),
	m_material(*scene.get_linked_material(object_name)), m_scale(1.f/rows, 1.f/columns),
	m_shader(*m_material.get_shader()), m_framerate(framerate), m_accumulator(0)
{
	m_shader.set_vector2("tiling", glm::vec2(m_scale.m_x, m_scale.m_y));
	m_shader.set_vector2("texture_position", glm::vec2(0, 0));
}

TMT::Game::SpriteAnimator::~SpriteAnimator()
{
}

void TMT::Game::SpriteAnimator::update()
{
	if (m_accumulator >= m_scale.m_x) {
		m_accumulator == 0;
	}
	m_anim_timer.update();
	if (m_anim_timer.get_end_status()) {
		m_anim_timer.restart();
		m_accumulator++;
		if(!m_is_single)
			m_shader.set_vector2("texture_position", glm::vec2(m_accumulator * m_scale.m_x, m_current_row * m_scale.m_y));
		else if (m_is_single)
			m_shader.set_vector2("texture_position", glm::vec2(0, m_current_row * m_scale.m_y));
	}

	

}

void TMT::Game::SpriteAnimator::select_row(int row)
{
	if (row > m_scale.m_y * 100.f) {
		std::cout << "ERROR: row value is larger than sprite size" << std::endl;
		exit(EXIT_FAILURE);
	}
	
	m_current_row = row;
}

void TMT::Game::SpriteAnimator::set_single(bool is_single)
{
	m_is_single = is_single;
}
