#include "Scene.h"

TMT::Scene::Scene(tmt_char scene_name, tmt_char directory) : m_scene_name(scene_name), m_directory(directory), 
m_file_dir((std::string)m_directory + "/" + (std::string)m_scene_name + ".tmt_scene")
{
}

TMT::Scene::Scene(const Scene& copy) : m_scene_name(copy.m_scene_name), m_directory(copy.m_directory),
m_file_dir(copy.m_file_dir), found_extension(copy.found_extension), m_position(copy.m_position)
{
	m_mesh_renderers = copy.m_mesh_renderers;
	m_textures = copy.m_textures;
	m_materials = copy.m_materials;
	m_shaders = copy.m_shaders;
	m_objects = copy.m_objects;

	m_shader_module = copy.m_shader_module;
	m_texture_module = copy.m_texture_module;
	m_material_module = copy.m_material_module;
	m_mesh_renderer_module = copy.m_mesh_renderer_module;
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
		for (auto& on : m.second->m_object_names) {
			delete on;
		}
	}

	for (auto& o : m_objects) {
		delete o.second;
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
			string_viewer temp_scv(m_texture_module.file_path);
			std::string ext_data;
			while (temp_scv.position < m_texture_module.file_path.length())
			{
				ext_data = temp_scv.while_peek('.', '\0');
				temp_scv.forward();
			}

			if (ext_data == "ppm")
			{
				Image temp_image = Image();
				temp_image.Load(m_texture_module.file_path.c_str());
				temp_tex->load_ppm(temp_image, texture_filter::TMT_LINEAR);
				std::cout << temp_tex->m_local_file_path << std::endl;
			}
			else
			{
				temp_tex->load_stbi(m_texture_module.file_path.c_str(), texture_filter::TMT_LINEAR);
			}

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

void TMT::Scene::init_scene()
{
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

void TMT::Scene::append_material(const char* material_name, const char* object_name)
{
	for (auto& o : m_objects) {

		if (m_materials.find(material_name) != m_materials.end()) 
		{
			if (o.second->m_name == object_name) {
				m_materials[material_name]->m_object_names.push_back(new std::string(object_name));
			}
		}
	}
}

void TMT::Scene::add_object(Object* object, const char* linked_material)
{
	m_objects[object->m_name] = object;
	if (m_materials.find(linked_material) != m_materials.end()) {
		m_materials[linked_material]->m_object_names.push_back(new std::string(object->m_name));
	}
}


/*
	NOTE: if you don't give it a material name, it will update for all materials
*/

void TMT::Scene::add_object(Object* object, std::optional<std::string> linked_material, const bool& no_render)
{
	if (no_render) 
	{
		object->add_tag("[no_render]");
	}
	m_objects[object->m_name] = object;
	if (linked_material.has_value())
	{
		if (m_materials.find(linked_material.value()) != m_materials.end()) {
			m_materials[linked_material.value()]->m_object_names.push_back(new std::string(object->m_name));
		}
	}
	else {
		for (auto& m : m_materials) {
			m.second->m_object_names.push_back(new std::string(object->m_name));
		}
	}
	
}

void TMT::Scene::add_object(std::string name, std::string matrix_name, const tmt_transform& transform, const char* linked_material)
{
	m_objects[name] = new Object(name, matrix_name, transform);
	if (m_materials.find(linked_material) != m_materials.end()) {
		m_materials[linked_material]->m_object_names.push_back(new std::string(name));
	}
}

std::map<std::string, TMT::Object*> TMT::Scene::get_objects()
{
	return m_objects;
}

void TMT::Scene::add_module(std::string object_name, TMT_Module* module)
{
	if (m_objects.find(object_name) != m_objects.end()) {
		m_modules[object_name] = module;
	}
}

TMT::Shader* TMT::Scene::get_shader(std::string shader_name)
{
	if (m_shaders.find(shader_name) != m_shaders.end())
		return m_shaders[shader_name];
	else
	{
		std::cout << "ERROR: Shader \"" << shader_name << "\" not found!" << std::endl;
		exit(EXIT_FAILURE);
	}
}

TMT::Texture* TMT::Scene::get_texture(std::string texture_name)
{
	if (m_textures.find(texture_name) != m_textures.end())
		return m_textures[texture_name];
	else
	{
		std::cout << "ERROR: Texture \"" << texture_name << "\" not found!" << std::endl;
		exit(EXIT_FAILURE);
	}
}

TMT::Material* TMT::Scene::get_material(std::string material_name)
{
	if (m_materials.find(material_name) != m_materials.end())
		return m_materials[material_name];
	else
	{
		std::cout << "ERROR: Material \"" << material_name << "\" not found!" << std::endl;
		exit(EXIT_FAILURE);
	}
}

TMT::Material* TMT::Scene::get_linked_material(std::string object_name)
{
	bool found = false;
	for (auto& m : m_materials) {
		for (auto& o : m.second->m_object_names) {
			if (*o == object_name) {
				return m.second;
				found = true;
			}
		}
	}
	if (!found) {
		std::cout << "ERROR: Material not found at function \"get_linked_material\"" << std::endl;
		exit(EXIT_FAILURE);
	}
}

TMT::Object* TMT::Scene::get_object(std::string object_name)
{
	if (m_objects.find(object_name) != m_objects.end())
		return m_objects[object_name];
	else
	{
		std::cout << "ERROR: Object \"" << object_name << "\" not found!" << std::endl;
		exit(EXIT_FAILURE);
	}
}

void TMT::Scene::render() 
{
	for (auto& mr : m_mesh_renderers) 
	{
		Shader& shader = *mr.second->m_material->m_shader;
		for (auto& on : mr.second->m_material->m_object_names)
		{
			if (m_objects.find(*on) != m_objects.end())
			{
				Object& o = *m_objects[*on];
				std::optional<std::string> parent = o.m_parent;
				
				if (parent.has_value() && m_objects.find(parent.value()) != m_objects.end() && o.matrix_name != "camera_transform")
				{
					o.m_final_transform = m_objects[parent.value()]->m_final_transform * o.update();
					shader.set_matrix4(o.matrix_name.c_str(), o.m_final_transform);
				}
				else
					shader.set_matrix4(o.matrix_name.c_str(), o.update());

				if (!o.has_tag("[no_render]"))
					mr.second->render();
			}
		}
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
