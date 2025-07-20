#include "Scene.h"

TMT::Scene::Scene(tmt_char scene_name, tmt_char directory) : m_scene_name(scene_name), m_directory(directory)
{
}

TMT::Scene::~Scene()
{
	for (auto& m : m_mesh_renderers) {
		delete m;
	}

	for (auto& s : m_shaders) {
		delete s.second;
	}


	for (auto& t : m_textures) {
		delete t.second;
	}

	for (auto& m : m_materials) {
		delete m.second;
	}
}

void TMT::Scene::load_scene()
{
	
}

void TMT::Scene::export_scene()
{
	// Checks to see if the file directory/directories exists, if not create it!
	if (!std::filesystem::exists(m_directory)) 
	{
		std::filesystem::create_directories(m_directory);
	}

	// Concatonize the file directory elements into one string
	std::string file_dir = std::string(m_directory) + "/" + m_scene_name + ".tmt_scene";
	// Replace any spaces with an underscore
	std::replace(file_dir.begin(), file_dir.end(), ' ', '_');

	//Open the file and fill it with data
	m_scene_out.open(file_dir);

	std::string data;

	for (auto& s : m_shaders) {
		data = "[S] \"" + s.first + "\" " + s.second->m_vertex_file_path + " " + s.second->m_fragment_file_path + "\n";
		m_scene_out << data;
	}
	for (auto& t : m_textures) {
		std::string data = "[T] \"" + t.first + "\" " + t.second->m_local_image->GetFilePath() + "\n";
		m_scene_out << data;
	}

	for (auto& m : m_materials) {
		std::string shader;
		std::string tex;

		for (auto& s : m_shaders) {
			if (s.second == m.second->m_shader) {
				shader = s.first;
			}
		}

		for (auto& t : m_textures) {
			if (t.second == m.second->m_texture) {
				tex = t.first;
			}
		}

		std::string data = "[M] \"" + m.first + "\" \"" + shader + "\" \"" + tex + "\"\n";
		m_scene_out << data;
	}


	m_scene_out.close();
}

void TMT::Scene::add_mesh_renderer(Mesh mesh_type, std::string material)
{
	Mesh mesh = mesh_type;
	if (!m_materials[material]) {
		std::cout << "ERROR: invalid material input!" << std::endl;
	}
	else 
	{
		m_mesh_renderers.push_back(new MeshRenderer(mesh, *m_materials[material]));
	}
}

void TMT::Scene::add_mesh_renderer(MeshRenderer* mesh_renderer)
{
	m_mesh_renderers.push_back(mesh_renderer);
}

void TMT::Scene::add_shader(std::string name, Shader& shader)
{
	m_shaders[name] = new Shader(shader);
}

void TMT::Scene::add_texture(std::string name, Texture& texture)
{
	m_textures[name] = new Texture(texture);
}

void TMT::Scene::add_material(std::string name, std::string shader, std::string texture, Vector3 color)
{
	if (!m_shaders[shader] || !m_textures[texture])
	{
		std::cout << "ERROR: invalid shader or texture input!" << std::endl;
	}
	else 
	{
		m_materials[name] = new Material(m_shaders[shader], m_textures[texture], color);
	}
}

void TMT::Scene::add_material(std::string name, Material& material)
{
	m_materials[name] = new Material(material);
}

void TMT::Scene::render() 
{
	for (auto& m : m_mesh_renderers) {
		m->render();
	}
}