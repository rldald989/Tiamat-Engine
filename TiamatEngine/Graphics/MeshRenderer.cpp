#include "MeshRenderer.h"

TMT::MeshRenderer::MeshRenderer(const Mesh& mesh, const Material& material) : m_mesh(mesh), m_material(material), m_vao(), m_vbo(), m_ibo()
{
    std::cout << m_mesh.get_nr_of_indicies();
    m_vao.bind();
    m_vbo.bind();
    m_ibo.bind();

    glBufferData(GL_ARRAY_BUFFER, m_mesh.get_nr_of_verticies() * sizeof(vertex), m_mesh.get_vertex_data(), GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_mesh.get_nr_of_indicies(), m_mesh.get_index_data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(TMT::vertex), NULL);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    m_ibo.unbind();
    m_vbo.unbind();
    m_vao.unbind();
}

TMT::MeshRenderer::~MeshRenderer()
{

}

void TMT::MeshRenderer::render()
{
    glActiveTexture(GL_TEXTURE0);
    m_material.update();
    m_vao.bind();
    m_material.draw_elements(m_mesh.get_nr_of_indicies(), m_mesh.get_index_data());
}
