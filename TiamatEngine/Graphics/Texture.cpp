#include "Texture.h"

void TMT::Texture::Load(Image& image)
{
	std::vector<float> image_data = Image::image_to_float(image);

	glGenTextures(1, &m_texture_id);

	bind();
	// set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height, nrChannels;
	width = image.GetResolution().m_x;
	height = image.GetResolution().m_y;

	if (image_data.size() > 0)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_FLOAT, image_data.data());
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
}

void TMT::Texture::bind()
{
	glBindTexture(GL_TEXTURE_2D, m_texture_id);
}
