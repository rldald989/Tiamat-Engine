#pragma once

#include <string>
#include <algorithm>

#include <filesystem>

#include <iostream>

#include "Graphics/MeshRenderer.h"

namespace TMT {

	typedef const char* tmt_char;

	class Scene
	{
	public:
		Scene(tmt_char scene_name, tmt_char directory);
		~Scene();

		void load_scene();

		void export_scene();

		void add_mesh_renderer(Mesh mesh_type, std::string material);

		void add_mesh_renderer(MeshRenderer* mesh_renderer);

		void add_shader(std::string name, Shader& shader);

		void add_texture(std::string name, Texture& texture);

		void add_material(std::string name, std::string shader, std::string texture, Vector3 color);

		void add_material(std::string name, Material& material);

		void render();

	private:
		tmt_char m_scene_name;
		tmt_char m_directory;

		std::ifstream m_scene_in;
		std::ofstream m_scene_out;

		std::vector<MeshRenderer*> m_mesh_renderers;
		std::map<std::string, Texture*> m_textures;
		std::map<std::string, Material*> m_materials;
		std::map<std::string, Shader*> m_shaders;
	};

	

}