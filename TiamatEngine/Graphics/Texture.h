#pragma once


#include <glew.h>
#include <glfw3.h>
#include "Output.h"

namespace TMT {
	struct Texture
	{
		unsigned int m_texture_id;
		std::string m_local_file_path;

		int width, height;

		void load_ppm(Image* image);
		void load_stbi(const char* file_path);
		void bind();
	};
}