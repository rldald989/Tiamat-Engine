#include "Scene.h"

TMT::Scene::Scene(tmt_char scene_name, tmt_char directory) : m_scene_name(scene_name), m_directory(directory), 
m_file_dir((std::string)m_directory + "/" + (std::string)m_scene_name + ".tmt_scene")
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

		std::string extension;
		Texture* temp_tex = new Texture();
		Image* temp_image = new Image();

		shader_module m_shader_module;
		texture_module m_texture_module;

		//std::cout << "LOADED ASSET: ";
		switch (pd->type)
		{
		case scene_type::SHADER:
		
			make_shader_module(scv, seperated_data, data, count);
			add_shader(m_shader_module.name, new Shader(m_shader_module.vertex.c_str(), m_shader_module.fragment.c_str()));
			break;
		
		case scene_type::TEXTURE:
		{
			make_texture_module(scv, seperated_data, data, count);
			file_viewer tokenized_string(tokenize_string(data));
			extension = tokenized_string.while_peek(".", "\0");
			if (extension != "ppm") {
				temp_tex->load_stbi(m_texture_module.file_path.c_str());
			}
			else {
				temp_tex->load_ppm(new Image());
			}
			add_texture(m_texture_module.name, temp_tex);
			break;
		}
		case scene_type::MATERIAL:
			//std::cout << "MATERIAL: " << *pd->value << std::endl;
			break;
		case scene_type::MESH_RENDERER:
			//std::cout << "MESH_RENDERER: " << *pd->value << std::endl;
			break;
		default:
			break;
		}
		
		if (temp_tex == nullptr) {
			delete temp_tex;
			delete temp_image;
		}
		
	}

	for (auto p : parsed_data) {
		delete p->value;
		delete p;
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

	for (int i = 0; i < m_mesh_renderers.size(); i++) {
		std::string mat;
		for (auto& m : m_materials) {
			if (m.second == m_mesh_renderers[i]->m_material) {
				mat = m.first;
			}
		}

		std::string data = "[MR] (\"" + std::to_string(i) + "\" \"" + m_mesh_renderers[i]->m_mesh.get_name() + "\" \"" + mat + "\")\n";
		m_scene_out << data;
	}

	m_scene_out.close();
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
		m_mesh_renderers.push_back(new MeshRenderer(mesh, m_materials[material]));
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
		m_materials[name] = new Material(m_shaders[shader], m_textures[texture], color);
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

void TMT::Scene::make_shader_module(file_viewer<std::string> scv, std::vector<std::string> seperated_data, std::string data, int count)
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
	std::cout << "SHADER DATA: " << "name: " << m_shader_module.name <<
		"\n vertex: " << m_shader_module.vertex <<
		"\n fragment: " << m_shader_module.fragment << std::endl;
}


void TMT::Scene::make_texture_module(file_viewer<std::string> scv, std::vector<std::string> seperated_data, std::string data, int count)
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
	std::cout << "TEXTURE DATA: " << "name: " << m_texture_module.name <<
		"\n dir: " << m_texture_module.file_path << std::endl;
}
