#pragma once

#include <string>
#include <algorithm>

#include <filesystem>

#include <iostream>

#include "Graphics/MeshRenderer.h"

#include "Parser.h"

namespace TMT {

	typedef const char* tmt_char;

	struct shader_module {
		std::string name;
		std::string vertex;
		std::string fragment;
	};

	struct texture_module {
		std::string name;
		std::string file_path;
	};

	struct material_module {
		std::string name;
		std::string shader_name;
		std::string texture_name;
	};

	struct mesh_renderer_module {
		std::string index;
		std::string material_name;
	};

	class Scene
	{
	public:
		Scene(tmt_char scene_name, tmt_char directory);
		~Scene();

		void load_scene();

		void export_scene();

		void add_mesh_renderer(Mesh mesh_type, std::string material, int index);
		void add_mesh_renderer(Mesh mesh_type, std::string material);

		void add_shader(std::string name, Shader* shader);

		void add_texture(std::string name, Texture* texture);

		void add_material(std::string name, std::string shader, std::string texture, Vector3 color);

		void add_material(std::string name, Material* material);

		Shader* get_shader(std::string shader_name);
		Texture* get_texture(std::string texture_name);
		Material* get_material(std::string material_name);

		void render();

	private:
		tmt_char m_scene_name;
		tmt_char m_directory;
		std::string m_file_dir;

		std::ifstream m_scene_in;
		std::ofstream m_scene_out;

		std::map<int, MeshRenderer*> m_mesh_renderers;
		std::map<std::string, Texture*> m_textures;
		std::map<std::string, Material*> m_materials;
		std::map<std::string, Shader*> m_shaders;

		int m_position;

		bool found_extension;

		shader_module m_shader_module;
		texture_module m_texture_module;
		material_module m_material_module;
		mesh_renderer_module m_mesh_renderer_module;

		std::string peek(std::vector<std::string> tokens, int ahead = 1) const
		{
			if (m_position + ahead < tokens.size()) {
				return tokens[m_position];
			}
			else {
				return {};
			}
		}

		void make_shader_module(file_viewer<std::string> scv, std::vector<std::string> seperated_data, std::string data, int count);
		void make_texture_module(file_viewer<std::string> scv, std::vector<std::string> seperated_data, std::string data, int count);
		void make_material_module(file_viewer<std::string> scv, std::vector<std::string> seperated_data, std::string data, int count);
		void make_mesh_renderer_module(file_viewer<std::string> scv, std::vector<std::string> seperated_data, std::string data, int count);
	};

	

}