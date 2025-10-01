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

		void clear() {
			name.clear();
			vertex.clear();
			fragment.clear();
		}
	};

	struct texture_module {
		std::string name;
		std::string file_path;

		void clear() {
			name.clear();
			file_path.clear();
		}
	};

	class Scene
	{
	public:
		Scene(tmt_char scene_name, tmt_char directory);
		~Scene();

		void load_scene();

		void export_scene();

		void add_mesh_renderer(Mesh mesh_type, std::string material);

		void add_mesh_renderer(MeshRenderer* mesh_renderer);

		void add_shader(std::string name, Shader* shader);

		void add_texture(std::string name, Texture* texture);

		void add_material(std::string name, std::string shader, std::string texture, Vector3 color);

		void add_material(std::string name, Material* material);

		void render();

	private:
		tmt_char m_scene_name;
		tmt_char m_directory;
		std::string m_file_dir;

		std::ifstream m_scene_in;
		std::ofstream m_scene_out;

		std::vector<MeshRenderer*> m_mesh_renderers;
		std::map<std::string, Texture*> m_textures;
		std::map<std::string, Material*> m_materials;
		std::map<std::string, Shader*> m_shaders;

		int m_position;

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
	};

	

}