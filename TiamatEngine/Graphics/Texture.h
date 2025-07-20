#pragma once

#include <glew.h>
#include <glfw3.h>
#include "../Output.h"

namespace TMT {
	struct Texture
	{
		unsigned int m_texture_id;
		Image* m_local_image;

		void Load(Image* image);
		void bind();
	};
}