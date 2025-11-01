#include "Parser.h"

TMT::Parser::Parser(std::vector<std::string>& tokens) : m_tokens(tokens), m_viewer(m_tokens)
{

}

TMT::Parser::~Parser()
{
	
}

std::vector<TMT::scene_component*> TMT::Parser::parse()
{
	std::vector<scene_component*> parsed_data;
	std::string buffer;
	std::string str_buffer;
	while (m_viewer.peek() != "\0") {

		buffer = m_viewer.while_peek("[", "]");
		m_viewer.forward();
		// TODO: Add a way to search through the found data (and find strings and add them to the output data)
		if (buffer == "S") {
			m_viewer.continue_if("(", false, "(Texture)");
			str_buffer = m_viewer.while_peek("(", ")");
			parsed_data.push_back(new scene_component{ scene_type::SHADER, new std::string(str_buffer) });
			str_buffer.clear();
		}
		else if (buffer == "T") {
			// Checks if parenthesis are found, otherwise exit
			m_viewer.continue_if("(", false, "(Texture)");
			str_buffer = m_viewer.while_peek("(", ")");
			parsed_data.push_back(new scene_component{ scene_type::TEXTURE, new std::string(str_buffer) });
			str_buffer.clear();
		}
		else if (buffer == "M") 
		{
			// Checks if parenthesis are found, otherwise exit
			m_viewer.continue_if("(", false, "(Material)");
			str_buffer = m_viewer.while_peek("(", ")");
			parsed_data.push_back(new scene_component{ scene_type::MATERIAL, new std::string(str_buffer) });
			str_buffer.clear();
		}
		else if (buffer == "MR")
		{
			// Checks if parenthesis are found, otherwise exit
			m_viewer.continue_if("(", false, "(Mesh Renderer)");
			str_buffer = m_viewer.while_peek("(", ")");
			parsed_data.push_back(new scene_component{ scene_type::MESH_RENDERER, new std::string(str_buffer) });
			str_buffer.clear();
		}
		else {
			continue;
		}
		
	}
	return parsed_data;
}
