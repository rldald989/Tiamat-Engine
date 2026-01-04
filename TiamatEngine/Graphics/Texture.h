#pragma once


#include <glew.h>
#include <glfw3.h>
#include "Output.h"

namespace TMT {

	enum texture_filter {
		TMT_LINEAR=GL_LINEAR,
		TMT_NEAREST=GL_NEAREST
	};

	struct Texture
	{
		unsigned int m_texture_id;
		std::string m_local_file_path;

		int width, height;

		void load_ppm(Image& image, texture_filter filter);
		void load_stbi(const char* file_path, texture_filter filter);
		void bind();
	};
}