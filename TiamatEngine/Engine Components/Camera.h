#pragma once

#include "Object.h"
#include "../Graphics/Window.h"

namespace TMT {
	class Camera : public Object
	{
	public:
		Camera(std::string name, Window& window, const tmt_transform& cam_transform);
		~Camera();

		glm::mat4 update() override;

	private:
		glm::mat4 m_projection;
		Window& m_window;
	};
}