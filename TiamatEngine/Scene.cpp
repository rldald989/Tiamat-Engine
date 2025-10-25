#include "Scene.h"

TMT::Scene::Scene(tmt_char scene_name, tmt_char directory) : m_scene_name(scene_name), m_directory(directory), 
m_file_dir((std::string)m_directory + "/" + (std::string)m_scene_name + ".tmt_scene")
{
}

TMT::Scene::~Scene()
{
	for (auto& m : m_mesh_renderers) {
		delete m.second;
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
	std::replace(m_file_dir.begin(), m_file_dir.end(), ' ', '_');
	Tokenizer tokenizer;
	tokenizer.load_file(m_file_dir.c_str());
	std::vector<std::string> tokens = tokenizer.tokenize();

	Parser parser(tokens);
	std::vector<scene_component*> parsed_data = parser.parse();

	for (auto& pd : parsed_data) {

		std::vector<std::string> seperated_data;
		for (char c : *pd->value) {
			seperated_data.push_back(std::string(1, c));
		}

		// SCV stands for Scene Component Viewer
		file_viewer<std::string> scv(seperated_data);
		std::string data = "";
		int count = 0;

		//std::cout << "LOADED ASSET: ";
		if(pd->type == scene_type::SHADER)
		{
			link_shader_data(scv, seperated_data, data, count);
			add_shader(m_shader_module.name, new Shader(m_shader_module.vertex.c_str(), m_shader_module.fragment.c_str()));
			count = 0;
		}
		else if(pd->type == scene_type::TEXTURE)
		{
			Texture* temp_tex = new Texture();
			link_texture_data(scv, seperated_data, data, count);
			temp_tex->load_stbi(m_texture_module.file_path.c_str());
			add_texture(m_texture_module.name, temp_tex);
			count = 0;
		}
		else if (pd->type == scene_type::MATERIAL) 
		{
			link_material_data(scv, seperated_data, data, count);
			add_material(m_material_module.name, m_material_module.shader_name, m_material_module.texture_name, Vector3(1, 1, 1));
			count = 0;
		}
		else if(pd->type == scene_type::MESH_RENDERER)
		{
			link_mesh_renderer_data(scv, seperated_data, data, count);
			add_mesh_renderer(TMT::Quad(), m_mesh_renderer_module.material_name, std::atoi(m_mesh_renderer_module.priority.c_str()));
			count = 0;
		}
		
		
	}


	for (auto& m : m_mesh_renderers) {
		std::cout << "Mesh Renderer: " << m.first << std::endl;
	}

	for (auto& s : m_shaders) {
		std::cout << "Shader: " << s.first << std::endl;
	}


	for (auto& t : m_textures) {
		std::cout << "Texture: " << t.first << std::endl;
	}

	for (auto& m : m_materials) {
		std::cout << "Material: " << m.first << std::endl;
	}
}

void TMT::Scene::export_scene()
{
	// Checks to see if the file directory/directories exists, if not create it!
	if (!std::filesystem::exists(m_directory)) 
	{
		std::filesystem::create_directories(m_directory);
	}

	// Replace any spaces with an underscore
	std::replace(m_file_dir.begin(), m_file_dir.end(), ' ', '_');

	//Open the file and fill it with data
	m_scene_out.open(m_file_dir);

	std::string data;

	// Adds the shaders to the file
	for (auto& s : m_shaders) {
		data = "[S] (\"" + s.first + "\" \"" + s.second->m_vertex_file_path + "\" \"" + s.second->m_fragment_file_path + "\")\n";
		m_scene_out << data;
	}

	// Adds the textures to the file
	for (auto& t : m_textures) {
		std::string data = "[T] (\"" + t.first + "\" \"" + t.second->m_local_file_path + "\")\n";
		
		m_scene_out << data;
	}

	// Adds the materials to the file
	for (auto& m : m_materials) {
		std::string shader;
		std::string tex;

		// Checks what shader in m_shaders is the same as the shader in m_materials
		for (auto& s : m_shaders) {
			if (s.second == m.second->m_shader) {
				shader = s.first;
			}
		}

		// Checks what shader in m_textures is the same as the shader in m_textures
		for (auto& t : m_textures) {
			if (t.second == m.second->m_texture) {
				tex = t.first;
			}
		}

		std::string data = "[M] (\"" + m.first + "\" \"" + shader + "\" \"" + tex + "\")\n";
		m_scene_out << data;
	}

	for (auto& mr : m_mesh_renderers) {
		std::string mat;
		for (auto& m : m_materials) {
			if (m.second == mr.second->m_material) {
				mat = m.first;
			}
		}

		std::string data = "[MR] (\"" + std::to_string(mr.first) + "\" \"" + mat + "\")\n";
		m_scene_out << data;
	}

	m_scene_out.close();
}

void TMT::Scene::add_mesh_renderer(Mesh mesh_type, std::string material, int index)
{
	Mesh mesh = mesh_type;		
	if (!m_materials[material]) {
		std::cout << "ERROR: invalid material input!" << std::endl;
		exit(EXIT_FAILURE);
	}
	else
	{
		m_mesh_renderers[index] = new MeshRenderer(mesh, m_materials[material]);
	}
}

void TMT::Scene::add_mesh_renderer(Mesh mesh_type, std::string material)
{
	Mesh mesh = mesh_type;
	if (!m_materials[material]) {
		std::cout << "ERROR: invalid material input!" << std::endl;
		exit(EXIT_FAILURE);
	}
	else
	{
		m_mesh_renderers[m_mesh_renderers.size()+1] = new MeshRenderer(mesh, m_materials[material]);
	}
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
		m_materials[name] = new Material(m_shaders[shader], m_textures[texture], color);
	}
}

