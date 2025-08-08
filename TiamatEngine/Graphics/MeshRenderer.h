#pragma once

#include "Buffers.h"
#include "Shader.h"
#include "Mesh.h"
#include "Material.h"

namespace TMT 
{
	class MeshRenderer
	{
	public:
		MeshRenderer(const Mesh& mesh, Material* material);
		~MeshRenderer();

		void render();

		friend class Scene;

	protected:

		Mesh m_mesh;
		Material* m_material;

		VAO m_vao;
		VBO m_vbo;
		IBO m_ibo;
	};
}