#pragma once

#include "Shader.h"
#include "Texture.h"
#include "../Vector/Vector3.h"

namespace TMT {
	class Material
	{
	public:
		Material(const Shader& shader, const Texture& texture, Vector3 color);
		~Material();

		// Draws elements
		void draw_elements(unsigned int nrOfIndices, unsigned int* indices);

		void update();

	private:
		Shader m_shader;
		Texture m_texture;
		Vector3 m_color;
	};
}