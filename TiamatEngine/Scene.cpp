#include "Scene.h"

TMT::Scene::Scene(const char* scene_name) : m_scene_name(scene_name)
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

void TMT::Scene::load_scene(const char* file_path)
{
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

void TMT::Scene::add_shader(std::string name, Shader* shader)
{
	m_shaders[name] = shader;
}

void TMT::Scene::add_texture(std::string name, Texture* texture)
{
	m_textures[name] = texture;
}

void TMT::Scene::add_material(std::string name, std::string shader, std::string texture, Vector3 color)
{
	if (!m_shaders[shader] || !m_textures[texture])
	{
		std::cout << "ERROR: invalid shader or texture input!" << std::endl;
	}
	else 
	{
		m_materials[name] = new Material(*m_shaders[shader], *m_textures[texture], color);
	}
}

void TMT::Scene::add_material(std::string name, Material* material)
{
	m_materials[name] = material;
}

void TMT::Scene::render() 
{
	for (auto& m : m_mesh_renderers) {
		m->render();
	}
}