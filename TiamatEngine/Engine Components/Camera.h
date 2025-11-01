#pragma once

#include "Object.h"
#include "../Graphics/Window.h"

namespace TMT {
	class Camera : public Object
	{
	public:
		Camera(const Window& window, const tmt_transform& cam_transform);
		~Camera();

		void update() override;

		void zoom(float amount);

	private:
		Window m_window;
	};
}