void TMT::Scene::add_material(std::string name, Material* material)
{
	m_materials[name] = material;
}

TMT::Shader* TMT::Scene::get_shader(std::string shader_name)
{
	return m_shaders[shader_name];
}

TMT::Texture* TMT::Scene::get_texture(std::string texture_name)
{
	return m_textures[texture_name];
}

TMT::Material* TMT::Scene::get_material(std::string material_name)
{
	return m_materials[material_name];
}

void TMT::Scene::render() 
{
	for (auto& m : m_mesh_renderers) {
		m.second->render();
	}
}

void TMT::Scene::link_shader_data(file_viewer<std::string> scv, std::vector<std::string> seperated_data, std::string data, int count)
{
	while (scv.position < seperated_data.size()) {
		data = scv.while_peek("\"", "\"");
		switch (count)
		{
		case 0:
			m_shader_module.name = data;
			break;
		case 1:
			m_shader_module.vertex = data;
			break;
		case 2:
			m_shader_module.fragment = data;
			count = 0;
			break;
		default:
			break;
		}
		scv.forward();
		count++;
	}
	//std::cout << "SHADER DATA: " << "name: " << m_shader_module.name <<
	//	"\n vertex: " << m_shader_module.vertex <<
	//	"\n fragment: " << m_shader_module.fragment << std::endl;
}

void TMT::Scene::link_texture_data(file_viewer<std::string> scv, std::vector<std::string> seperated_data, std::string data, int count)
{
	while (scv.position < seperated_data.size()) {
		data = scv.while_peek("\"", "\"");
		switch (count)
		{
		case 0:
			m_texture_module.name = data;
			break;
		case 1:
			m_texture_module.file_path = data;
			count = 0;
			break;
		default:
			break;
		}
		scv.forward();
		count++;
	}
	//std::cout << "TEXTURE DATA: " << "name: " << m_texture_module.name <<
	//	"\n dir: " << m_texture_module.file_path << std::endl;
}

void TMT::Scene::link_material_data(file_viewer<std::string> scv, std::vector<std::string> seperated_data, std::string data, int count)
{
	while (scv.position < seperated_data.size()) {
		data = scv.while_peek("\"", "\"");
		switch (count)
		{
		case 0:
			m_material_module.name = data;
			break;
		case 1:
			m_material_module.shader_name = data;
			break;
		case 2:
			m_material_module.texture_name = data;
			count = 0;
			break;
		default:
			break;
		}
		scv.forward();
		count++;
	}
	//std::cout << "MATERIAL DATA: " << "name: " << m_material_module.name <<
	//	"\n shader: " << m_material_module.shader_name <<
	//	"\n texture: " << m_material_module.texture_name << std::endl;
}

void TMT::Scene::link_mesh_renderer_data(file_viewer<std::string> scv, std::vector<std::string> seperated_data, std::string data, int count)
{
	while (scv.position < seperated_data.size()) {
		data = scv.while_peek("\"", "\"");
		switch (count)
		{
		case 0:
			m_mesh_renderer_module.priority = data;
			break;
		case 1:
			m_mesh_renderer_module.material_name = data;
			count = 0;
			break;
		default:
			break;
		}
		
		scv.forward();
		count++;
	}
	//std::cout << "MESH RENDRERER DATA: " << "mesh renderer index: " << m_mesh_renderer_module.index << "\n" 
	//	<< "material name: " << m_mesh_renderer_module.material_name << std::endl;
}
