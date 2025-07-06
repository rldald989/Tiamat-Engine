#pragma once

#include <glew.h>
#include <glfw3.h>
#include "../Output.h"

namespace TMT {
	struct Texture
	{
		unsigned int m_texture_id;

		void Load(Image& image);
		void bind();
	};
}