#include "MaterialManager.h"

TMT::MaterialManager::MaterialManager(std::string file_directory) : m_file_directory(file_directory)
{
}

TMT::MaterialManager::~MaterialManager()
{
}

void TMT::MaterialManager::export_materials(std::map<std::string, Material*> materials, std::map<std::string, Texture*> textures, std::map<std::string, Shader*> shaders)
{
	for (auto& m : materials) {
		out.open(m_file_directory + m.first + ".tmt_material");
		for (auto& s : shaders) 
		{
			if (m.second->m_shader == s.second) 
			{
				std::cout << "\"" << s.first << "\"" << std::endl;
			}
		}
		for (auto& t : textures)
		{
			if (m.second->m_texture == t.second)
			{
				std::cout << "\"" << t.first << "\"" << std::endl;
			}
		}
		for (auto& o : m.second->m_object_names) 
		{
			out << "\"" << *o << "\"" << std::endl;
		}

		out.close();
	}
}
