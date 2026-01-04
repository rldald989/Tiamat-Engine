#pragma once

#include "Parser.h"
#include "../Graphics/Material.h"
#include <map>

namespace TMT 
{
	struct material_properties
	{
		std::string name;
		std::string linked_shader;
		std::string linked_texture;
		std::vector<std::string*> linked_objects;
	};

	class MaterialManager
	{
	public:
		MaterialManager(std::string file_directory);
		~MaterialManager();

		void export_materials(std::map<std::string, Material*> materials, std::map<std::string, Texture*> textures, std::map<std::string, Shader*> shaders);

	private:
		std::ofstream out;

		std::string m_file_directory;

		std::map<std::string, Material*> m_materials;
	};
}