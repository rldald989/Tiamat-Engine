#pragma once

#include "Graphics/MeshRenderer.h"
#include <typeinfo>

namespace TMT {

	class Scene
	{
	public:
		Scene(const char* scene_name);
		~Scene();

		void load_scene(const char* file_path);

		void add_mesh_renderer(Mesh mesh_type, std::string material);

		void add_mesh_renderer(MeshRenderer* mesh_renderer);

		void add_shader(std::string name, Shader* shader);

		void add_texture(std::string name, Texture* texture);

		void add_material(std::string name, std::string shader, std::string texture, Vector3 color);

		void add_material(std::string name, Material* material);

		void render();

	private:
		const char* m_scene_name;

		std::vector<MeshRenderer*> m_mesh_renderers;
		std::map<std::string, Shader*> m_shaders;
		std::map<std::string, Texture*> m_textures;
		std::map<std::string, Material*> m_materials;
	};

	

}