#include "Material.h"

TMT::Material::Material(const Shader& shader, const Texture& texture, Vector3 color) : m_shader(shader), m_texture(texture), m_color(color)
{

}

TMT::Material::~Material()
{
}

void TMT::Material::draw_elements(unsigned int nrOfIndices, unsigned int* indices)
{
	glDrawElements(GL_TRIANGLES, nrOfIndices, GL_UNSIGNED_INT, indices);
}

void TMT::Material::update()
{
	m_shader.set_vector3("color", to_glm(m_color));

	m_shader.use();
	m_texture.bind();
}
